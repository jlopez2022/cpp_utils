#include <stdio.h>
#define N1 4 //dimension 1. debe ser >N2
#define N2 3
#define U 0.9999999999

void main()
{
	double K;K=1.0*N1/N2;
	double z1[N1][N1],z2[N2][N2];
	long x1,x2,y1,y2;
	double x1min,x1max;
	double y1min,y1max;


	//Llenado de matriz ejemplo:
	for (y1=0;y1<N1;y1++)
	{
		for (x1=0;x1<N1;x1++)
			z1[y1][x1]=1.0;
	}


	for (y2=0;y2<N2;y2++)
		for (x2=0;x2<N2;x2++)
	{
		double sumz=0.0;
		x1min=K* x2;
		x1max=K* (U+x2);
		y1min=K* y2;
		y1max=K* (U+y2);
		double fx=1.0;
		for (x1=x1min;x1<x1max;x1++)
		{
			if ((x1+1.0-x1min)<1.0) fx=(x1+1.0-x1min);
			else if ((x1max-x1)<1.0 ) fx=(x1max-x1);
			for (y1=y1min;y1<y1max;y1++)
			{
				double fxy=fx;
				if ((y1+1.0-y1min)<1.0) fxy*=(y1+1.0-y1min);
				else if ((y1max-y1)<1.0 ) fxy*=(y1max-y1);
				sumz+=fxy*z1[y1][x1];
			}
		}
		z2[y2][x2]=sumz/K/K;
	}

	for (y2=0;y2<N2;y2++)
	{
		printf("\n");
		for (x2=0;x2<N2;x2++)
			printf("%8f ",z2[y2][x2]);
	}

	char c;scanf("%c%c",&c,&c);
}