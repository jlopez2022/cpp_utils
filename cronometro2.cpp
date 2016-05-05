//Emplear en modo release!!
#include <stdio.h>      
#include <stdlib.h> //rand()
#include <math.h>   //fabs()
#include <time.h>
#include <Windows.h>
#define XMAX 1920
#define SIZE 100000L //XMAX*SIZE debe estar entre 1e8 y 5e8
#define KDOBLE double 

//Entrega diferencia en valor absoluto y diferencia al cuadrado
//UDIF tarda EL DOBLE que fabs() empleado sobre matrices pero no usa libreria math.h
#define UDIF(a,b) ((a) > (b) ? (a-b) : (b-a))
//DIF2 tarda el doble si se emplea sobre matrices que usar x=a-b y luego usar x*x
#define DIF2(a,b) ( (a-b)*(a-b) )

int main ()
{
	long i,j;
	KDOBLE color1[XMAX],color2[XMAX];
	for (i=0;i<XMAX;i++)
		color1[i]=(KDOBLE) (rand() % 256);
	for (i=0;i<XMAX;i++)
		color2[i]=(KDOBLE) (rand() % 256);

	clock_t tiempo0,tiempo1;
	KDOBLE sum,xx;
	double MFLOPS;
	sum=0.0;
	//Calculo de diferencia sin emplear UDIF
	tiempo0 = clock();
	for (j = 0; j < SIZE; j++)
		for (i = 0; i < XMAX; i++)
		{
			sum+=fabs(color1[i]-color2[i]);
		}
			
	tiempo1 = clock()-tiempo0; 
	MFLOPS=1e-6*SIZE*XMAX/tiempo1*CLOCKS_PER_SEC; printf("\nEmpleando fabs:   %lg Megaflops", MFLOPS);

		for (j = 0; j < SIZE; j++)
		for (i = 0; i < XMAX; i++)
		{
			sum+=UDIF(color1[i],color2[i]);
		}
			
	tiempo1 = clock()-tiempo0; 
	MFLOPS=1e-6*SIZE*XMAX/tiempo1*CLOCKS_PER_SEC; printf("\nEmpleando UDIF:   %lg Megaflops", MFLOPS);

	tiempo0 = clock();
	for (j = 0; j < SIZE; j++)
		for (i = 0; i < XMAX; i++)
		{
			xx=color1[i]-color2[i];
			sum+=xx*xx;
		}
			
	tiempo1 = clock()-tiempo0; 
	MFLOPS=1e-6*SIZE*XMAX/tiempo1*CLOCKS_PER_SEC; printf("\nSin emplear DIF2: %lg Megaflops", MFLOPS);

		for (j = 0; j < SIZE; j++)
		for (i = 0; i < XMAX; i++)
		{
			sum+=DIF2(color1[i],color2[i]);
		}
			
	tiempo1 = clock()-tiempo0; 
	MFLOPS=1e-6*SIZE*XMAX/tiempo1*CLOCKS_PER_SEC; printf("\nEmpleando DIF2:   %lg Megaflops", MFLOPS);


	printf("\nIgnorar:%lg",sum);//Si no se usa sum no se ejecutariann los loops.
	printf("\n\n=== FIN ===\n");getchar();getchar();
	return 0;
}

