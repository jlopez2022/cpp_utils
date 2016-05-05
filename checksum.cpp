#include <stdio.h>

/*
Calculo de checksums.
Si la probabilidad de que un paquete sea malo es del 1%, la probabilidad de tener un checksum
correcto es que el paquete tenga dos errores inversos en el mismo bit, o sea: 
1/2*0.01*0.01*1/8 = 1/160000

hallachecksum2 divide este número por el número de bytes checksum_size
Si checksum_size=16 entonces la probabilidad de checksum correcto y datos mal es de 1/2.56 Mill
*/

/*
Halla checksum de 8 bits
No detecta error si se intercambia de posición dos bytes (ver hallachecksum2() )
La probabilidad de checksum bueno de paquete malo es:
una entre 16/probabilidad de fallo simple al cuadrado, o sea, si la probabilidad de error simple
es del 1%, la probabilidad de fallo es una entre 16*(1/100)^2=160000
*/
char hallachecksum(char *inicio,long size)
{
	char checksum=0x55;
	long i;
	for (i=0;i<size;i++)
	{
		checksum^=inicio[i];
	}
	return checksum;
}

/*
hallachecksum2() halla un checksum de tamaño 8xchecksum_size bits. 
Si la matriz no es múltiplo del tamaño de checksum, usa 0x55 de relleno
La probabilidad de checksum correcto y paquete incorrecto es una entre 
 16*checksum_size/probabilidad de fallo simple al cuadrado

Ejemplo: probabilidad de fallo simple=1/100,checksum_size=8, 
probabilidad de checksum correcto y paquete no es una entre:

  16*8/(1/100)^2=1.28 millones
 
*/
void hallachecksum2(char *inicio,long inicio_size,char *checksum,long checksum_size)
{
	long i,j,k;
	for (j=0;j<checksum_size;j++)
		checksum[j]=0x55;

	for (i=0;i<inicio_size;i+=checksum_size)
	{
		for (j=0;j<checksum_size;j++)
		{
			k=i+j;
			if (k<inicio_size)
				checksum[j]^=inicio[k];
			else
				checksum[j]^=0x55;
		}
	}
}


int main()
{
	long i;
	long mat[60000];
	double mat2[60000];
	for (i=0;i<60000;i++)
	{
		mat[i]=i;
		mat2[i]=1000.0*i;
	}

	char checksum1,checksum2,checksum22,checksum23;
	long size;
	size=60000*sizeof(long);
	checksum1=hallachecksum((char *) mat,size);

	size=60000*sizeof(double);
	checksum2=hallachecksum((char *) mat2,size);
	mat2[177]+=100;
	checksum22=hallachecksum((char *) mat2,size);
	mat2[177]=1000.0*177;
	checksum23=hallachecksum((char *) mat2,size);

	char checksum4[4];
	char ch[256];
	for (i=0;i<256;i++)
	{
		ch[i]=(char) (i-128);
	}
	hallachecksum2(ch,5,checksum4,4);


	char checksum9=0x55;
	checksum9^=0x0A;
	checksum9^=0x0B;
	checksum9^=0x05;
	checksum9^=0x05;
	checksum9=checksum9;
	
	checksum9=0x55;
	checksum9^=0x0A;
	checksum9^=0x0B;
	checksum9^=0x05;
	checksum9^=0x06;
	checksum9=checksum9;


	printf("\nFIN");getchar();getchar();
	return 1;
}