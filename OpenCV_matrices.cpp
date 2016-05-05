//EN PROJECT->SETTING->LINK->OUTPUT en RESERVE poner: 0x6400000  (=100Mb)
//Poner en directorio las dlls: libguide40.dll y cxcore100.dll
//Meter en Project->settings,general: cxcore.lib cv.lib highgui.lib cvaux.lib 
#ifdef _CH_
#pragma package <opencv>
#endif

#ifndef _EiC
#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <stdlib.h>
#endif

void imprimematriz(int filas,int col,CvMat* Ma);

void main()
{
	{//double:
		printf("\nDouble:");
		double a[9]={1,1,1,2,-2,2,2,2,-5};
	//	CvMat Ma=CvMat(3,3,CV_32FC1,a,0);

		CvMat* Ma=cvCreateMat(3,3,CV_64FC1);//CV_64FC1 para double
		CvMat* Mb=cvCreateMat(3,3,CV_64FC1);
		CvMat* Mc=cvCreateMat(3,3,CV_64FC1);

		cvInitMatHeader(Ma,3,3,CV_64FC1,a);
		//CvMat resultMat = cvMat(3, 3, CV_32FC1, a);

		cvInvert(Ma,Mb);
		cvMatMul(Ma,Mb,Mc);

		//imprimematriz(3,3,Mb);
		//imprimematriz(3,3,Mc);

		double determinante,producto;

		determinante=cvDotProduct(Ma,Ma);
		producto    =cvDotProduct(Ma,Mc);
		printf("\nDeterminante=%lg",determinante);
		printf("\nProducto    =%lg",producto);
	}
	{//float:
		printf("\nFloat:");
		float a[9]={1,1,1,2,-2,2,2,2,-5};
	//	CvMat Ma=CvMat(3,3,CV_32FC1,a,0);

		CvMat* Ma=cvCreateMat(3,3,CV_32FC1);//CV_64FC1 para double
		CvMat* Mb=cvCreateMat(3,3,CV_32FC1);
		CvMat* Mc=cvCreateMat(3,3,CV_32FC1);

		cvInitMatHeader(Ma,3,3,CV_32FC1,a);
		//CvMat resultMat = cvMat(3, 3, CV_32FC1, a);

		cvInvert(Ma,Mb);
		cvMatMul(Ma,Mb,Mc);

		//imprimematriz(3,3,Mb);
		//imprimematriz(3,3,Mc);

		double determinante,producto;

		determinante=cvDotProduct(Ma,Ma);
		producto    =cvDotProduct(Ma,Mc);
		printf("\nDeterminante=%lg",determinante);
		printf("\nProducto    =%lg",producto);
	}


	//Resolviendo sistemas lineales tipo Ax=b para obtener x
	double xx[3]={10,202,303};
	CvMat* x2=cvCreateMat(3,1,CV_64FC1);
	cvInitMatHeader(x2,3,1,CV_64FC1,xx);
	CvMat* b=cvCreateMat(3,1,CV_64FC1);
	CvMat* x=cvCreateMat(3,1,CV_64FC1);

	double a[9]={1,1,1,2,-2,2,2,2,-5};
	CvMat* Ma=cvCreateMat(3,3,CV_64FC1);//CV_64FC1 para double
	cvInitMatHeader(Ma,3,3,CV_64FC1,a);
	cvMatMul(Ma,x2,b);
	imprimematriz(1,3,b);
	cvSolve(Ma,b,x);
	imprimematriz(1,3,x);

	printf("\nEnd");
	getchar();getchar();
}


void imprimematriz(int filas,int col,CvMat* Ma)
{
	long i,j;
	for (i=0;i<col;i++)
	{
		printf("\n");
		for(j=0;j<filas;j++)
		{
			printf("%g\t",cvmGet(Ma,i,j));
		}
	}
	printf("\n=====================================");
}


