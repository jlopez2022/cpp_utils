#include <stdio.h>
#include <math.h>
#define SEGMENTS 1000 //segmentos

double dis2(double pos1[3],double pos3[3]) //distancia al cuadrado
{
	double x=0.0,xx;
	xx=(pos1[0]-pos3[0]);x+=xx*xx;
	xx=(pos1[1]-pos3[1]);x+=xx*xx;
	xx=(pos1[2]-pos3[2]);x+=xx*xx;
	return(x);
}

double dis2(double pos1[3]) //distancia al cuadrado
{
	double x;
	x=pos1[0]*pos1[0]+pos1[1]*pos1[1]+pos1[2]*pos1[2];
	return(x);
}


void prod(double a[3],double b[3],double *c)//Halla el producto vectorial de a y b y lo mete en c
{
	c[0]= a[1]*b[2]-a[2]*b[1];
	c[1]=-a[0]*b[2]+a[2]*b[0];
	c[2]= a[0]*b[1]-a[1]*b[0];
}

void halla_B(double pos1[3],double pos2[3],double pos3[3],double *B)
{
	double u[3],du[3];//du es el vector delta del vector pos1 a pos2
	long i;
	double long_vector;
	long_vector=sqrt(dis2(pos1,pos2));
	for (i=0;i<3;i++)
	{
		du[i]=(pos2[i]-pos1[i])/SEGMENTS;
	}
	B[0]=B[1]=B[2]=0.0;
	pos1[0]+=du[0]/2.0;pos1[1]+=du[1]/2.0;pos1[2]+=du[2]/2.0;//añado du/2 para centrar
	for (i=0;i<SEGMENTS;i++)
	{
		u[0]=pos1[0]+du[0]*i;
		u[1]=pos1[1]+du[1]*i;
		u[2]=pos1[2]+du[2]*i;
		double BB;
		BB=sqrt(dis2(u,pos3));BB=1/BB/BB/BB;
		double dv[3]; //dv es el delta x,y,z del vector u+i*du respecto la posicion pos3
		dv[0]=pos3[0]-u[0];
		dv[1]=pos3[1]-u[1];
		dv[2]=pos3[2]-u[2];
		double dw[3]; //dw es el producto vectorial de du por dv
		prod(du,dv,dw);
		B[0]+=BB*dw[0];
		B[1]+=BB*dw[1];
		B[2]+=BB*dw[2];
	}
	B[0]*=1e-7;
	B[1]*=1e-7;
	B[2]*=1e-7;
}	


void main()
{
	//los segmentos van de pos1 a 2 y en pos3 se mide el campo


	{
		double pos1[3]={-0.0100,0,0};
		double pos2[3]={+0.0100,0,0};
		double pos3[3]={0,5,0};
		double B[3];
		double BB;
		halla_B(pos1,pos2,pos3,B);
		BB=sqrt(B[0]*B[0]+B[1]*B[1]+B[2]*B[2]);
		printf("\n=====================");
		printf("\nBt=%lg teslas*I",BB);
		printf("\nBx=%lg teslas*I",B[0]);
		printf("\nBy=%lg teslas*I",B[1]);
		printf("\nBz=%lg teslas*I",B[2]);
	}
	{
		double pos1[3]={-1.00,0,0};
		double pos2[3]={+1.00,0,0};
		double pos3[3]={0,5,0};
		double B[3];
		double BB;
		halla_B(pos1,pos2,pos3,B);
		BB=sqrt(B[0]*B[0]+B[1]*B[1]+B[2]*B[2]);
		printf("\n=====================");
		printf("\nBt=%lg teslas*I",BB);
		printf("\nBx=%lg teslas*I",B[0]);
		printf("\nBy=%lg teslas*I",B[1]);
		printf("\nBz=%lg teslas*I",B[2]);
	}
	{
		double pos1[3]={-5,0,0};
		double pos2[3]={+5,0,0};
		double pos3[3]={0,5,0};
		double B[3];
		double BB;
		halla_B(pos1,pos2,pos3,B);
		BB=sqrt(B[0]*B[0]+B[1]*B[1]+B[2]*B[2]);
		printf("\n=====================");
		printf("\nBt=%lg teslas*I",BB);
		printf("\nBx=%lg teslas*I",B[0]);
		printf("\nBy=%lg teslas*I",B[1]);
		printf("\nBz=%lg teslas*I",B[2]);
	}
	{
		double pos1[3]={-1000.0,0,0};
		double pos2[3]={+1000.0,0,0};
		double pos3[3]={0,5,0};
		double B[3];
		double BB;
		halla_B(pos1,pos2,pos3,B);
		BB=sqrt(B[0]*B[0]+B[1]*B[1]+B[2]*B[2]);
		printf("\n=====================");
		printf("\nBt=%lg teslas*I",BB);
		printf("\nBx=%lg teslas*I",B[0]);
		printf("\nBy=%lg teslas*I",B[1]);
		printf("\nBz=%lg teslas*I",B[2]);
	}

	{
		double pos1[3]={-1000.0,0,0};
		double pos2[3]={+1000.0,0,0};
		double pos3[3]={0,0,5};
		double B[3];
		double BB;
		halla_B(pos1,pos2,pos3,B);
		BB=sqrt(B[0]*B[0]+B[1]*B[1]+B[2]*B[2]);
		printf("\n=====================");
		printf("\nBt=%lg teslas*I",BB);
		printf("\nBx=%lg teslas*I",B[0]);
		printf("\nBy=%lg teslas*I",B[1]);
		printf("\nBz=%lg teslas*I",B[2]);
	}

	{
		double pos1[3]={0,-1000.0,0};
		double pos2[3]={0,+1000.0,0};
		double pos3[3]={5,0,0};
		double B[3];
		double BB;
		halla_B(pos1,pos2,pos3,B);
		BB=sqrt(B[0]*B[0]+B[1]*B[1]+B[2]*B[2]);
		printf("\n=====================");
		printf("\nBt=%lg teslas*I",BB);
		printf("\nBx=%lg teslas*I",B[0]);
		printf("\nBy=%lg teslas*I",B[1]);
		printf("\nBz=%lg teslas*I",B[2]);
	}

	printf("\n=====================");
	getchar();getchar();
}


