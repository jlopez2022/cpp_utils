#include <stdio.h>
#define DIM 9

typedef unsigned char uchar;

double convolucion(double *m1,double *m2,long dim)
{
	long i;
	double A=0.0,B=1e-99,C=1e-99;
	for (i=0;i<dim;i++)
	{
		A+=m1[i]*m2[i];
		B+=m1[i]*m1[i];
		C+=m2[i]*m2[i];
	}
	return (A*A/B/C);
}


void main()
{				     //0   1   2   3   4   5   6   7   8   9   
	uchar mat1[DIM+1]={00, 01, 02, 02, 05, 01, 03, 05, 12, 15};
	uchar mat2[DIM+1]={01, 01, 02, 05, 05, 01, 03, 05, 07, 15};
	uchar mat3[DIM+1]={00, 01, 02, 02, 05, 01, 03, 05, 12, 15};
	
	double dm1[DIM],dm2[DIM],dm3[DIM];
	long i;
	for (i=0;i<DIM;i++)
	{
		dm1[i]=mat1[i]-mat1[i+1];
		dm2[i]=mat2[i]-mat2[i+1];
		dm3[i]=mat3[i]-mat3[i+1];
	}

	double z;
	z=convolucion(dm1,dm2,DIM);
	printf("\nZ=%lg",z);
	z=convolucion(dm1,dm3,DIM);
	printf("\nZ=%lg",z);
	for (i=0;i<10;i++)
	{
		dm3[DIM-1]++;
		z=convolucion(dm1,dm3,DIM);
		printf("\nZ=%lg",z);
	}
	char c;
	scanf("%c%c",&c,&c);
}

