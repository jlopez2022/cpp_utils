//Ordeno una estructura de cualquier tipo y tamaño usando una lista!!!
#include <stdio.h>
#include <string.h>//memcpy
#include <stdlib.h>//rand
#include <math.h>//sqrt
#define YMAX 40
#define XMAX 5


double *error_d;
int compara_d(const void *p1,const void *p2)
{
	long a = (* (long *) p1);
	long b = (* (long *) p2);
	if (error_d[a]<error_d[b]) return 1; // ">" si es creciente, "<" si decreciente
	else       return -1;
}

void main()
{
	double datos[YMAX][XMAX];
	double error[YMAX];
	srand(0);

	//relleno datos aleatoriamente
	long x,y;
	double xmed=0.0,xx;
	for (y=0;y<YMAX;y++)
		for (x=0;x<XMAX;x++)
		{
			xx=(100.0+x)+(rand() % 256); //datos aleatorios
			datos[y][x]=xx;xmed+=xx;
		}
	xmed=1.0*xmed/XMAX*YMAX;
	//hallo el error
	for (y=0;y<YMAX;y++)
	{
		error[y]=0;
		for (x=0;x<XMAX;x++)
		{
			xx=xmed-datos[y][x];
			error[y]+=xx*xx;
		}
		error[y]=sqrt(error[y]/XMAX);
	}


	printf("\nLISTA:");

	//ZONA DE ORDENACION:
	long lista[YMAX];//lista que contiene el orden
	long i;for (i=0;i<YMAX;i++) lista[i]=i;//relleno lista[]
	error_d=error;//digo donde esta el error. error_d debe ser del mismo tipo que error (double,long o lo que sea)
	qsort(lista,YMAX,sizeof(long),compara_d);//ordeno la lista cuyos indices son long  

	printf("\n\nLISTA ordenada:\n");
	double ant=1e199,e;
	long error2=0;
	for (y=0;y<YMAX;y++)
	{
		for (x=0;x<XMAX;x++) printf(" %15lg",datos[lista[y]][x]);
		e=error[lista[y]];printf(" error=%lg",e);
		if (e>ant) {printf(" ERROR!!!!\n");error2++;}
		else printf("\n");
		ant=e;
	}
	printf("\n=== NUMERO TOTAL DE ERRORES=%li",error2); 

	//Ahora copio ordenadamente datos[] en datos2[]:
	double datos2[YMAX][XMAX];
	for (y=0;y<YMAX;y++)
		memcpy(datos2[y],datos[lista[y]],XMAX*sizeof(double));//copio los bloques de tamaño XMAX de golpe en datos2
	//Y ahora copio de golpe datos2[] en datos[]
	memcpy(datos,datos2,YMAX*XMAX*sizeof(double));

	printf("\n\nMatriz completa reordenada:\n");
	ant=1e199;error2=0;
	for (y=0;y<YMAX;y++)
	{
		double error1=0;
		for (x=0;x<XMAX;x++)
		{
			xx=xmed-datos[y][x];
			error1+=xx*xx;
		}
		for (x=0;x<XMAX;x++) printf(" %15lg",datos[y][x]);
		e=sqrt(error1/XMAX);printf(" error=%lg",e);
		if (e>ant) {printf(" ERROR!!!!\n");error2++;}
		else printf("\n");
		ant=e;
	}
	printf("\n=== NUMERO TOTAL DE ERRORES=%li",error2); 


	printf("\n\n====FIN====");getchar();getchar();
}