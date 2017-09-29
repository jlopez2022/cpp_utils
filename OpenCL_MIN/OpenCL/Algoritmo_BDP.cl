/*/0.0 Uncomment to use c checker the following lines:
#include <math.h>
#include <stdio.h>
#define __global
#define __local
typedef unsigned char uchar;
typedef unsigned short ushort;
#define restrict 
#define __kernel 
int get_global_id(int i1){ return 1; }  
#define CLK_LOCAL_MEM_FENCE 1
int barrier(int i) {return i;}
//*/


__kernel void algoritmo_BDP(
	__global uchar*  video,	    // #0 ALL the video
	__global ushort*  coefxy1,  // #1 coefficients entered first time only
	__global short*  coefs,     // #2 coefficients entered first time only
	__global uchar*  bg,		// #3 Background. intermediate data. input first time only
	__global uchar*  bgcount,   // #4 intermediate data. intermediate data. input first time only
	__global ushort*  move,      // #5 intermediate data. Not needed to be preset to any number
	__global uchar*  imageout,	// #6 grayscale image output size=pixels
	__global int*  move1,		// #7 output data. size=ymax. Occupation in the left side
	__global int*  move2,		// #8 output data. size=ymax Occupation in the right side
	int framesize,			    // #9 input data. Input one time only. int=32-bit width=4giga
	int index					// #10 index. must be done index++ every frame. It must be < (number of frames-3) or be 0!!
	)
{
	__global uchar *imagen0,*imagen1,*imagen2;//image before, actual and following, must be __global (to be matched with video)
	//MUST BE DONE AT c++!!!!:   if (index>maxframes-3) index=0;
	imagen0=video+index*framesize+6;
	imagen1=imagen0+framesize;
	imagen2=imagen1+framesize;
	long pix = get_global_id(0);

	short deltaBK = coefs[0];
	short maxcountBK = coefs[1];
	short max_lat = coefs[2];
	short max_bg = coefs[3];
	short xmax = coefs[4]; //block size!
	short ymax = coefs[5]; //number of blocks
	short xmed = coefs[6];
	long pixels = xmax*ymax;

	uchar out = 0;
	move[pix] = 0;

	if (coefxy1[pix]>1e-10f)
	{
		//Calculus of dif with pixels at left&right and line before and after:
		short lat = 0;
		if ((pix > 10) && (pix < pixels - 11))
		{
			lat = 4 * imagen2[pix - 10] - 8 * imagen1[pix - 10] + 4 * imagen0[pix - 10];
			lat += 4 * imagen2[pix + 10] - 8 * imagen1[pix + 10] + 4 * imagen0[pix + 10];
			lat += -6 * imagen2[pix] + 12 * imagen1[pix] - 6 * imagen0[pix];
			if (lat < 0) lat = -lat;
		}
		//3. Calculates if background: 
		if ((imagen1[pix]>30) && (imagen1[pix]<245) && (lat < deltaBK))
		{
			bgcount[pix]++;
			if (bgcount[pix]>maxcountBK)
				bg[pix] = imagen1[pix];
		}
		//4. Calculates if car or background:
		if ((abs(imagen1[pix] - bg[pix]) < max_bg) && (lat < max_lat))
			out = 0; //background
		else
		{
			out = imagen1[pix]; //car
			move[pix] = coefxy1[pix];//add surface
		}
	}

	imageout[pix] = out;

	//Data concentration 1280 times:
	barrier(CLK_LOCAL_MEM_FENCE); //to give time to all move[pix] be finished
	//This loop reduces the output data from 900k to 720. Also reduces the CPU operations to obtain move1&2 1280 times (from 900k to 720 operations):
	if (pix<ymax)
	{
		int sum1 = 0, sum2 = 0;
		int ix0 = pix*xmax;
		short x;
		for (x=0;x<xmed;x++)
			sum1 += move[ix0 + x];
		for (; x < xmax;x++)
			sum2 += move[ix0 + x];
		move1[pix] = sum1;
		move2[pix] = sum2;
	}
}

__kernel void algoritmo_BDP_UNCOMPRESSED(
	__global uchar*  imagen0,	// #0 frame0
	__global ushort*  coefxy1,  // #1 coefficients entered first time only
	__global short*  coefs,     // #2 coefficients entered first time only
	__global uchar*  bg,		// #3 Background. intermediate data. input first time only
	__global uchar*  bgcount,   // #4 intermediate data. intermediate data. input first time only
	__global ushort*  move,     // #5 Not needed 
	__global uchar*  imageout,	// #6 grayscale image output size=pixels
	__global int*  move1,		// #7 output data. size=ymax. Occupation in the left side
	__global int*  move2,		// #8 output data. size=ymax Occupation in the right side
	int framesize,			    // #9 input data. Input one time only. int=32-bit width=4giga
	int index,					// #10 index. must be done index++ every frame. It must be < (number of frames-3) or be 0!!
	__global uchar*  imagen1,	// #11 frame1
	__global uchar*  imagen2	// #12 frame2
	//__local uchar*  lmove1,		// #13 
	//__local uchar*  lmove2		// #14 
	)
{
	//__global uchar *imagen0,*imagen1,*imagen2;//image before, actual and following, must be __global (to be matched with video)
	//MUST BE DONE AT c++!!!!:   if (index>maxframes-3) index=0;
	//imagen0=video+index*framesize+6;
	//imagen1=imagen0+framesize;
	//imagen2=imagen1+framesize;
	long pix = get_global_id(0);

	short deltaBK = coefs[0];
	short maxcountBK = coefs[1];
	short max_lat = coefs[2];
	short max_bg = coefs[3];
	short xmax = coefs[4]; //block size!
	short ymax = coefs[5]; //number of blocks
	short xmed = coefs[6];
	long pixels = xmax*ymax;

	uchar out = 0;
	int mov = 0;

	if (coefxy1[pix]>1e-10f)
	{
		//Calculus of dif with pixels at left&right and line before and after:
		short lat = 0;
		if ((pix > 10) && (pix < pixels - 11))
		{
			lat = 4 * imagen2[pix - 10] - 8 * imagen1[pix - 10] + 4 * imagen0[pix - 10];
			lat += 4 * imagen2[pix + 10] - 8 * imagen1[pix + 10] + 4 * imagen0[pix + 10];
			lat += -6 * imagen2[pix] + 12 * imagen1[pix] - 6 * imagen0[pix];
			if (lat < 0) lat = -lat;
		}
		//3. Calculates if background: 
		if ((imagen1[pix]>30) && (imagen1[pix]<245) && (lat < deltaBK))
		{
			bgcount[pix]++;
			if (bgcount[pix]>maxcountBK)
				bg[pix] = imagen1[pix];
		}
		//4. Calculates if car or background:
		if ((abs(imagen1[pix] - bg[pix]) < max_bg) && (lat < max_lat))
			out = 0; //background
		else
		{
			out = imagen1[pix]; //car
			mov = coefxy1[pix];//add surface
		}
	}

	imageout[pix] = out;

	if (pix % xmax < xmed)
		move1[pix]=mov;
	else
		move2[pix]=mov;


}

