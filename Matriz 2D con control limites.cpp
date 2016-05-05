//UB() accede a una matriz sin salirse de los limites de la misma
#include <stdio.h>      /* printf */
#define XMAX 5
#define YMAX 4
//UB(image,x,y,W,H) = image[y*W+x] pero comprobando antes que 0<=y<H  0<=x<W
#define UB(image,x,y,W,H) ((image)[( (y)>=H ? H-1 : ((y)<0 ? 0:(y)) )*(W)+( (x)>=W ? W-1 : ((x)<0 ? 0 : (x)) )])


int main ()
{
	double image1[XMAX*YMAX];
	long x,y;
	for (y=0;y<YMAX;y++)
	for (x=0;x<XMAX;x++)
	{
		image1[y*XMAX+x]=100*y+x;
	}

	for (y=0;y<YMAX;y++)
	{
		for (x=0;x<XMAX;x++)
		{
			printf("%5f ",image1[y*XMAX+x]);
		}
		printf("\n");
	}
	printf("\n");
	y=-1;
	for (x=-2;x<6;x++)
	{
		printf("\nxy= %2i %2i UB=%f",x,y,UB(image1,x,y,XMAX,YMAX));
	}
	y=2;
	for (x=-2;x<6;x++)
	{
		printf("\nxy= %2i %2i UB=%f",x,y,UB(image1,x,y,XMAX,YMAX));
	}
	y=6;
	for (x=-2;x<6;x++)
	{
		printf("\nxy= %2i %2i UB=%f",x,y,UB(image1,x,y,XMAX,YMAX));
	}

	printf("\n\nFIN\n");getchar();getchar();
	return 0;
}

