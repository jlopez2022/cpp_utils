#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLON 10000

void leelin(FILE *strin,char *lin)
{
	char c;
	while(!feof(strin))
	{
		c=fgetc(strin);
		if (c==0x0A)
			break;
		if (c!=0x0D)
			*lin++=c;
	}
	*lin='\0';
}

void leetabla(FILE *str,double *x,double *y,long *xy_size)
{
	char linea[1024],*ptr;
	leelin(str,linea);


	long i;
	for(i=0;i<MAXLON;i++)
	{
		leelin(str,linea);
		if (strlen(linea)<3)
			break;
		ptr=linea;
		while (*ptr)
		{
			if (*ptr==',')
				*ptr='.';
			ptr++;
		}
		ptr=linea;
		x[i]=strtod(ptr,&ptr);
		y[i]=strtod(ptr+1,&ptr);
		if (feof(str))
			break;
	}
	*xy_size=i;
}

void buscaY(double *x,double *y,long xy_size,double &xx,double &yy)
{
	double x0,x1,y0,y1;
	long i;
	x1=x[0];y1=y[0];
	for (i=1;i<xy_size;i++)
	{
		x0=x1;y0=y1;
		x1=x[i];y1=y[i];
		if ((x0<=x1)&&(xx<=x1))
			break;
		if ((x0>=x1)&&(xx>=x1))
			break;
	}
	yy=y0+(y1-y0)/(x1-x0+1e-99)*(xx-x0);
}

void buscaX(double *x,double *y,long xy_size,double &xx,double &yy)
{
	double zz;
	buscaY(y,x,xy_size,yy,xx);
}


void main()
{
	double x[MAXLON],y[MAXLON];
	long xy_size;
	FILE *str=fopen("tabla.txt","r");
	if (!str)
	{
		printf("\nNO ENCUENTRO tabla.txt");getchar();getchar();
		return;
	}
	leetabla(str,x,y,&xy_size);

	double xx,yy;
	xx=3;			buscaY(x,y,xy_size,xx,yy);
	xx=0;buscaX(x,y,xy_size,xx,yy);
	xx=1.8652625;	buscaY(x,y,xy_size,xx,yy);
	xx=0;buscaX(x,y,xy_size,xx,yy);
	xx=2;			buscaY(x,y,xy_size,xx,yy);
	xx=0;buscaX(x,y,xy_size,xx,yy);
}


