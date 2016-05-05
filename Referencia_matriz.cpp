#include <stdio.h>

double prueba_pointer(double mat[],long indice)
{
	return mat[indice];
}

void main()
{
	double mat1[12]={10,11,12,13,14,15,16,17,18,19,20},*mat2=mat1+1;
	double x;
	x=prueba_pointer(mat1,4);
	x=prueba_pointer(mat2,4);
	x=x;
}