#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void imprimebytes(double y)
{
	long *ptr=(long *) &y;
	printf("%8X%8X_",*(ptr+1),*ptr);
}

//REDONDEO:
__int64 redondeo[52];//Contiene la matriz
void crearedondeo()//rellena la matriz
{
	long i,j;
	__int64 long_max=0xFFFFFFFFFFFFFFFF;
	for (i=0;i<52;i++)
	{
		redondeo[i]=long_max;

		__int64 rotador=1;
		for (j=0;j<i;j++)
		{
			redondeo[i]^=rotador;
			rotador<<=1;
		}
	}
}
double redondea(double valor,double cifras_significativas)//Cifras_sig.=1..16.69
{
	if (cifras_significativas<1.0)
		cifras_significativas=1.0;
	else if (cifras_significativas>16.69)
		cifras_significativas=16.69;
	long digito=(long) (54.25-3.25*cifras_significativas);
	double y=valor;
	__int64 *b=(__int64 *) &y;
	*b=*b&redondeo[digito];
	return y;
}
//=== fin redondeo

int main()
{

	//Redondeo

	long i;
	double valor_max,valor_min;
	long *ptr;

	ptr=(long *) &valor_max;
	*ptr=0xFFFFFFFF;
	ptr++;
	//*ptr=0x7EFFFFFF;
	*ptr=0x7FEFFFFF;
	ptr=(long *) &valor_min;
	*ptr=0xFFFFFFFF;
	ptr++;
//	*ptr=0xFEFFFFFF;
	*ptr=0xFFEFFFFF;
	double epsilon,epsilon_n;
	ptr=(long *) &epsilon;
	*ptr=0x1;
	ptr++;
	*ptr=0x0;
	epsilon_n=-epsilon;
	ptr=(long *) &epsilon_n;
	*ptr=0x1;
	ptr++;
	*ptr=0x80000000;



	//=== creacion de la matriz de redondeo
	crearedondeo();
	//=== fin de creacion

	double x,y;
	ptr=(long *) &x;
	__int64 *ptr2;
	ptr2=(__int64 *) &x;
	x=15.99999999999999;

	y=redondea(x,(long) (53.25-3.25*8));//8 cifras significativas. (Max 16, min 0.30)
	y=(x-y)/x;
	y=redondea(x,(long) (53.25-3.25*4));//4 cifras significativas
	y=(x-y)/x;


	x=15.99999999999999;
	printf("\n00\t%.17lg\t",x);
	imprimebytes(x);
	for (i=0;i<52;i++)
	{
		y=redondea(x,i);
		printf("\n%li\t%.17lg\t",i,y);

		imprimebytes(y);
	}
	printf("\n==========================");

	x=valor_max;
	printf("\n00\t%.17lg\t",x);
	imprimebytes(x);
	for (i=1;i<17;i++)
	{
		y=redondea(x,(double) i);
		printf("\n%li\t%.17lg\t",i,y);

		imprimebytes(y);
	}
	printf("\n==========================");

	printf("\nFIN");getchar();getchar();
	return 1;
}