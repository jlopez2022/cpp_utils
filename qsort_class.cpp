#include <stdio.h>
#include <stdlib.h>
#define TOP 6
#define DIM 1

class wptc
{
public:
	long valor;
	char cc;
};

int compara(const void *p1, const void *p2);


int compara(const void *p1,const void *p2)
{
	wptc *a = (* (wptc **) p1);
	wptc *b = (* (wptc **) p2);
	if (a->valor < b->valor)
		return(-1);
	else
		return(1);
}


void main()
{
	int datos[TOP]={4688,4692,4700,4690,4695,4705};
	long i;

	wptc wpt[TOP];
	wptc **listaw;
	listaw=new wptc *[TOP];

	for (i=0;i<TOP;i++)
	{
		wpt[i].valor=datos[i];
		listaw[i]=wpt+i;
	}

	qsort(listaw,TOP,sizeof(wptc *),compara);

	FILE *strout;
	strout=fopen("out.txt","w");
	for (i=0;i<(TOP-1);i++)
	{
		fprintf(strout,"\n%i",listaw[i]->valor);
		if (listaw[i]->valor>listaw[i+1]->valor)
		{
			printf("\nError en i=%li",i);
			char c;scanf("%c%c",&c,&c);
		}
	}
	fprintf(strout,"\n%i",wpt[i].valor);
	fclose(strout);
}
