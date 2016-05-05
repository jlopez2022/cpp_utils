#include <stdio.h>
#include <stdlib.h>
#define TOP 10000
#define DIM 1

int compara(const void *p1, const void *p2);


int compara(const void *p1,const void *p2)
{
	int a = (* (int *) p1);
	int b = (* (int *) p2);
/*	int u=0;
	for (int i=0;i<DIM;i++)
		u=u+(a[i]-b[i]);*/
	return(a-b);
}


void main()
{
	int datos[TOP];
	long i;

	for (i=0;i<TOP;i++)
		datos[i]=(int) (1024*rand()/RAND_MAX);

	qsort(datos,TOP,sizeof(int),compara);

	FILE *strout;
	strout=fopen("out.txt","w");
	for (i=0;i<(TOP-1);i++)
	{
		fprintf(strout,"\n%i",datos[i]);
		if (datos[i]>datos[i+1])
		{
			printf("\nError en i=%li",i);
			char c;scanf("%c%c",&c,&c);
		}
	}
	fclose(strout);
}
