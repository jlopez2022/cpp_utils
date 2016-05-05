/*
Modulo de estadistica

Como stat.h pero:
- No carga GeneralC  
- Mejora la funcion log2()
*/
#include <stdlib.h>
#include <stdio.h>
#define VALORMAX 1000000  //maximo numero de datos


class StatC
{
   private:
//	  double bitmatriz[2050];
   public:
	  // La matriz bitsn[i] halla los bits necesarios de i=2E/Emin E=+-error RMS o delta, Emin=error máximo admisible
	  // i=-1024..+1024  bitsn[+/-i] = log(2i)/log2 = 1+log(i)/log2
	  double *X,*Y;//datos de entrada
	  double A, B;   //X=A+B*Y
	   
      double Sx, Sx2, Sy, Sxy;
      long NumMuestras;
      StatC(void);~StatC(void);
	  void Borra(void);//Pone todo a 0
      void StatIn(double x, double y); //Introduce datos de entrada
	  void HallaStat(void);
	  double *INL,maxINL;
      double HallaINL(void);//Calcula el INL de cada dato con respecto a la recta, los mete en INL[] y devuelve el peor
	  void GeneraInforme();
};

StatC::StatC(void)
{
   Borra();
   X=new double[VALORMAX];
   Y=new double[VALORMAX];
   INL=new double[VALORMAX];
}

StatC::~StatC(void)
{ delete[] X, Y, INL; }

void StatC::Borra(void)//Pone todo a 0
{
   Sx=Sx2=Sy=Sxy=0;NumMuestras=0;A=B=0.00001;maxINL=0.0;
}


void StatC::StatIn(double x, double y) //Introduce datos de entrada
{
	X[NumMuestras]=x;
	Y[NumMuestras]=y;
   NumMuestras++;
   Sx+=x;
   Sx2+=x*x;
   Sy+=y;
   Sxy+=x*y;
}


void StatC::HallaStat(void)
{
	double N=NumMuestras*1.0;
	B=(N*Sxy-Sx*Sy)/(N*Sx2-Sx*Sx);
	A=(Sy-B*Sx)/N;
}

double StatC::HallaINL(void)
{
	HallaStat();
	long i;double xx;
	maxINL=0.0;
	for (i=0;i<NumMuestras;i++)
	{
		xx=Y[i]-(A+B*X[i]);
		if (xx<0) xx=-xx;
		if (maxINL<xx) 
			maxINL=xx;
		INL[i]=xx;
	}
	return(maxINL);
}

void StatC::GeneraInforme()
{	
	FILE *str=fopen("out.txt","w");
	this->HallaINL();
	if (!str)
	{
		printf("\nError en Imain(): no puedo escribir en out.txt");
		getchar();getchar();
		return;
	}

	fprintf(str,"A = %lg \nB = %lg \nmaxINL = %lg\n\n",A,B,maxINL);
	
	
	fprintf(str,"i\tx\ty\tINL\n");
	for (long i=0;i<NumMuestras;i++)
		fprintf(str,"%8li\t%lg\t%lg\t%lg\n",i,X[i],Y[i],INL[i]);

	fclose(str);

}

void main() //ejemplo de uso
{
	double a=10.05,b=1.01,r=1.8;
	long i;
	StatC *stat=new StatC();
	double x;
	for (i=10;i<132;i++)
	{
		x=a+b*i+r*rand()/RAND_MAX;
		stat->StatIn((double) i,x);
	}
	//x=stat->HallaINL();
	stat->GeneraInforme();
}

