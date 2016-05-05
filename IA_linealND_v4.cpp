//ffilldemo-1.c  Prueba de mouse
//Metido en project->settings-> ventana "Object/lybrary modules":
//  cxcore.lib cv.lib highgui.lib cvaux.lib


//  ¡¡¡¡¡OJO, vin debe ser de tamaño DIMin+1   !!!!

#ifdef _CH_
#pragma package <opencv>
#endif

#ifndef _EiC
#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <stdlib.h>
#endif

#include <memory.h>
#define DMAX 25 //maximo numero de dimensiones

void imprimematriz(int filas,int col,CvMat* Ma);


class c_linealND
{
public:
	c_linealND(int DIMin1,int DIMout1) { DIMin=DIMin1+1;DIMout=DIMout1;	Mk=cvCreateMat(DIMin,DIMout,CV_64FC1);borra();}//ojo, dimin+1 pues hay cte a0: z=a0+a1*x+a1*y+...
	void borra();
	void mete(double *vin,double *vout);//introduce vector de entrada y salida OJO, vin debe ser de tamaño DIMin+1!!!
	void halla_coeficientes(double *kk);//Halla coeficientes y los mete en kk
	void halla_vout(double *vin,double *vout);//introduce vector de entrada dá salida OJO, vin debe ser de tamaño DIMin+1!!!
	~c_linealND() {cvReleaseMat(&Mk);}
private:
	int DIMin,DIMout;//dimensiones de entrada-salida
	double S[DMAX][DMAX];//[DIMin][DIMin]
	double T[DMAX][DMAX];//[DIMin][DIMout]
	double K[DMAX][DMAX];//[DIMin][DIMout] =ctes de salida
	int kvalid;//dice si tienes datos válidos en K[][]
	CvMat* Mk;
};



int main()
{

	double vin[20][4]={
						94.25144667, 62.05715692, 91.75156847, 70.75881302,
						57.56310108, 30.4443594 , 59.11714525, 10.31094298,
						86.37969852, 77.52834817, 6.542383554, 32.41663836,
						52.54969224, 87.70095821, 84.83087516, 52.17296847,
						73.77345076, 38.05952371, 16.20308938, 78.11140818,
						84.85354606, 91.48100894, 49.39516724, 79.49201163,
						90.85833144, 76.52088345, 25.07678127, 16.26524862,
						22.33884824, 11.96070025, 80.71184145, 81.29329514,
						49.88728978, 66.19496988, 69.17625788, 28.18026848,
						41.89648562, 97.74555609, 0.295716613, 48.97272772,
						56.97519316, 16.86598066, 88.41270155, 32.97750716,
						94.72750603, 70.04212945, 60.0415457, 14.28209484,
						76.94913892, 40.04454177, 0.654389549, 17.54071542,
						13.87090559, 48.36911409, 77.61517671, 73.84147491,
						24.84576025, 64.32151785, 43.06152481, 79.16073455,
						6.087699965, 89.33399149, 38.46512674, 47.3639427,
						15.45843319, 8.800130424, 50.4810371 , 67.69913452,
						44.13613972, 16.83557982, 41.61927781, 86.65378836,
						62.88279191, 39.91451275, 22.03679941, 99.9480564,
						84.66674297, 14.4918086 , 9.421657199, 76.81083874};

	double coef[2][5]={
	 					5,  -6,8,-8,120,
						10,-10,5,-5,250};
	double rran=1.0/RAND_MAX;

	c_linealND lineal(4,2);

	long i,d,j;
	double vvout[2],vvin[5];
	for(j=0;j<20;j++)
	{
		for (d=0;d<2;d++)
		{
			vvout[d]=0.0;
			for (i=0;i<4;i++)
			{
				vvout[d]+=vin[j][i]*coef[d][i];
			}
			vvout[d]+=(coef[d][i]+rran*rand());
		}
		for (i=0;i<4;i++)
		{
			vvin[i]=vin[j][i];//HAY que copiar pues la clase modifica vvin[DIMin] que es el siguiente
		}
		lineal.mete(vvin,vvout);
	}
	double k[2][5];
	lineal.halla_coeficientes(&k[0][0]);

	for (i=0;i<4;i++)
		vvin[i]=vin[0][i];
	lineal.halla_vout(vvin,vvout);
	for (i=0;i<2;i++)
		printf("\nvout %li:%lg",i,vvout[i]);

	printf("\nEnd");
	getchar();getchar();
	return 1;
}


