//Prueba de paso de clases con datos de una funcion a otra usando punteros.

#include <stdio.h>

class c_prue
{
public:
	char a[1500];
	double x[18000];
	double y[18000];

	void rellena(double a,double b,double a2,double b2);
	int compara(double *x1,double *y1,char *a1);
};

void c_prue::rellena(double a1,double b1,double a2,double b2)
{
	int i;
	for (i=0;i<18000;i++)
	{
		x[i]=a1+b1*i;
		y[i]=a2+b2*i;
		if (i<1500)
			a[i]=(char) i;
	}
}

int c_prue::compara(double *x1,double *y1,char *a1)
{
	int i,r1=-1;

	for (i=0;i<18000;i++)
	{
		if (x1[i]!=x[i])
			return i+1; //nok
		if (y1[i]!=y[i])
			return i+1; //nok
		if ((i<1500)&&(a[i]!=a1[i]))
			return i+1; //nok
	}
	return -777;//ok
}

int comparaclases(char *mem1,char *mem2)
{

	c_prue *prue1;
	c_prue *prue2;

	prue1=(c_prue *) mem1;
	prue2=(c_prue *) mem2;

	int ii;
	ii=prue2->compara(prue1->x,prue1->y,prue1->a);
	return ii;
}

void main()
{
	char *mem1,*mem2;
	int memsize;
	memsize=sizeof(c_prue);
	mem1=new char[memsize];
	mem2=new char[memsize];

	c_prue *prue1;
	c_prue *prue2;

	prue1=(c_prue *) mem1;
	prue2=(c_prue *) mem2;
	prue1->rellena(1.1,2.2,-5.3,0.99);
	prue2->rellena(1.1,2.2,-5.3,0.99);

	int ii;
	ii=prue2->compara(prue1->x,prue1->y,prue1->a);
	ii=ii;

	ii=comparaclases(mem1,mem2);
	ii=ii;


	delete[] mem1,mem2;
}