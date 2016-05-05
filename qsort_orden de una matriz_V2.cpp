#include <stdio.h>
#include <stdlib.h>
#define TOP 20 //NO SALE ERROR ni aun subiendo el numero

double  *array_d;//Fundamental para que funcione compara_d. nota: la lista es long PERO array_d es double!!!!!
int compara_d(const void *p1,const void *p2)
{
	long a = (* (long *) p1);//no cambiar el tipo pues la lista es long
	long b = (* (long *) p2);
	if (array_d[a]<array_d[b])	return 1; // ">" si es creciente, "<" si decreciente
	else						return -1;
}

void main()
{
	double data[TOP];
	long i;

	for (i=0;i<TOP;i++)
		data[i]=100.0*rand() / (RAND_MAX+1.0);

	//FUNDAMENTAL poner estas 3 lineas:
	long lista[TOP]; for (i=0;i<TOP;i++) lista[i]=i;
	array_d=data;
	qsort(lista,TOP,sizeof(long),compara_d); //lista es de tipo long

	printf("\nLISTA:");
	long error2=0;double ant=1e199;
	for (i=0;i<TOP;i++)
	{
		double x=data[lista[i]];
		printf("\n%li:%lg",i,x);
		if (ant<x) {printf(" ERROR!!!!");error2++;}
		ant=x;
	}
	printf("\n\n=== NUMERO TOTAL DE ERRORES=%li",error2); 

	printf("\n====FIN====");getchar();getchar();
}