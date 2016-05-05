#include <stdio.h>
#include <stdlib.h>

/*
void aleatorio(long *matriz,long longitud)
{
	long *mat=new long[longitud];

//	long *ptr=mat;
	for (long i=0;i<longitud;i++) //*ptr++=i;//relleno la matriz mat[]=0,1,2...
		mat[i]=i;

	long x;
	for (;longitud>0;)
	{
		x=(long) (0.0+longitud*rand()/RAND_MAX);
		matriz[--longitud]=mat[x];
		mat[x]=mat[longitud];
	}
	delete[] mat;
}
*/

void aleatorio(long *matriz,long longitud)
{
	for (long i=0;i<longitud;i++) //*ptr++=i;//relleno la matriz mat[]=0,1,2...
		matriz[i]=i;

	long x,dat;
	for (;longitud>1;)
	{
		longitud--;
		x=(long) (1.0*longitud*rand()/RAND_MAX);
		dat=matriz[longitud];
		matriz[longitud]=matriz[x];
		matriz[x]=dat;
	}
}


#define MAX 3954999  //39549

int compara(const void *p1,const void *p2)
{
	long a = (* (long *) p1);
	long b = (* (long *) p2);
/*	int u=0;
	for (int i=0;i<DIM;i++)
		u=u+(a[i]-b[i]);*/
	return(a-b);
}


void main()
{
	long *matriz=new long[MAX];
	long i;
	aleatorio(matriz,MAX);
/*	FILE *pru=fopen("prue.txt","w");
	for (i=0;i<MAX;i++)
	fclose(pru);*/
	qsort(matriz,MAX,sizeof(long),compara);
	for (i=0;i<MAX;i++)
		if (i!=matriz[i])
			printf("\nError en linea %li",i);
	char c;scanf("%c%c",&c,&c);
}
