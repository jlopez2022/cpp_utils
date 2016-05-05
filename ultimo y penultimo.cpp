//Calcula el ultimo y el penultimo de una barrida
#include <stdio.h>
#include <stdlib.h>
#define LONG 5
//saca el menor y el siguiente menor (min1 y min2)
void minimo2(float *f,long f_max,float &min1,float &min2);

void main()
{
	float r[LONG],min1,min2;


	long i,j;
	for (i=0;i<10000;i++)
	{
		for (j=0;j<LONG;j++)
		{
			r[j]=1.0f*LONG*rand()/RAND_MAX;
			printf("%g\t",r[j]);
		}
		minimo2(r,LONG,min1,min2);
		printf(" #%g %g\n",min1,min2);
		for (j=0;j<LONG;j++)
		{
			if (( r[j] < min2) && (r[j]!= min1))
			{
				printf("\n###############  ERROR #################n");
				getchar();
			}
		}
	}
	printf("\nFIN");
	getchar();
}


void minimo2(float *f,long f_max,float &min1,float &min2)
{
	min1=min2=3.4e37f; //FLT_MAX

	long i;
	for (i=0;i<f_max;i++)
	{
		if (min1>f[i])
		{
			if (min2>min1)
				min2=min1;
			min1=f[i];
		}
		else if (min2>f[i])
			min2=f[i];
	}
}
