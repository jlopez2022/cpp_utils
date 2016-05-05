//Escoge los indices de matrices en otro orden
#include <stdio.h>
//FUNCIONA
/*
Sea la matriz:
0 1 2 3 4 5 6

Va cogiendo el punto medio, entonces se obtiene:

3 (que es la mitad de 6) y dos matrices: 0 1 2 y 4 5 6
Hago lo mismo a ambas matrices y obtengo:

3,1,5,...  el caso es que voy buscando la maxima distancia entre puntos

*/
void semialeatorio(long *mat2,long mat_size);


void main()
{
	long mat[15];
	semialeatorio(mat,15);
	long i=1;
}

void semialeatorio(long *mat2,long mat_size)
{
	long *mat1 = new long[mat_size];
	long i,j;
	for (i=0;i<mat_size;i++)
	{
		mat1[i]=i;
	}

	long mat2_index=0;
	for (i=0;i<mat_size;i++)
	{
		long top,div;
		top=1<<i;
		div=2*top;
		if (top>mat_size) 
			break;
		for (j=0;j<top;j++)
		{
			long index=mat_size*(2*j+1)/div;
			if (mat1[index]>=0)
			{
				mat2[mat2_index++]=mat1[index];
				mat1[index]=-1;
			}
		}
	}
	delete mat1;
}
