#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void imprimebytes(double y)
{
	long *ptr=(long *) &y;
	printf("%8X%8X_",*(ptr+1),*ptr);
}

//REDONDEO:
long redondeo[52][2];//Contiene la matriz
void crearedondeo()//rellena la matriz
{
	long i,j,long_max=0xFFFFFFFF;
	for (i=0;i<52;i++)
	{
		redondeo[i][0]=redondeo[i][1]=long_max;

		long rotador=1;
		for (j=0;j<i;j++)
		{
			redondeo[i][0]^=rotador;
			rotador<<=1;
		}
		rotador=1;
		for (j=32;j<i;j++)
		{
			redondeo[i][1]^=rotador;
			rotador<<=1;
		}
		i=i;
	}
}
double redondea(double valor,long digito)//Usa la matriz. Max digito=51
{
	if (digito>51) digito=51;
	double y=valor;
	long *b=(long *) &y;
	b[0]=b[0]&redondeo[digito][0];
	b[1]=b[1]&redondeo[digito][1];//Solo es necesario dos operaciones
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


	double x=valor_max,y;

	printf("\n00\t%.17lg\t",x);
	imprimebytes(x);
	for (i=0;i<52;i++)
	{
		y=redondea(x,i);
		printf("\n%li\t%.17lg\t",i,y);

		imprimebytes(y);
	}
	printf("\n==========================");
	for (i=0;i<52;i++)
	{
		y=redondea(-x,i);
		printf("\n%li\t%.17lg\t",i,y);

		imprimebytes(y);
	}
	printf("\n==========================");
	double valor2;
	ptr=(long *) &valor2;
	*ptr=0xFFFFFFFF;
	ptr++;
	*ptr=0x1FFFFF;
	for (i=0;i<52;i++)
	{
		y=redondea(valor2,i);
		printf("\n%li\t%.17lg\t",i,y);

		imprimebytes(y);
	}
	printf("\n==========================");
	for (i=0;i<52;i++)
	{
		y=redondea(-valor2,i);
		printf("\n%li\t%.17lg\t",i,y);

		imprimebytes(y);
	}
	printf("\n==========================");

	printf("\nFIN");getchar();getchar();
	return 1;
}