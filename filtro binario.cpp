#include <stdio.h>
#include <stdlib.h> //rand
#include <math.h> //fabs

#define FILTRO(u,bit) (  (u[bit/8]>>(bit % 8)) & 1  ) //Filtro empleando con un define!!

typedef unsigned long ulong;
typedef unsigned char uchar;
//filtro hasta 32 bits:
int filtro(ulong u,int posicion);
//filtro de 8xn bits (tantos bytes como se quiera)
int filtro(uchar *u,int posicion);
//Aplica el filtro a dos números double, siendo a,b los dos arrays double, filtro1 el filtro y s_filtro el tamaño en bits del mismo:
double aplica_filtro(double *a,double *b,uchar *filtro1,int s_filtro1);
//Halla la distancia entre dos vectores double, siendo a,b los dos vectores, filtro1 el filtro y s_filtro el tamaño en bits del mismo, que es el numero de dimensiones:
double halla_distancia(double *a,double *b,uchar *filtro1,int s_filtro1);


int main()
{
	ulong u;
	int j;
	u=0xC128F126LU;
	printf("\ni=0x%08X Empleo filtro de hasta 32 bits:\n",u);
	for (j=31;j>=0;j--) 	{ 		printf("%i",filtro(u,j)); if (j%8==0) printf(" "); 	}

	printf("\n\ni=0x");
	//     byte:   0    1    2    3   :Se meten en orden inverso
	uchar b[4]={0x26,0xF1,0x28,0xC1}; //= 0xC128F126
	for (j=3;j>=0;j--) printf("%02X",b[j]);
	printf(" Empleo filtro de numero de bytes arbitrario:\n");
	for (j=31;j>=0;j--) 	{ 		printf("%i",filtro(b,j)); if (j%8==0) printf(" "); 	}
	printf("\n");
	for (j=31;j>=0;j--) 	{ 		printf("%i",FILTRO(b,j)); if (j%8==0) printf(" "); 	}

	//Aplico el filtro binario a dos arrays double:
	double x[40],y[40];
	for (j=0;j<40;j++)
	{
		x[j]=(double) (rand()/RAND_MAX);
		y[j]=(double) (rand()/RAND_MAX);
	}
	uchar filtro1[4]={0x26,0xF1,0x28,0xC1}; //= 0xC128F126
	double xx;
	xx=aplica_filtro(  x,y,filtro1,40);
	xx=halla_distancia(x,y,filtro1,40);
	x[38]=3.2;x[39]=2.2;
	y[38]=5.3;y[39]=3.5;
	uchar filtro2[4]={0x03,0x00,0x00,0x00}; //= 0000....00011 
	xx=aplica_filtro(  x,y,filtro2,40);
	printf("\nAplicando filtro a    vectores (%lg,%lg) y (%lg,%lg) = %lg",x[38],x[39],y[38],y[39],xx);
	xx=halla_distancia(x,y,filtro2,40);
	printf("\nHallo distancia entre vectores (%lg,%lg) y (%lg,%lg) = %lg",x[38],x[39],y[38],y[39],xx);
	printf("\nFIN");

	getchar();getchar();
	return 0;
}


int filtro(ulong u,int posicion)
{
	return (u>>posicion)&1;  //2 operaciones
}

int filtro(uchar *u,int posicion)
{
	return ( (u[posicion/8]>>(posicion % 8)) & 1 ); //5 operaciones
}

double aplica_filtro(double *a,double *b,uchar *filtro1,int s_filtro1)
{
	double x=0;
	int i;
	for (i=0;i<s_filtro1;i++)
	{
		x+=fabs(a[i]-b[i]) * FILTRO(filtro1,i);
	}
	return x;
}

double halla_distancia(double *a,double *b,uchar *filtro1,int s_filtro1)
{
	double x=0;
	int i=0;
	for (i=0;i<s_filtro1;i++)
	{
		x+=(a[i]-b[i])*(a[i]-b[i]) * FILTRO(filtro1,i);
	}
	return sqrt(x);
}
