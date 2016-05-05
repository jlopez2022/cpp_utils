#include <stdio.h>
#include <math.h>
#include <string.h>
#define XMAX 3
#define YMAX 200
#define PI2 6.283185307179586476925286766559

void similaridad(double *mat,long YMAX1,long XMAX1,double *simil);

int main()
{
	FILE *strout=fopen("out.xls","w");
	if (!strout)
	{
		printf("Error out.xls");getchar();getchar();return 0;
	}
	double matriz[XMAX*YMAX];
	double dep[XMAX][XMAX]=
	{
		1.0,1.0,1.0,
		0.0,1.0,1.0,
		1.0,2.0,1.0
	};

	long x,y,x2;
	for (y=0;y<YMAX;y++)
	{
		for (x=0;x<XMAX;x++)
		{
			double r;
			r=dep[x][x]*sin((1.0+x)*PI2*y/YMAX);
			for (x2=0;x2<x;x2++)
			{
				r+=dep[x][x2]*matriz[y*XMAX+x2];
			}
			matriz[y*XMAX+x]=r;
			fprintf(strout,"%lg\t",r);
		}
		fprintf(strout,"\n");
	}

	double simil[XMAX*XMAX];
	similaridad(matriz,YMAX,XMAX,simil);
	fprintf(strout,"\n=========resultado=========");
	for (y=0;y<XMAX;y++)
	{
		fprintf(strout,"\n");
		for (x=0;x<XMAX;x++)
		{
			fprintf(strout,"%lg\t",simil[y*XMAX+x]);
		}
	}

	fclose(strout);
	return 1;
}


void similaridad(double *mat,long YMAX1,long XMAX1,double *simil)
{
	//mat[YMAX1*XMAX1] y simil[XMAX1*XMAX1], siendo simil[i,j]=simil[j,i]
	long x,y,x2,xmax2;
	xmax2=XMAX1*(XMAX1-1)/2;
	double *cuad=new double[XMAX1];//contiene suma de cuadrados Sxx
	double *cruz=new double[xmax2];//contiene suma de productos cruzados Sxy
	memset(cuad,0,XMAX1*sizeof(double));
	memset(cruz,0,xmax2*sizeof(double));
	for (y=1;y<YMAX1;y++)
	{
		long index=0;
		for (x=0;x<XMAX1;x++)
		{
			double r;
			r=mat[y*XMAX1+x]-mat[y*XMAX1+x-XMAX1];
			cuad[x]+=r*r;
			for (x2=0;x2<x;x2++)
			{
				double s;
				s=mat[y*XMAX1+x2]-mat[y*XMAX1+x2-XMAX1];
				cruz[index++]+=r*s;
			}
		}
	}
	long index=0;
	for (y=0;y<XMAX1;y++)
	{
		simil[y*XMAX1+y]=1.0;
		for (x=0;x<y;x++)
		{
			simil[y*XMAX1+x]=simil[x*XMAX1+y]=fabs(cruz[index++])/sqrt(cuad[x]*cuad[y]+1e-150);
		}
	}
	delete[] cuad,cruz;
}