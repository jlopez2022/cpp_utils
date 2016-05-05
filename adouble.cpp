#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//No necesarios:
#include <locale.h>
#include <sstream> 

//sustituye a strtod() pero no tiene en cuenta si es coma o punto decimal
double adouble(char *lin,char **ptr);

void main()
{
	lconv *localptr;
	localptr=localeconv();
	char tipoant,*ptr;
	tipoant=*localptr->decimal_point;

	double x;
	char linea1[]="17.23 gg",linea2[]="17,23 gg";
	x=adouble(linea2,&ptr);
	printf("\n%s > %g",linea2,x);
	x=adouble(linea1,&ptr);
	printf("\n%s > %g",linea1,x);

	printf("\n=====================\nFIN");
	getchar();getchar();
}


double adouble(char *lin,char **ptr)
{
	double x;
	x=strtod(lin,ptr);
//	if ((**ptr=='.')||(**ptr==','))
	if (**ptr==',')
	{
		**ptr='.';
	}
	x=strtod(lin,ptr);
	return x;
}
