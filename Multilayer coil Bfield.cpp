// Halla campo B en el eje de una bobina multilayer en el eje. Pone el resultado en out.txt
// PARA 1 AMPERIO ojo!

//#include "stdafx.h"
#include <stdio.h>
#include <math.h>

#define PI 3.1415926535897932384626433832795
#define rmin  8.5e-3 //radio mínimo de la bobina
#define dh    1e-3   //diametro de hilo de cobre
#define turns 20     //vueltas de cada capa
#define capas 4      //Número de capas
#define factor 1.0   //incremento de altura/diametro por capa, debe ser o bien 1 si coincide una sobre otra o 0.866 si se mete en medio


int main()
{
	FILE *str;
	str=fopen("out.txt","w");
	if(!str)
	{
		printf("\nNo puedo abrir out.txt");getchar();return -1;
	}

	double length=dh*turns,dmax;
	dmax=2*rmin+2*dh+ 2*factor*dh*(capas-1);
	fprintf(str,"\nLongitud de bobina       :%lg",length);
	fprintf(str,"\nCapas                    :%li",capas);
	fprintf(str,"\nDiametro minimo de bobina:%lg",2*rmin);
	fprintf(str,"\nDiametro maximo de bobina:%lg",dmax);
	fprintf(str,"\nCalculo de B para 1 amperio desde el centro de la bobina a 4*longitud");
	fprintf(str,"\nz (m)\tB (T)");

	printf("\nLongitud de bobina       :%lg",length);
	printf("\nCapas                    :%li",capas);
	printf("\nDiametro minimo de bobina:%lg",2*rmin);
	printf("\nDiametro maximo de bobina:%lg",dmax);
	printf("\nCalculo de B para 1 amperio desde el centro de la bobina a 4*longitud");
	printf("\nz (m)\tB (T)");


	//Calculo desde el centro (z=0) hasta z=4*long en 50 puntos
	double z=0,R;
	double dz=length/50;
	for (z=0;z<=length;z+=dz)
	{//z=punto de observación
		double B=0.0;int i,j;
		for (i=0;i<turns;i++)
		{
			double z1;
			z1=z-(i-0.5*turns)*dh;//distancia de cada loop al punto de observación
			R=rmin+dh/2;//radio medio de cada loop
			for (j=0;j<capas;j++)
			{
				double x;
				x=R*R+z1*z1;
				x=R*R/pow(x,1.5);
				B+=x;
				R+=factor*dh;//incremento el radio 				
			}
		}
		B=B*2e-7*PI;
		printf(     "\n%lg\t %lg",z,B);
		fprintf(str,"\n%lg\t %lg",z,B);
	}
	//printf("\nDiametro maximo alcanzado=%lg",2*(R-factor*dh));

	printf("\n========== END ==============");getchar();
	return 0;
}

