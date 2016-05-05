#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*
in.txt:
Primera fila debe contener el numero de variables var
x,y,u,v
Halla los coeficientes: 

u = a0 + a1*x + a2*y + a3*xy

v = b0 + b1*x + b2*y + b3*xy

*/

typedef double array1[2];

//x es la entrada e y la salida
long inversa(double *x,double *y,long dimension);

void orden2(array1 *datin,array1 *datout,array1 *coef) 
{
	//x= datin[][0], y= datin[][1]
	//u=datout[][0], v=datout[][1]
	//a=  coef[][0], b=  coef[][1]
	
	//1. relleno MAT[] con 1 x y xy
	double  MAT[4][4];
	long i,j,k;
	for (i=0;i<4;i++)
	{
		MAT[0][i]=1.0;
		MAT[1][i]=datin[i][0];
		MAT[2][i]=datin[i][1];
		MAT[3][i]=datin[i][0]*datin[i][1];
	}
	//2. Hallo la inversa
	double *MAT1=new double[4*4];
	i=0;
	for (j=0;j<4;j++)
	{
		for (k=0;k<4;k++)
			MAT1[i++]=MAT[j][k];
	}
	double *MAT2=new double[4*4];
	i=inversa(MAT1,MAT2,4);
	if (i<4)
	{
		printf("\nError: La matriz a invertir es de determinante nulo");
		char c;scanf("%c%c",&c,&c);return;
	}
	//3. Meto la inversa de MAT en MAT:
	i=0;
	for (j=0;j<4;j++)
	{
		for (k=0;k<4;k++)
			MAT[j][k]=MAT2[i++];
	}

	//4. coef=traspuesta_inversa(MAT)*OUT
	i=4*2*sizeof(double);
	memset(coef,0,i);

	for (i=0;i<2;i++)
	{
		for (j=0;j<4;j++)
		{
			for (k=0;k<4;k++)
			{
				coef[j][i]+=MAT[k][j]*datout[k][i];
			}
		}
	}
}

long inversa(double *x,double *y,long dimension)
{//x es la entrada e y la salida
	int i,j,ord;
	double *ptrx,*ptrx0,*ptry,*ptry0,*ptrx00,*ptry00,x0;
	for (ord=0;ord<dimension;ord++)
	{
		//Hacemos elemento diagonal=1
		ptrx0=x+ord*dimension+ord;
		ptry=y+ord*dimension;
		if (!*ptrx0) return ord;
		for (i=0;i<ord;i++)
		 *ptry++/=*ptrx0; //y(ord,i<ord)=y/x(ord,ord)
		*ptry=1./ *ptrx0;   //y(ord,ord)  =1/x(ord,ord)
		ptrx=ptrx0+1;
		for (i=ord+1;i<dimension;i++)
		 *ptrx++ /= *ptrx0; //x(ord,i>ord)=x/x(ord,ord)

		//Hacemos toda la columna "ord" =0 salvo el valor en (ord,ord)
		ptry00=y+dimension*ord;
		ptrx00=x+dimension*ord+ord+1;
		for (j=0;j<dimension;j++)  //todas las filas
		if (j!=ord)          //salvo la ord
		{
			 ptrx=x+j*dimension+ord;x0=*ptrx;
			 ptry=y+j*dimension;ptry0=ptry00;
			 for (i=0;i<ord;i++) //columnas Y desde 0 a ord
				*ptry=(*ptry++)-(*ptry0++)*x0;
			 *ptry=-(*ptry0++)*x0;//columna Y ord;
     
			 ptrx++;ptrx0=ptrx00;
			 for (i=ord+1;i<dimension;i++) //columnas x desde ord a dim
				*ptrx=(*ptrx++)-(*ptrx0++)*x0;
		}
	}//end ord
	return dimension;
}

void main()
{
	double datin[4][2]={ 10,15,  110,20,   111,130,  5,110};
	double datout[4][2]={110,130, 10100,10, 12000,11500, 80,9000};
	double coef[4][2];
	orden2(&datin[0],&datout[0],&coef[0]);
	double w[4];
	long i;
	for (i=0;i<4;i++)
	{
		w[0]=1.0;w[1]=datin[i][0];w[2]=datin[i][1];w[3]=datin[i][0]*datin[i][1];
		double x,y;
		x=0;
		x=coef[0][0]+coef[1][0]*w[1]+coef[2][0]*w[2]+coef[3][0]*w[3];
		printf("x=%lg",x);
		y=0;
		y=coef[0][1]+coef[1][1]*w[1]+coef[2][1]*w[2]+coef[3][1]*w[3];
		printf("\ty=%lg\n",y);
	}
	char c;scanf("%c%c",&c,&c);return;

}