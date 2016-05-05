#ifdef _CH_
#pragma package <opencv> 
#endif
#ifndef _EiC
#include "cv.h"
#include "highgui.h"
#include <memory.h>

#include <stdio.h>
#include <stdlib.h>
#endif

void imprimematriz(CvMat* Ma);


void main()
{
	double datin[14][5]={
			10,11,12,13,14,
			20,21,22,23,24,
			30,31,32,33,34,
			40,41,42,43,44,
			50,51,52,53,54,
			60,61,62,63,64,
			70,71,72,73,74,
			80,81,82,83,84,
			90,91,92,93,94,
			100,101,102,103,104,
			110,111,112,113,114,
			120,121,122,123,124,
			130,131,132,133,134,
			140,141,142,143,144
			};
	double m_k[5][3]={
			30,32,34,
			40,42,44,
			50,52,54,
			60,62,64,
			70,72,74};

	CvMat *Mdatin;
	CvMat *Mk;
	CvMat *Mdatout;
	Mdatin=  cvCreateMat(14,5,CV_64FC1);
	Mk    =  cvCreateMat(5, 3,CV_64FC1);
	Mdatout= cvCreateMat(14,3,CV_64FC1);

	cvInitMatHeader(Mdatin,14,5,CV_64FC1,datin);
	cvInitMatHeader(Mk    ,5 ,3,CV_64FC1,m_k);
	cvMatMul(Mdatin,Mk,Mdatout);

	imprimematriz(Mdatout);
	printf("\nFIN");
	getchar();getchar();

	cvReleaseMat(&Mdatin);
	cvReleaseMat(&Mk);
	cvReleaseMat(&Mdatin);

}	


void imprimematriz(CvMat* Ma)
{
	long i,j;
	for(j=0;j<Ma->rows;j++)
	{
		printf("\n");
		for (i=0;i<Ma->cols;i++)
		{
			printf("%10g\t",cvmGet(Ma,j,i));
		}
	}
	printf("\n=====================================");
}