void imprimematriz(int filas,int col,CvMat* Ma)
{
	long i,j;
	for(j=0;j<filas;j++)
	{
		printf("\n");
		for (i=0;i<col;i++)
		{
			printf("%10g\t",cvmGet(Ma,j,i));
		}
	}
	printf("\n=====================================");
}



void c_linealND::borra()
{
	kvalid=0;//No tenemos K[][] válida aún
	long in,out,in2;
	for (in=0;in<DIMin;in++)
	{
		for(out=0;out<DIMout;out++)
		{
			T[in][out]=0.0;
			K[in][out]=0.0;
		}
		for(in2=0;in2<DIMin;in2++)
		{
			S[in2][in]=0.0;
		}
	}
}

void c_linealND::mete(double *vin,double *vout)
{
	vin[DIMin-1]=1.0;//para hallar la cte
	int i,j;
	for (i=0;i<DIMin;i++)
	{
		for (j=i;j<DIMin;j++)
		{
			S[i][j]+=(vin[i]*vin[j]);
		}
		for (j=0;j<DIMout;j++)
		{
			T[i][j]+=(vin[i]*vout[j]);
		}
	}
}

void c_linealND::halla_coeficientes(double *kk)
{
	int i,j,k;
	for (i=0;i<(DIMin-1);i++)
	{
		for (j=i+1;j<DIMin;j++)
		{
			S[j][i]=S[i][j];
		}
	}

	double ss[DMAX*DMAX],tt[DMAX*DMAX];
	k=0;
	for (i=0;i<DIMin;i++)
	{
		for (j=0;j<DIMin;j++)
		{
			ss[k++]=S[i][j];
		}
	}
	k=0;
	for (j=0;j<DIMin;j++)
	{
		for (i=0;i<DIMout;i++)
		{
			tt[k++]=T[j][i];
		}
	}

	//Ms*Mk=Mt..hallar Mk
	CvMat* Ms=cvCreateMat(DIMin,DIMin,CV_64FC1);
	CvMat* Mt=cvCreateMat(DIMin,DIMout,CV_64FC1);
	//     Mk=cvCreateMat(DIMin,DIMout,CV_64FC1)
	cvInitMatHeader(Ms,DIMin,DIMin, CV_64FC1,ss);
	cvInitMatHeader(Mt,DIMin,DIMout,CV_64FC1,tt);
	cvSolve(Ms,Mt,Mk);

	imprimematriz(DIMin,DIMout,Mt);
	imprimematriz(DIMin,DIMout,Mk);

	long index=0;
	double suma=0.0;
	for (k=0;k<DIMout;k++)
	{
		for (i=0;i<DIMin;i++)
		{
			kk[index++]=K[i][k]=cvmGet(Mk,i,k);
			suma+=fabs(K[i][k]);
		}
	}
	cvReleaseMat(&Ms);
	cvReleaseMat(&Mt);

	if (suma) 
		kvalid=1;//YA es válido
	else 
	{
		printf("\nERROR, calculo de coeficientes converge");
		getchar();getchar();
	}
}

void c_linealND::halla_vout(double *vin,double *vout)//introduce vector de entrada dá salida OJO, vin debe ser de tamaño DIMin+1!!!
{
	if (!kvalid)
	{
		printf("\nERROR, no hay datos validos de coeficientes");
		getchar();getchar();
		return;
	}
	vin[DIMin-1]=1;
	CvMat* Mvin =cvCreateMat(1,DIMin ,CV_64FC1);
	CvMat* Mvout=cvCreateMat(1,DIMout,CV_64FC1);
	cvInitMatHeader(Mvin,1,DIMin,CV_64FC1,vin);
	cvMatMul(Mvin,Mk,Mvout);
	long i;
	for (i=0;i<DIMout;i++)
		vout[i]=cvmGet(Mvout,0,i);
	cvReleaseMat(&Mvin);
	cvReleaseMat(&Mvout);
}