#include <stdio.h>
//#include <conio.h>
//#include <windows.h>

int main()
{
	char linea[1024]="xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
	char *ptr=linea;
	double x=23.51;long l=12300300;
	char simbolo[123]="DW303-1-SW";
	sprintf(linea,"%lg %li %s",x,l,simbolo);
	double x2;long l2;char simbolo2[123];
	sscanf(linea,"%lg %li %s",&x2,&l2,simbolo2);

	x=x;

	return 1;
}