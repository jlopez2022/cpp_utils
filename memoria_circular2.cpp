#include <stdio.h>
//#include <conio.h>
//#include <windows.h>
class c_circular
{
public:
	double mat[1024];
	void mete(long i,double x)
	{
		while (i<0) i+=1024;
		i=i%1024;
		mat[i]=x;
	}
	double valor(long i)
	{
		while (i<0) i+=1024;
		i=i%1024;
		return mat[i];
	}
};

int main()
{
	long i2;double x;

	c_circular mem;

	i2=2024 ;mem.mete(i2,2024);x=mem.valor(i2);
	i2=24   ;mem.mete(i2,24);  x=mem.valor(i2);
	i2=-24  ;mem.mete(i2,-24); x=mem.valor(i2);
	i2=-2024;mem.mete(i2,-2024);x=mem.valor(i2);

	char linea[1024]="xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
	char *ptr=linea;
	x=23.51;long l=12300300;
	char simbolo[123]="DW303-1-SW";
	sprintf(linea,"%lg %li %s",x,l,simbolo);
	double x2;long l2;char simbolo2[123];
	sscanf(linea,"%lg %li %s",&x2,&l2,simbolo2);

	x=x;

	return 1;
}