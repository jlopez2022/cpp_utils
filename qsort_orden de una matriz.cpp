#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define TOP 10
/*
Da el orden de una matriz x1[] de menor a mayor y lo pone en lista[]
sea:

x1[0]=7
x1[1]=3
x1[2]=1
x1[3]=2

Entonces lista[]=2,3,1,0
*/
double *compara_ord_x;//Variable global imprescindible
int compara_ord_increasing(const void *p1,const void *p2)
{
	long a = (* (long *) p1);
	long b = (* (long *) p2);
	if (compara_ord_x[a] < compara_ord_x[b])
		return(-1);
	else
		return(1);
}
int compara_ord_decreasing(const void *p1,const void *p2)
{
	long a = (* (long *) p1);
	long b = (* (long *) p2);
	if (compara_ord_x[a] > compara_ord_x[b])
		return(-1);
	else
		return(1);
}
//Genera una lista[i] de la matriz x1 en forma creciente
void ordena_increasing(double *x1,long *lista,long size)
{
	compara_ord_x=x1;
	long i;
	for (i=0;i<size;i++)
		lista[i]=i;
	qsort(lista,size,sizeof(long *),compara_ord_increasing);
}
void ordena_decreasing(double *x1,long *lista,long size)
{
	compara_ord_x=x1;
	long i;
	for (i=0;i<size;i++)
		lista[i]=i;
	qsort(lista,size,sizeof(long *),compara_ord_decreasing);
}


void main()
{
	double datos[TOP]={12.3,5,10,8,11,13,2.2, 3,12.1,7};
	long lista[TOP];
	printf("\nIncreasing");
	ordena_increasing(datos,lista,TOP);
	long i;
	for (i=0;i<TOP;i++)
	{
		printf("\n%3i:%lg",lista[i],datos[lista[i]]);
	}
	printf("\n\nDecreasing");
	ordena_decreasing(datos,lista,TOP);
	for (i=0;i<TOP;i++)
	{
		printf("\n%3i:%lg",lista[i],datos[lista[i]]);
	}

	printf("\n\n===FIN===");getchar();

}
