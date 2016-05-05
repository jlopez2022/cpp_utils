#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TOP 11


int compara_decreciente(const void *p1,const void *p2)
{
	double a = (* (double *) p1); double b = (* (double *) p2); 	if (a<b) return 1; 	else return -1;
}

int compara_creciente(const void *p1,const void *p2)
{
	double a = (* (double *) p1); double b = (* (double *) p2); 	if (a>b) return 1; 	else return -1;
}


void main()
{
	double x1[TOP]={ 10, 20.2, 20.1, 15, 3, 2.0, 1e30, 43.3, -7.0, 14.2, 11.0};
	double x2[TOP]={ 10, 20.2, 20.1, 15, 3, 2.0, 1e30, 43.3, -7.0, 14.2, 11.0};

	printf("\nUsa compara decreciente:");
	qsort(x1,TOP,sizeof(double),compara_decreciente);
	for (long i=0;i<TOP;i++)
		printf("\n%lg",x1[i]);

	printf("\n\nUsa compara creciente:");
	qsort(x2,TOP,sizeof(double),compara_creciente);
	for (long i=0;i<TOP;i++)
		printf("\n%lg",x2[i]);
	char c;scanf("%c%c",&c,&c);
}

