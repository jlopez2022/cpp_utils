#include <stdio.h>
#include <stdlib.h>

void main()
{
	double *f[100],mat[100],*(*g);
	long i;
	g=new double *[100];

	for (i=0;i<100;i++)
		mat[i]=10000.0+i;

	for (i=0;i<10;i++)
	{
		f[i]=&mat[i+10];
		g[i]=&mat[i+20];
	}

	i=0;
}
