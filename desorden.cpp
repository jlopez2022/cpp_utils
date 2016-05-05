#include <stdio.h>
#include <stdlib.h>
#define TOP 4

int compara(const void *p1,const void *p2)
{
	double *a = (* (double **) p1);
	double *b = (* (double **) p2);
	int u=1;
	if (*a<*b) u=-1;
	return u;
}

double halla_desorden(double *datoin,double *datout,long size)
{
	double **ordin,**ordout;
	ordin= new double *[size];
	ordout=new double *[size];

	long i;
	for (i=0;i<size;i++)
	{
		ordin[i] =datoin+i;
		ordout[i]=datout+i;
	}

	qsort(ordin ,size,sizeof(double *),compara);
	qsort(ordout,size,sizeof(double *),compara);
	long k;
	k=datoin-datout;
	double x,suma=0.0;
	for (i=0;i<size;i++)
	{
		x=ordout[i]-ordin[i]+k;
		suma+=x*x;
	}
	suma/=size;
	delete[] ordin,ordout;
	return suma;
}

void main()
{
//	double datoin[TOP]={5,3,12,2,103,4 ,9,103,107,17, 23,19,102};
//	double datout[TOP]={5,3,12,2,103,17,4,9  ,103,107,23,19,102};
	double datoin[TOP]={3,12,9,5};
	double datout[TOP]={5,3,12,9};

	double desorden;
	desorden=halla_desorden(datoin,datout,TOP);

	printf("\nDesorden=%lg",desorden);
	char c;scanf("%c%c",&c,&c);
}
