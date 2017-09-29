
//================= Javier Luis Lopez Segura, Acciona Infraestructuras SA July 2016 =======================


//0.0 Uncomment to use c checker
/*
not_compile_thisSSSSSS
#define __global 
#define __local
#define __kernel
#define uchar unsigned char
#define restrict 
#include <math.h>
int get_global_id(int i1){ return 1; }
void barrier(int i1){}
int CLK_LOCAL_MEM_FENCE;
#define event_t int
#define float4 float
#define int4 int
//*/





//2.0 #define of constant variables
#ifndef M_PI
	#define M_PI 3.1415926535f
#endif
// Flow vector scaling factor
#define FLOW_SCALING_FACTOR (0.25f)  //(1.0f/4.0f)
#define DELTA_MOVE .0926f    //km/h  = DELTA_MOVE*(30*3.6*2)

//3.0 Define inline functions
// Image access without bounds wrapping.
#define PO(image,x,y,W) ((image)[(y)*(W)+(x)])
// Image access with bounds wrapping.
#define P(image,x,y,W,H) ((image)[( (y)>=(H) ? (H)-1 : ((y)<0 ? 0:(y)) )*(W)+( (x)>=W ? W-1 : ((x)<0 ? 0 : (x)) )])

#define Ix_(im1,i,j,W,H) ((P(im1, (i)+1, (j), W, H) - P(im1, (i)-1, (j), W, H)) >> 1)
#define Iy_(im1,i,j,W,H) ((P(im1, (i), (j)+1, W, H) - P(im1, (i), (j)-1, W, H)) >> 1)

//4.0 Structs and classes definitions
typedef struct colorW
{
//public:
	int s0;
	int s1;
	int s2;
	//int s3;
}colS;

//5.0 Inline functions
//5.1 Calculate color by using color wheel:
void computeColor(float fx, float fy, unsigned char *pix)
{
	// hard-coded colorwheel constants
	const int l_ncols = 55;
	const int l_colorwheel[] = {
		255, 0, 0,
		255, 17, 0,
		255, 34, 0,
		255, 51, 0,
		255, 68, 0,
		255, 85, 0,
		255, 102, 0,
		255, 119, 0,
		255, 136, 0,
		255, 153, 0,
		255, 170, 0,
		255, 187, 0,
		255, 204, 0,
		255, 221, 0,
		255, 238, 0,
		255, 255, 0,
		213, 255, 0,
		170, 255, 0,
		128, 255, 0,
		85, 255, 0,
		43, 255, 0,
		0, 255, 0,
		0, 255, 63,
		0, 255, 127,
		0, 255, 191,
		0, 255, 255,
		0, 232, 255,
		0, 209, 255,
		0, 186, 255,
		0, 163, 255,
		0, 140, 255,
		0, 116, 255,
		0, 93, 255,
		0, 70, 255,
		0, 47, 255,
		0, 24, 255,
		0, 0, 255,
		19, 0, 255,
		39, 0, 255,
		58, 0, 255,
		78, 0, 255,
		98, 0, 255,
		117, 0, 255,
		137, 0, 255,
		156, 0, 255,
		176, 0, 255,
		196, 0, 255,
		215, 0, 255,
		235, 0, 255,
		255, 0, 255,
		255, 0, 213,
		255, 0, 170,
		255, 0, 128,
		255, 0, 85,
		255, 0, 43
	};
	float rad = sqrt(fx * fx + fy * fy);
	float a = atan2(-fy, -fx) / (float)M_PI;
	float fk = (a + 1.0f) / 2.0f * (l_ncols - 1);
	int k0 = (int)fk;

	colS col;
	col.s0 = *(l_colorwheel + k0 * 3 + 0);
	col.s1 = *(l_colorwheel + k0 * 3 + 1);
	col.s2 = *(l_colorwheel + k0 * 3 + 2);
	if (rad > 1) rad = 1; // max at 1
	pix[0] = (uchar) (255 - rad * (255 - col.s0));
	pix[1] = (uchar) (col.s1 = 255 - rad * (255 - col.s1));
	pix[2] = (uchar) (255 - rad * (255 - col.s2));
}

//5.2. Find inverse of 2x2 int matrix,  returns 1 on success, 0 on failure
int get_matrix_inv(float* G, float* G_inv)
{
	float detG = (float)(G[0] * G[3] - G[1] * G[2]);
	if (detG <= 1.0f) { return 0; }
	G_inv[0] = G[3] / detG;		G_inv[1] = -G[1] / detG;
	G_inv[2] = -G[2] / detG;	G_inv[3] = G[0] / detG;
	return 1;
}


