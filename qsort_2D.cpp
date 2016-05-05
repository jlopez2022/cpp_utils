#include <stdio.h>
#include <stdlib.h>
#define TOP 5000
#define DIM 2

int compara(const void *p1, const void *p2);

int compara(const void *p1,const void *p2)
{
	int *a = (int *) p1;
	int *b = (int *) p2;
	int u=0;
	for (int i=0;i<DIM;i++)
		u=u+(a[i]-b[i]);
	return(u);
}

void main()
{
	int datos[TOP][2];
	long i;

	for (i=0;i<TOP;i++)
	{
		datos[i][0]=(int) (1024*rand()/RAND_MAX);
		datos[i][1]=(int) (1024*rand()/RAND_MAX);
	}

	qsort(datos,TOP,2*sizeof(int),compara);

	FILE *strout;
	strout=fopen("out.txt","w");
	for (i=0;i<TOP;i++)
		fprintf(strout,"\n%i\t%i",datos[i][0],datos[i][1]);
	fclose(strout);
}