__kernel void algoritmo_BDP_COMPRESSED2(
	__global uchar*  imagen0,	// #0 frame0
	__global ushort*  coefxy1,  // #1 coefficients entered first time only
	__global short*  coefs,     // #2 coefficients entered first time only
	__global uchar*  bg,		// #3 Background. intermediate data. input first time only
	__global uchar*  bgcount,   // #4 intermediate data. intermediate data. input first time only
	__global ushort*  move,     // #5 Not needed 
	__global uchar*  imageout,	// #6 grayscale image output size=pixels
	__global int*  move1,		// #7 output data. size=ymax. Occupation in the left side
	__global int*  move2,		// #8 output data. size=ymax Occupation in the right side
	int framesize,			    // #9 input data. Input one time only. int=32-bit width=4giga
	int index,					// #10 index. must be done index++ every frame. It must be < (number of frames-3) or be 0!!
	__global uchar*  imagen1,	// #11 frame1
	__global uchar*  imagen2,	// #12 frame2
	__local int*  lmov1,		// #13 size=max_local_size
	__local int*  lmov2			// #14 
	)
{
	//__global uchar *imagen0,*imagen1,*imagen2;//image before, actual and following, must be __global (to be matched with video)
	//MUST BE DONE AT c++!!!!:   if (index>maxframes-3) index=0;
	//imagen0=video+index*framesize+6;
	//imagen1=imagen0+framesize;
	//imagen2=imagen1+framesize;
	long pix = get_global_id(0);

	short deltaBK = coefs[0];
	short maxcountBK = coefs[1];
	short max_lat = coefs[2];
	short max_bg = coefs[3];
	short xmax = coefs[4]; //block size!
	short ymax = coefs[5]; //number of blocks
	short xmed = coefs[6];
	long pixels = xmax*ymax;

	uchar out = 0;
	int mov = 0;


	if (coefxy1[pix]>0)
	{
		//Calculus of dif with pixels at left&right and line before and after:
		short lat = 0;
		if ((pix > 10) && (pix < pixels - 11))
		{
			lat = 4 * imagen2[pix - 10] - 8 * imagen1[pix - 10] + 4 * imagen0[pix - 10];
			lat += 4 * imagen2[pix + 10] - 8 * imagen1[pix + 10] + 4 * imagen0[pix + 10];
			lat += -6 * imagen2[pix] + 12 * imagen1[pix] - 6 * imagen0[pix];
			if (lat < 0) lat = -lat;
		}
		//3. Calculates if background: 
		if ((imagen1[pix]>30) && (imagen1[pix]<245) && (lat < deltaBK))
		{
			bgcount[pix]++;
			if (bgcount[pix]>maxcountBK)
				bg[pix] = imagen1[pix];
		}
		//4. Calculates if car or background:
		if ((abs(imagen1[pix] - bg[pix]) < max_bg) && (lat < max_lat))
			out = 0; //background
		else
		{
			out = imagen1[pix]; //car
			mov = coefxy1[pix];//add surface
		}
	}

	imageout[pix] = out;

	int lik= get_local_id(0);
	int group_size=get_local_size(0);
	lmov1[lik]=lmov2[lik]=0.0f;

	if (pix % xmax < xmed)
		lmov1[lik]=mov;
	else
		lmov2[lik]=mov;

	barrier(CLK_LOCAL_MEM_FENCE); //to give time to all lmov1 & 2 be loaded

	//Tree mode data concentration of local arrays lmov1[0..255] & lmov2[0..255] to: lmov1[0], lmov2[0] in 8 steps!
	for (int med=group_size/2;med>0;med>>=1)
	{
		if (lik<med)
		{
			lmov1[lik]+=lmov1[lik+med];
			lmov2[lik]+=lmov2[lik+med];
		}
		barrier(CLK_LOCAL_MEM_FENCE); //to give time to all lmov1,2 be added 
	}

	//data output accordingly work_group:
	if (lik==0)
	{
		int k2=get_group_id(0);
		move1[k2]=lmov1[0];
		move2[k2]=lmov2[0];
	}
}

