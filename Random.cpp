#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void aleatorio(long *mat,long matlong)
{
	long i,k,index;
	for (i=matlong-1;i>0;i--)
	{
		index=(long) (i*rand()/RAND_MAX);
		k=mat[i];mat[i]=mat[index];mat[index]=k;
	}
}

void f_log2(float *matf,long matflong)
{
	matf[0]=-1e35f;
	double log2=log(2.0);
	for (long i=1;i<matflong;i++)
		matf[i]=(float) (log(i)/log2);
}

void main()
{
	long i,j;
	long *mat;
	long matlong=16;

	mat=new long[matlong];

	for(j=0;j<100;j++)
	{
		for (i=0;i<matlong;i++)
		{
			mat[i]=i;
		}
		aleatorio(mat,matlong);
		for (i=0;i<matlong;i++)
			printf("%3i",mat[i]);
		printf("\n");
	}

	float matf[65536];
	f_log2(matf,65536);

	i=1;

	delete[] mat;
	getchar();getchar();
}