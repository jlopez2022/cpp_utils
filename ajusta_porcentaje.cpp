#include <stdio.h>
#include <stdlib.h>

//Ajusta porcentajes para que la suma sea 1.0

//Entrada de datos=porcen[0..dim-2], siendo porcen[dim-1]=1-suma(porcen[i=0..dim-2])
void ajusta_porcentaje(double *porcen,long dim);


void main()
{
	double porcen[5];
	long i,j,dim=5;
	for(i=0;i<20;i++)
	{
		for (j=0;j<dim;j++)
			porcen[j]=1.0*rand()/RAND_MAX;
		ajusta_porcentaje(porcen,dim);
		printf("\n%3i:",i);
		double suma=0.0;
		for (j=0;j<dim;j++)
		{
			printf("\t%9lg",porcen[j]);
			suma+=porcen[j];
		}
		printf("\t suma=%lg",suma);
	}
	printf("\n=====================\nFIN");
	getchar();getchar();
}

void ajusta_porcentaje(double *porcen,long dim)
{
	long i;
	double suma=0.0;
	for (i=0;i<dim;i++)
	{
		suma+=porcen[i];
	}
	for (i=0;i<dim;i++)
	{
		porcen[i]/=suma;
	}
}
