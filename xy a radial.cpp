#include <stdio.h>
#include <math.h>
#define MAXX 255
/*
 matFI[x][y]=K*atan(y/x)  K es tal que el incremento de angulo minimo es un lsb
matDIS[x][y]=K*raiz(x^2+y^2) K es tal que el incremento de distancia es un lsb
matX[DIS][FI]=DIS*cos[FI]
matY[DIS][FI]=DIS*sen[FI]

x,y estan en el intervalo -MAXX a +MAXX
DIS va de -max_DIS a max_DIS
FI  va de -max_FI a +max_FI

El tamaño que ocupan las matrices es:
MAXX:       760     64.3 Mb
MAXX y MAXY=760x480 40   Mb (esperado)
MAXX        255     7.26 Mb 
*/

void main()
{
	double k_atan;
	k_atan=(atan(1.0)-atan((MAXX-1.0)/MAXX));
	short max_atan;
	max_atan=(short) (atan(1e99)/k_atan) +2;
	double k_dis;
	short max_DIS;
	k_dis=sqrt(MAXX*MAXX+MAXX*MAXX)-sqrt(MAXX*MAXX+(MAXX-1.0)*(MAXX-1.0));
	max_DIS=(short) (sqrt(MAXX*MAXX+MAXX*MAXX)/k_dis)+2;

	short *(*matX),*(*matY),*(*matFI),*(*matDIS);
	//dimensionado de matX,matY 
	matX=new short *[max_DIS];
	matY=new short *[max_DIS];
	long ss;
	ss=max_DIS*(max_atan*4+2)*sizeof(short);
	printf("\nmax_DIS = %i",max_DIS);
	short max_FI=max_atan*2;
	printf("\nmax_FI  = %i",max_FI);
	printf("\n matX y matY ocupan        %li bytes = %lg Mbytes",ss,1.0*ss/1024/1024);

	long i,j;
	for (i=0;i<max_DIS;i++)
	{
		matX[i]=new short[max_atan*4+2];matX[i]+=max_atan*2;
		matY[i]=new short[max_atan*4+2];matY[i]+=max_atan*2;
	}
	//llenado de matX, matY
	for (i=0;i<max_DIS;i++)
	{
		for (j=0;j<=max_atan;j++)
		{
			short uu,vv;
			uu=(short) (k_dis*i*cos(k_atan*j)+0.5);
			vv=(short) (k_dis*i*sin(k_atan*j)+0.5);
			matX[i][j]=matX[i][-j]=uu;
			matX[i][j+max_atan]=matX[i][-j-max_atan]=-vv;
			matY[i][j]=vv;
			matY[i][-j]=-vv;
			matY[i][j+max_atan]=uu;
			matY[i][-j-max_atan]=-uu;
		}
	}

	//dimensionado de matDIS,matFI 
	matDIS=new short *[MAXX*2+4];matDIS+=MAXX+1;
	matFI =new short *[MAXX*2+4];matFI+= MAXX+1;

	for (i=-MAXX;i<=MAXX;i++)
	{
		matDIS[i]=new short[MAXX*2+2];matDIS[i]+=MAXX+1;
		matFI[i] =new short[MAXX*2+2];matFI[ i]+=MAXX+1;
	}
	ss=(MAXX*2+4)*(MAXX*2+2)*sizeof(short);
	printf("\n matDIS y matFI ocupan     %li bytes = %lg Mbytes",ss,1.0*ss/1024/1024);
	ss=ss*2+ 2*(max_DIS*(max_atan*4+2)*sizeof(short));
	printf("\n Todas las matrices ocupan %li bytes = %lg Mbytes",ss,1.0*ss/1024/1024); 

	//llenado de matDIS,matFI
	for (i=0;i<=MAXX;i++)
	{
		for (j=0;j<=MAXX;j++)
		{
			short ww;
			ww=(short) (2.0*atan(1e99)/k_atan+0.5);
			double zz;
			zz=sqrt(i*i+j*j);
			short uu,vv;
			uu=(short) (zz/k_dis+0.5);
			matDIS[i][j]=matDIS[-i][j]=matDIS[-i][-j]=matDIS[i][-j]=uu;
			//zz=(atan(j/(1e-99+i)))/k_atan;
			//if ((i==MAXX)&&(j==MAXX))
			//	i=i;
			vv=(short) ((atan(j/(1e-99+i)))/k_atan-0.3);
			matFI[ i][ j]=vv;
			matFI[-i][ j]=ww-vv;
			matFI[ i][-j]=-vv;
			matFI[-i][-j]=vv-ww;
		}
	}

	//Comprobacion:
	double error=0.0;
	for (i=-MAXX;i<=MAXX;i++)
	{
		for (j=-MAXX;j<=MAXX;j++)
		{
			double x;
			x=i-matX[matDIS[i][j]][matFI[i][j]];
			if (x<0) x=-x;
			error+=x;

			x=j-matY[matDIS[i][j]][matFI[i][j]];
			if (x<0) x=-x;
			error+=x;
		}
	}
	printf("\nError medio en la conversion = %lf ",error/(2*MAXX+1.0)/(2*MAXX+1.0));
	char c;scanf("%c%c",&c,&c);

	i=i;

}