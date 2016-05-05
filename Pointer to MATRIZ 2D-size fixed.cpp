#include <stdio.h>
#define XMAX 100
#define YMAX 50

long i_mat[2*YMAX][2*XMAX-1];//Debiera ser [2*YMAX-1] pero se suma uno pues no caben mitades
//Usar como mat[y][x] siendo y=-YMAX+1 a YMAX-1 y x=-XMAX+1 a XMAX-1
long (*mat)[2*XMAX-1]=i_mat + YMAX;


void main()
{
	long i,j,x,y;

	long *ptr,*ptr2;
	ptr= &i_mat[2*YMAX-1][2*XMAX-2];//top
	ptr2=  &mat[YMAX-1][XMAX-1];//top
	ptr= &i_mat[0][0];//top
	ptr2=  &mat[-YMAX+1][-XMAX+1];//bottom

	for (x=-XMAX+1;x<XMAX;x++)
		for (y=-YMAX+1;y<YMAX;y++)
			mat[y][x]=y*10000+x;
	for (x=-XMAX+1;x<XMAX;x++)
		for (y=-YMAX+1;y<YMAX;y++)
			if(mat[y][x]!=y*10000+x)
			{
				printf("\nERROR");getchar();getchar();
			}
}