//10.0 Kernel definition
__kernel void algoritmo_KNP(
	__global uchar*  video,// #0 ALL the video
	__global float*  coefx, // #1. coefficients entered first time only
	__global float*  coefy, // #2. coefficients entered first time only
	__global uchar*  out,   // #3 RGB color output sized 3*xmax*ymax
	__global float*  move,  // #4. buffer. No preset needed
	__global float*  movy1, // #5. output reduced data. Array size=ymax
	__global float*  movy2, // #6. output reduced data. Array size=ymax
	__global int*  count1,	// #7. output reduced data. Array size=ymax
	__global int*  count2,	// #8. output reduced data. Array size=ymax
	int WIDTH,				// #9. xmax entered first time only
	int HEIGHT,				// #10. ymax entered first time only
	int WINDOW_SIZE,		// #11. entered first time only
	int xmed,				// #12. entered first time only
	int framesize,			// #13. entered first time only
	int index				// #14. entered EVERY FRAME. It must be increased one every call
	)
{
	__global uchar*  im1 = video + index*framesize + 6;
	__global uchar*  im2 = im1 + framesize;

	//10.1. Variable declaration and initial values:
	long k = get_global_id(0);

	int i = k % WIDTH;
	int j = k / WIDTH;

	float G_inv[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	// Guess for optical flow for each iteration 
	// Image mismatch vector. Formula #29
	float G[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float b_k[2] = { 0.0f, 0.0f };


	int wj = -WINDOW_SIZE, wi = -WINDOW_SIZE;

	 
	 
	//10.2. Calculation within the window:
	while (wj <= WINDOW_SIZE)
	{
		// Image difference. Formula #30
		int im2_val = P(im2, (int)(i + wi), (int)(j + wj), WIDTH, HEIGHT);
		int deltaIk = P(im1, i + wi, j + wj, WIDTH, HEIGHT) - im2_val;

		int cIx = Ix_(im1, i + wi, j + wj, WIDTH, HEIGHT);
		int cIy = Iy_(im1, i + wi, j + wj, WIDTH, HEIGHT);

		G[0] += cIx * cIx; G[1] += cIx * cIy;
		G[2] += cIx * cIy; G[3] += cIy * cIy;
		b_k[0] += deltaIk * cIx; b_k[1] += deltaIk * cIy;
		wj = (wi>WINDOW_SIZE) ? (wj + 1) : wj;
		wi = (wi>WINDOW_SIZE) ? -WINDOW_SIZE : (wi + 1);
	}




	//10.3. Calculate of the invert matrix
	get_matrix_inv(G, G_inv);
	// If not invertible, G_inv will stay as 0s

	float fx = 0.0f, fy = 0.0f;

	//10.4 Optical flow. Formula #28
	fx = G_inv[0] * b_k[0] + G_inv[1] * b_k[1];
	fy = G_inv[2] * b_k[0] + G_inv[3] * b_k[1];



	//10.5. Output values using color wheel:



	unsigned char result[3];
	computeColor(fx * FLOW_SCALING_FACTOR, fy * FLOW_SCALING_FACTOR, result);

	out[3 * (j*WIDTH+i)] = (unsigned char)result[0];
	out[3 * (j*WIDTH+i) + 1] = (unsigned char)result[1];
	out[3 * (j*WIDTH+i) + 2] = (unsigned char)result[2];
	if (fabs(fx*fy)>1.0)
	{
		move[k]= fy*coefy[k];
	}
	else move[k]=0.0f;

	//Data concentration 1280 times:
	barrier(CLK_LOCAL_MEM_FENCE); //to give time to all move[k] be filled
	if (k < HEIGHT)
	{
		count1[k] = count2[k] = 0;
		float sum1 = 0.0f, sum2 = 0.0f;
		int ix0 = k*WIDTH;
		short x;
		for (x = 0; x < xmed; x++)
		{
			if (fabs(move[ix0 + x])>DELTA_MOVE)
			{
				sum1 += move[ix0 + x];
				count1[k]++;
			}
		}
		for (; x < WIDTH; x++)
		{
			if (fabs(move[ix0 + x])>DELTA_MOVE)
			{
				sum2 += move[ix0 + x];
				count2[k]++;
			}
		}
		movy1[k] = sum1;
		movy2[k] = sum2;
	}
}










//do not compress mov1,2 and count1,2
__kernel void algoritmo_KNP_UNCOMPRESSED(
	__global uchar*  im1,// #0 FRAME-1
	__global float*  coefx, // #1. coefficients entered first time only
	__global float*  coefy, // #2. coefficients entered first time only
	__global uchar*  out,   // #3 RGB color output sized 3*xmax*ymax
	__global float*  move,  // #4. buffer. No preset needed
	__global float*  movy1, // #5. output reduced data. Array size=ymax
	__global float*  movy2, // #6. output reduced data. Array size=ymax
	__global int*  count1,	// #7. output reduced data. Array size=ymax
	__global int*  count2,	// #8. output reduced data. Array size=ymax
	int WIDTH,				// #9. xmax entered first time only
	int HEIGHT,				// #10. ymax entered first time only
	int WINDOW_SIZE,		// #11. entered first time only
	int xmed,				// #12. entered first time only
	//int framesize,		// #13. entered first time only
	//int index				// #14. entered EVERY FRAME. It must be increased one every call
	__global uchar*  im2	// #13 FRAME-2
	)
{
	//10.1. Variable declaration and initial values:
	long k = get_global_id(0);

	int i = k % WIDTH;
	int j = k / WIDTH;

	float G_inv[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	// Guess for optical flow for each iteration 
	// Image mismatch vector. Formula #29
	float G[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float b_k[2] = { 0.0f, 0.0f };


	int wj = -WINDOW_SIZE, wi = -WINDOW_SIZE;

	 
	 
	//10.2. Calculation within the window:
	while (wj <= WINDOW_SIZE)
	{
		// Image difference. Formula #30
		int im2_val = P(im2, (int)(i + wi), (int)(j + wj), WIDTH, HEIGHT);
		int deltaIk = P(im1, i + wi, j + wj, WIDTH, HEIGHT) - im2_val;

		int cIx = Ix_(im1, i + wi, j + wj, WIDTH, HEIGHT);
		int cIy = Iy_(im1, i + wi, j + wj, WIDTH, HEIGHT);

		G[0] += cIx * cIx; G[1] += cIx * cIy;
		G[2] += cIx * cIy; G[3] += cIy * cIy;
		b_k[0] += deltaIk * cIx; b_k[1] += deltaIk * cIy;
		wj = (wi>WINDOW_SIZE) ? (wj + 1) : wj;
		wi = (wi>WINDOW_SIZE) ? -WINDOW_SIZE : (wi + 1);
	}

	//10.3. Calculate of the invert matrix
	get_matrix_inv(G, G_inv);
	// If not invertible, G_inv will stay as 0s

	float fx = 0.0f, fy = 0.0f;

	//10.4 Optical flow. Formula #28
	fx = G_inv[0] * b_k[0] + G_inv[1] * b_k[1];
	fy = G_inv[2] * b_k[0] + G_inv[3] * b_k[1];

	//10.5. Output values using color wheel:
	unsigned char result[3];
	computeColor(fx * FLOW_SCALING_FACTOR, fy * FLOW_SCALING_FACTOR, result);

	out[3 * (j*WIDTH+i)] = (unsigned char)result[0];
	out[3 * (j*WIDTH+i) + 1] = (unsigned char)result[1];
	out[3 * (j*WIDTH+i) + 2] = (unsigned char)result[2];

	move[k]= fy*coefy[k];

	//Data concentration 1280 times:
	//barrier(CLK_LOCAL_MEM_FENCE); //to give time to all move[k] be filled
	if (fabs(move[k])>DELTA_MOVE)
	{
		if (i < xmed)
		{
			count1[k]=1;
			movy1[k]=move[k];
		}
		else
		{
			count2[k]=1;
			movy2[k]=move[k];
		}
	}
}


//compress in a better manner
__kernel void algoritmo_KNP_COMPRESSED1(
	__global uchar*  im1,// #0 FRAME-1
	__global float*  coefx, // #1. coefficients entered first time only
	__global float*  coefy, // #2. coefficients entered first time only
	__global uchar*  out,   // #3 RGB color output sized 3*xmax*ymax
	__global float*  move,  // #4. buffer. No preset needed
	__global float*  movy1, // #5. output reduced data. Array size=ymax
	__global float*  movy2, // #6. output reduced data. Array size=ymax
	__global int*  count1,	// #7. output reduced data. Array size=ymax
	__global int*  count2,	// #8. output reduced data. Array size=ymax
	int WIDTH,				// #9. xmax entered first time only
	int HEIGHT,				// #10. ymax entered first time only
	int WINDOW_SIZE,		// #11. entered first time only
	int xmed,				// #12. entered first time only
	//int framesize,		// #13. entered first time only
	//int index				// #14. entered EVERY FRAME. It must be increased one every call
	__global uchar*  im2	// #13 FRAME-2
	//add any more global or local variables
	)
{
	//  

}


//ACCIONA code
//COPY of the algorithm BUT using just 2 images!!
__kernel void algoritmo_KNP_COMPRESSED2(
	__global uchar*  im1,// #0 FRAME-1
	__global float*  coefx, // #1. coefficients entered first time only
	__global float*  coefy, // #2. coefficients entered first time only
	__global uchar*  out,   // #3 RGB color output sized 3*xmax*ymax
	__global float*  move,  // #4. buffer. No preset needed
	__global float*  movy1, // #5. output reduced data. Array size=ymax
	__global float*  movy2, // #6. output reduced data. Array size=ymax
	__global int*  count1,	// #7. output reduced data. Array size=ymax
	__global int*  count2,	// #8. output reduced data. Array size=ymax
	int WIDTH,				// #9. xmax entered first time only
	int HEIGHT,				// #10. ymax entered first time only
	int WINDOW_SIZE,		// #11. entered first time only
	int xmed,				// #12. entered first time only   	//int framesize,		// #13. entered first time only 	//int index				// #14. entered EVERY FRAME. It must be increased one every call
	__global uchar*  im2,	// #13 FRAME-2
	__local float* lmov1,	// #14    size=max_local_size*sizeof(float)
	__local float* lmov2,	// #15
	__local int* lcount1,	// #16    size=max_local_size*sizeof(int)
	__local int* lcount2	// #17
	)
{
	//10.1. Variable declaration and initial values:
	long k = get_global_id(0);

	int i = k % WIDTH;
	int j = k / WIDTH;

	float G_inv[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	// Guess for optical flow for each iteration 
	// Image mismatch vector. Formula #29
	float G[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float b_k[2] = { 0.0f, 0.0f };


	int wj = -WINDOW_SIZE, wi = -WINDOW_SIZE;

	 
	 
	//10.2. Calculation within the window:
	while (wj <= WINDOW_SIZE)
	{
		// Image difference. Formula #30
		int im2_val = P(im2, (int)(i + wi), (int)(j + wj), WIDTH, HEIGHT);
		int deltaIk = P(im1, i + wi, j + wj, WIDTH, HEIGHT) - im2_val;

		int cIx = Ix_(im1, i + wi, j + wj, WIDTH, HEIGHT);
		int cIy = Iy_(im1, i + wi, j + wj, WIDTH, HEIGHT);

		G[0] += cIx * cIx; G[1] += cIx * cIy;
		G[2] += cIx * cIy; G[3] += cIy * cIy;
		b_k[0] += deltaIk * cIx; b_k[1] += deltaIk * cIy;
		wj = (wi>WINDOW_SIZE) ? (wj + 1) : wj;
		wi = (wi>WINDOW_SIZE) ? -WINDOW_SIZE : (wi + 1);
	}

	//10.3. Calculate of the invert matrix
	get_matrix_inv(G, G_inv);
	// If not invertible, G_inv will stay as 0s

	float fx = 0.0f, fy = 0.0f;

	//10.4 Optical flow. Formula #28
	fx = G_inv[0] * b_k[0] + G_inv[1] * b_k[1];
	fy = G_inv[2] * b_k[0] + G_inv[3] * b_k[1];

	//10.5. Output values using color wheel:
	unsigned char result[3];
	computeColor(fx * FLOW_SCALING_FACTOR, fy * FLOW_SCALING_FACTOR, result);

	out[3 * (j*WIDTH+i)] = (unsigned char)result[0];
	out[3 * (j*WIDTH+i) + 1] = (unsigned char)result[1];
	out[3 * (j*WIDTH+i) + 2] = (unsigned char)result[2];

	//Calculus of move[]:
	move[k]= fy*coefy[k];

	//Assign move[k] to local arrays lmov1,2 and counting on local arrays lcount1 and 2
	int lik= get_local_id(0);
	int group_size=get_local_size(0);
	lmov1[lik]=lmov2[lik]=0.0f;lcount1[lik]=lcount2[lik]=0;
	if (fabs(move[k])>DELTA_MOVE)
	{
		if (i <xmed)
		{
			lmov1[lik]=move[k];
			lcount1[lik]=1;
		}
		else
		{
			lmov2[lik]=move[k];
			lcount2[lik]=1;
		}
	}
	barrier(CLK_LOCAL_MEM_FENCE); //to give time to all lmov1,2 and lcount1,2 be filled

	//Tree mode data concentration of local arrays lmov1[0..255] to lmov1[0] in 8 steps! (also with lmov2,lcount1 and lcount2):
	for (int med=group_size/2;med>0;med>>=1)
	{
		if (lik<med)
		{
			lmov1[lik]+=lmov1[lik+med];
			lmov2[lik]+=lmov2[lik+med];
			lcount1[lik]+=lcount1[lik+med];
			lcount2[lik]+=lcount2[lik+med];
		}
		barrier(CLK_LOCAL_MEM_FENCE); //to give time to all lmov1,2 and lcount1,2 be added
	}

	//data output accordingly work_group:
	if (lik==0)
	{
		int k2=get_group_id(0);
		movy1[k2]=lmov1[0];
		movy2[k2]=lmov2[0];
		count1[k2]=lcount1[0];
		count2[k2]=lcount2[0];
	}
}
