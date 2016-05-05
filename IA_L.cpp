#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define VARMAX 20//Maximo numero de variables



double C[VARMAX]={0.81519,0.1799,-0.1501,0.089111,-0.01,0,0.0111111,0.10567687654,0.1991319,-0.012345};
double funcion1(double *x,int size)
{
	double y=0;
	int i;
	for (i=0;i<size;i++)
		y+=fabs(x[i]-C[i]);
	return y;
}

double C2[VARMAX];
double funcion2(double *x,int size)
{
	double y=0;
	int i;
	for (i=0;i<size;i++)
		y+=fabs(x[i]-C2[i]);
	return y;
}

double C3[VARMAX];
double funcion3(double *x,int size)
{
	double y=0;
	int i;
	for (i=0;i<size;i++)
		y+=fabs(x[i]-C3[i]);
	return y;
}



//veces=veces que se divide por dos el delta
//Coeficiente=valor por el que se divide DELTA
void F_L(double *COEF,double *DELTA0,int size,int veces,double (*funcion)(double *,int),double coef_reduccion=0.6)
{
	double z1,z0;
	double DELTA[VARMAX];
	memcpy(DELTA,DELTA0,size*sizeof(double));
	int v,x;
	for (x=0;x<size;x++)
		COEF[x]=COEF[x]+0.5*DELTA[x];
	z0=funcion(COEF,size);

	for (v=0;v<veces;v++)
	{
		if (v&1) //11 si impar
		for (x=0;x<size;x++)
		{
			double coef0=COEF[x];
			COEF[x]=COEF[x]+DELTA[x];
			z1=funcion(COEF,size);
			if (z0<z1)
				COEF[x]=coef0;
			else
				z0=z1;
			DELTA[x]*=coef_reduccion;
		}
		else
		for (x=0;x<size;x++)
		{
			double coef0=COEF[x];
			COEF[x]=COEF[x]-DELTA[x];
			z1=funcion(COEF,size);
			if (z0<z1)
				COEF[x]=coef0;
			else
				z0=z1;
			DELTA[x]*=coef_reduccion;
		}
	}
}


void main()
{
	int size=20;
	double COEF[VARMAX], DELTA[VARMAX]={0.5,0.4},COEF0[VARMAX]={1,0};
	int i;
	for (i=0;i<size;i++)
	{
		if (i>0)
			{	COEF0[i]=0.0;DELTA[i]=0.4;}
		C2[i]=COEF0[i]+DELTA[i]*(rand()-RAND_MAX*0.5)/RAND_MAX;
		C3[i]=COEF0[i]+DELTA[i]*(rand()-RAND_MAX*0.5)/RAND_MAX;
	}
	double x,y,y1,y2=0,y3=0;
	for (x=0.49;x<0.65;x+=0.001)
	{
		memcpy(COEF,COEF0,size*sizeof(double));
		F_L(COEF,DELTA,size,25,&funcion1,x);
		y=y1=funcion1(COEF,size);

		memcpy(COEF,COEF0,size*sizeof(double));
		F_L(COEF,DELTA,size,25,&funcion2,x);
		y2=funcion2(COEF,size);

		memcpy(COEF,COEF0,size*sizeof(double));
		F_L(COEF,DELTA,size,25,&funcion3,x);
		y3=funcion3(COEF,size);

		y+=(y2+y3);
		printf("\n%lg\t%lg\t%lg   \t%lg\t%lg",x,y,y1,y2,y3);
	}
	getchar();getchar();
	x=x;
}