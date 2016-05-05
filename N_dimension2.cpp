//Calcula funciones de valor minimo de fun con n coeficientes 

#include <stdio.h>
#define CONSTS 11 //numero de coeficientes
#define MIN -1.0 //minimo inicial
#define MAX 1.0  //maximo inicial
#define DELTA 1e-4

double fun(double *coef);

double fun(double *coef)//funcion de prueba
{
	double x=0;
	static double k[CONSTS]={-0.010,0.121,0.232,0.343,0.454, 0.565, 0.676, 0.787, 0.898, 0.121,0.232};
	static double k2[CONSTS]={-1.2, 0.7, 0.2, 15.2, 3.1, 2.18, -1.3, 0.2, 6.1, 3.1, 4.4};
	long i;
	for (i=0;i<CONSTS;i++)
		x=x+k2[i]*(coef[i]-k[i])*(coef[i]-k[i]);
	return x;
}


void main()
{
	char c;
	long i;

	double error,errormin=1e60;
	double coef[CONSTS];
	long iter,itermax,icoef; //iter es el número de iteraciones
	printf("\nNumero de iteraciones:");scanf("%li",&itermax);

	for (i=0;i<CONSTS;i++)
	{
		coef[i]=0.5;
	}

	for (iter=0;iter<itermax;iter++)
	{
		for (icoef=0;icoef<CONSTS;icoef++)
		{
			double a0,a1,a2,ant,delta,x;
			ant=coef[icoef];
			delta=DELTA*ant;

			a0=fun(coef);
			coef[icoef]=ant-delta;a1=fun(coef);
			coef[icoef]=ant-2.0*delta;a2=fun(coef);

			x=ant- (a0-a1)*delta/(a0-2.0*a1+a2+1e-60);
			if (x<MIN) 
				x=MIN;
			if (x>MAX) 
				x=MAX;
			coef[icoef]=x;
		}
		error=fun(coef);if (error<0) error=-error;
		if (error<errormin)
			errormin=error;
		else 
			printf("\nWarning error aumenta en iter %i de %g a %g",iter,errormin,error);

		printf("\nError=%g",error);
	}

	for (icoef=0;icoef<CONSTS;icoef++)
	{
		printf("\ncoeficiente %2i = %g ",icoef,coef[icoef]);
	}

	//ignorar las siguientes lineas
	printf("\n");
	double errx,errmax=0;
	double k[CONSTS]={-0.010,0.121,0.232,0.343,0.454, 0.565, 0.676, 0.787, 0.898, 0.121,0.232};
	for (icoef=0;icoef<CONSTS;icoef++)
	{
		errx=coef[icoef]-k[icoef];if (errx<0) errx=-errx;
		if (errmax<errx) errmax=errx;
		printf("\ncoeficiente %2i = %g error = %g",icoef,coef[icoef],errx);
	}
	printf("\nerror max=%g",errmax);
	scanf("%c%c",&c,&c);

}