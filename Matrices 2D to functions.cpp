#include "stdafx.h"
#include <stdlib.h>
#define DIM 3
#define WORMS 50000 //gusanos

void halla_centros_V000(double CENW[][DIM]) 
{
	int w,i;
	for (w=0;w<WORMS;w++)
	{
		for (i=0;i<DIM;i++)
		{
			CENW[w][i]=1000*w+i;
		}
	}
}
void halla_centros_V001(double (*CENW)[DIM])
{
	int w,i;
	for (w=0;w<WORMS;w++)
	{
		for (i=0;i<DIM;i++)
		{
			CENW[w][i]=1000*w+i;
		}
	}
}



int main()
{
	int i;
	double *CENW_MEM=new double[WORMS*DIM];
	double (*CENW)[DIM];
	CENW=(double (*)[3]) &CENW_MEM[0];
	i=1;i=10;
	halla_centros_V000(CENW);
	halla_centros_V000(&CENW[0]);
	halla_centros_V001(CENW);

	delete[] CENW_MEM;
	printf("\n\n===FIN===");getchar();	return 1;
}
