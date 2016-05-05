#include <stdlib.h>
#include <stdio.h>
typedef unsigned char byte;

//muestras[0..nummuestras]= 0..maxmuestras.
//La matriz muestras debe estar dimensionada ANTES
void aleatorio(long *muestras,long nummuestras,long maxmuestras);
//bgr_in[0..pixelin*3] , bgr_out[0..pixelout] (dimensionados ANTES)
void aleabin_3d(byte *bgrin,long pixelin,byte *bgrout,long pixelout);
//mat_in[0..pixelin*3] , mat_out[0..pixelout] (dimensionados ANTES)
void aleabin_nd(byte  *matin,long pixelin,byte  *matout,long pixelout,int dim);
void aleabin_nd(short *matin,long pixelin,short *matout,long pixelout,int dim);


void aleatorio(long *muestras,long nummuestras,long maxmuestras)
{
	//muestras=new long[nummuestras];
	//srand(202);
	long delta=maxmuestras/nummuestras;
	long i;
	for (i=0;i<nummuestras;i++)
	{
		long val;
		val=i*delta+ (long) (delta*rand()/RAND_MAX);
		muestras[i]=val;
	}
}

//bgr_in[0..pixelin*3] , bgr_out[0..pixelout] (dimensionados ANTES)
void aleabin_3d(byte *bgrin,long pixelin,byte *bgrout,long pixelout)
{
	long *muestras,nummuestras=pixelout,maxmuestras=pixelin;
	muestras=new long[nummuestras];
	aleatorio(muestras,nummuestras,maxmuestras);
	long i;
	byte *ptrout=bgrout;
	for (i=0;i<pixelout;i++)
	{
		long j;
		j=muestras[i]*3;
		byte *ptrin=bgrin+j;
		*ptrout++=*ptrin++;
		*ptrout++=*ptrin++;
		*ptrout++=*ptrin;
	}
	delete[] muestras;
}

//mat_in[0..pixelin*3] , mat_out[0..pixelout] (dimensionados ANTES)
void aleabin_nd(byte *bgrin,long pixelin,byte *bgrout,long pixelout,int dim)
{
	long *muestras,nummuestras=pixelout,maxmuestras=pixelin;
	muestras=new long[nummuestras];
	aleatorio(muestras,nummuestras,maxmuestras);
	long i;
	byte *ptrout=bgrout;
	for (i=0;i<pixelout;i++)
	{
		byte *ptrin=bgrin+muestras[i]*dim;
		for (int j=0;j<dim;j++)
			*ptrout++=*ptrin++;
	}
	delete[] muestras;
}

//mat_in[0..pixelin*3] , mat_out[0..pixelout] (dimensionados ANTES)
void aleabin_nd(short *matin,long pixelin,short *matout,long pixelout,int dim)
{
	long *muestras,nummuestras=pixelout,maxmuestras=pixelin;
	muestras=new long[nummuestras];
	aleatorio(muestras,nummuestras,maxmuestras);
	long i;
	short *ptrout=matout;
	for (i=0;i<pixelout;i++)
	{
		long kk;
		kk=muestras[i]*dim;
		short *ptrin=matin+kk;
		for (int j=0;j<dim;j++)
			*ptrout++=*ptrin++;
	}
	delete[] muestras;
}
