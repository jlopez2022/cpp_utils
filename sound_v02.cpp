/* Analizador de calibraciones.cpp: 

*/
#include "stdafx.h"
#include <windows.h> // WinApi header 
#include <math.h>
#define BMP 118.0  //118 batidos por minuto

#pragma warning(disable: 4996)


//halla las notas musicales y tiempos: (ver función):
long nota_mat[26],*nota_ix=nota_mat+12,tiempo_ix[6];
void hallanotas(void);

void suena(long nota,long tiempo)
{
	//tiempo: 0=redonda,1=blanca,2=negra,3=corchea, 4=semicorchea, 5=fusa 
	//nota:   0=La 1=La# 2=Si 3=do 4=do# 5=re 6=re# 7=mi 8=fa 9=fa# 10=sol 11=sol# 12=la 13=SILENCIO!!
	if (tiempo<7)
		Beep(nota_ix[nota],tiempo_ix[tiempo]);
}

long main( void )
{
	hallanotas();
	int secuencia1[60]={-1,2, 13,3, -1,2, 13,3, -1,2, 13,3, 2,1, 13,2, 6,1, 13,2, 5,2, 13,3, 4,2, 13,3, 3,2, 13,3, 9,1, 13,2, 6,2, 13,2,  5,2, 13,3, 4,2, 13,3, 3,2, 13,3, 9,1, 13,2, 6,2, 13,2 };  
	long i;
	for (i=0;i<31;i++)
	{
		suena(secuencia1[2*i],secuencia1[2*i+1]);
	}

	/*
	suena(0,2);  //la, negra
	suena(1,2);
	suena(5,2);
	suena(4,2);
	suena(0,2);
	suena(1,2);*/

	printf("\nFIN");
	getchar();
	return 1;
}


void hallanotas(void)
{
/*
ix	not	frec exact	formula
-12	la	220	220.000	.=440*2^(-12/12)
-11	la#	233	233.082	.=440*2^(-11/12)
-10	si	247	246.942	.=440*2^(-10/12)
-9	do	262	261.626	…
-8	do#	277	277.183	
-7	re	294	293.665	
-6	re#	311	311.127	
-5	mi	330	329.628	
-4	fa	349	349.228	
-3	fa#	370	369.994	
-2	sol	392	391.995	
-1	sol#415	415.305	
0	la	440	440.000	
1	la#	466	466.164	
2	si	494	493.883	
3	do	523	523.251	
4	do#	554	554.365	
5	re	587	587.330	
6	re#	622	622.254	
7	mi	659	659.255	
8	fa	698	698.456	
9	fa#	740	739.989	
10	sol	784	783.991	
11	sol#831	830.609	
12	la	880	880.000	
13  SILENCIO  ¡¡¡¡ OJO !!!!!!!!!!!!!
	*/
	long i;
	for (i=-12;i<13;i++)
	{
		nota_ix[i]=(long) (0.499+440.0*pow(2.0,1.0*i/12.0));
	}
	nota_ix[i]=1; //silencio

	//0=redonda,1=blanca,negra,2=corchea, 3=semicorchea, 4=fusa 
	//redonda=o blanca=0 con palo, negra=o rellena con palo, corchea=negra con palo y una banderin, 
	//semicorchea=corchea con 2 banderines, fusa=semicorchea con 3 banderines
	double x=60000.0/BMP/8.0;
	for (i=5;i>=0;i--)
	{
		tiempo_ix[i]=(long) (0.499+x);
		x*=2;
	}
	tiempo_ix[6]=1;//1 milisegundo para hacer mezclas
}