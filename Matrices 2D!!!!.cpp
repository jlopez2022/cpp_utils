#include <stdio.h>
#include <stdlib.h>
#define DIM2 3
#define DIM1 500 

void funcion1(double MAT[][DIM2]) 
{
	int i,j;
	for (i=0;i<DIM1;i++)
	{
		for (j=0;j<DIM2;j++)
		{
			MAT[i][j]=1000*i+j;
		}
	}
}
void funcion2(double (*MAT)[DIM2])
{
	int i,j;
	for (i=0;i<DIM1;i++)
	{
		for (j=0;j<DIM2;j++)
		{
			MAT[i][j]=1000*i+j;
		}
	}
}



int main()
{
	int i,j;
	double *ARRAY2D_M=new double[DIM1*DIM2]; double (*ARRAY2D)[DIM2]; //created using 2 commands
	ARRAY2D=(double (*)[DIM2]) &ARRAY2D_M[0];
	i=1;i=10;
	funcion1(ARRAY2D);
	funcion1(&ARRAY2D[0]);
	funcion1(ARRAY2D);

	delete[] ARRAY2D_M; //deleted in one command
	printf("\n\n===FIN===");getchar();	return 1;
}
