#include <stdio.h>

double pruebastatic(double x)
{
	static double old;
	double x2=old;
	old=x;
	return x2;
}


void main()
{
	int i;
	double x1,x0;
	for (i=0;i<10;i++)
	{
		x1=10.0*i;
		x0=pruebastatic(x1);
		printf("\n%i New:%lg Old:%lg",i,x1,x0);
	}
	getchar();getchar();
}