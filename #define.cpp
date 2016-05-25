#include <stdio.h>
#include <string.h> //memcpy
#include <math.h>   //floor(),sin, cos,tan
#include <time.h>   //no hace falta, solo para medir performance
#pragma warning(disable:4996) //o cualquier otro 

//mete a x entre 0 y xmax:
#define INLIMIT(x,xmax) ( x<0 ? 0 : (x<xmax ? x : xmax-1))    //Va 10x en modo debug. En release es 1x (1.13Gops/s)
long INLIMIT_F(long x,long xmax);//funcion equivalente a INLIMIT
void prue_inlimit();

#define ROUND(x) (floor(0.5+x))
#define ABS(a) ((a) < 0 ? (-a) : (a))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define SWAP(t,a,b) ( (t) = (a), (a) = (b), (b) = (t) ) 
//Extrae dato de matriz 2D comprobando limites:
//UB(image,x,y,W,H) = image[y*W+x] pero comprobando antes que 0<=y<H  0<=x<W
#define UB(image,x,y,W,H) ((image)[( (y)>=H ? H-1 : ((y)<0 ? 0:(y)) )*(W)+( (x)>=W ? W-1 : ((x)<0 ? 0 : (x)) )])
void prue_UB(void);

//Entrega diferencia en valor absoluto y diferencia al cuadrado
//UDIF tarda EL DOBLE que fabs() empleado sobre matrices pero no usa libreria math.h
#define UDIF(a,b) ((a) > (b) ? (a-b) : (b-a))
//DIF2 tarda el doble si se emplea sobre matrices que usar x=a-b y luego usar x*x
#define DIF2(a,b) ( (a-b)*(a-b) )

#define PI 3.1415926535897932384626433832795
#define sinpi(a) (sin(PI*(a)))
#define cospi(a) (cos(PI*(a)))
#define tanpi(a) (tan(PI*(a)))



int main()
{
	prue_inlimit();//prueba inlimit 
	prue_UB();


	{//=======prueba de ABS=============
		printf("======== ini prueba ABS ============\n");
		float f[11]={1.0f,-1.5f,0.0f,1.2f,1.9f,-1.9f,-1.1f,-9.99e30f,-1.199e-07f,1.222e-7f,9.87e30f};
		float g[11],h[11];
		long i;
		memcpy(g,f,11*sizeof(float));
		memcpy(h,f,11*sizeof(float));
		for (i=0;i<11;i++)
		{
			if (g[i]<0) g[i]=-g[i];
			h[i]=ABS(h[i]) ;
		}
		for (i=0;i<11;i++)
			printf("%g : \t%g : \t%g\n",f[i],g[i],h[i]);
		printf("\n======== fin prueba ABS ===========\n");
		printf(  "===================================\n");
	}

	printf("==== ini prueba MIN MAX SWAP ======\n");
	double a=1.1,b=2.5,temp;
	printf("\na=%lg b=%lg",a,b);
	temp=MIN(a,b);
	printf("\nMIN=%lg",temp);
	temp=MAX(a,b);
	printf("\nMAX=%lg",temp);
	SWAP(temp,a,b);
	printf("\na=%lg b=%lg",a,b);

	__int16 c=132,d=-15,t2;
	printf("\nc=%li d=%li",c,d);
	t2=MIN(c,d);
	printf("\nMIN=%li",t2);
	t2=MIN(d,c);
	printf("\nMIN=%li",t2);
	t2=MAX(c,d);
	printf("\nMAX=%li",t2);
	t2=MAX(d,c);
	printf("\nMAX=%li",t2);
	__int16 temp2;
	SWAP(temp2,c,d);
	printf("\nc=%li d=%li",c,d);

	printf("\n\n ROUND:");
	a= 1.1;b=ROUND(a);printf("\nROUND(%5lg)=%lg",a,b);
	a=-1.1;b=ROUND(a);printf("\nROUND(%5lg)=%lg",a,b);
	a= 1.8;b=ROUND(a);printf("\nROUND(%5lg)=%lg",a,b);
	a=-1.8;b=ROUND(a);printf("\nROUND(%5lg)=%lg",a,b);
	printf("\n==== fin prueba MIN MAX SWAP ======\n");
	printf(  "===================================\n");

	{
		printf("=======  ini prueba UDIF DIF2 =====\n");
		printf("\n\n UDIF y DIF2");
		long a=10,b=7;
		double x=10.2,y=12.4;

		a=10;b=100;printf("\na=%li b=%li UDIF=%li",a,b,UDIF(a,b)); 
		a=99;b= 23;printf("\na=%li b=%li UDIF=%li",a,b,UDIF(a,b)); 
		a=10;b=100;printf("\na=%li b=%li DIF2=%li",a,b,DIF2(a,b)); 
		a=99;b= 23;printf("\na=%li b=%li DIF2=%li",a,b,DIF2(a,b)); 

		x=10.2;y=12.4;printf("\nx=%lg y=%lg UDIF=%lg",x,y,UDIF(x,y)); 
		x=23.5;y=-1.2;printf("\nx=%lg y=%lg UDIF=%lg",x,y,UDIF(x,y)); 
		x=10.2;y=12.4;printf("\nx=%lg y=%lg DIF2=%lg",x,y,DIF2(x,y)); 
		x=23.5;y=-2.6;printf("\nx=%lg y=%lg DIF2=%lg",x,y,DIF2(x,y)); 
		printf("\n=======  fin prueba UDIF DIF2 =====\n");
		printf(  "===================================\n");	}

	{
		printf(  "====== ini sinpi cospi tanpi ======\n");
		double x,y;
		x=2.0*asin(1.0);
		y=sin(x);
		printf("Pi=%.50lg\n",x);
		printf("sin(pi)=%.50lg\n",y);
		x=sinpi(0.25);
		y=sin(PI*0.25);
		printf("sin( PI/4): x =%.50lg y =%.50lg\n",x,y);

		x=cospi(0.25);
		y=cos(PI*0.25);
		printf("cos( PI/4): x =%.50lg y =%.50lg\n",x,y);

		x=tanpi(0.25);
		y=tan(PI*0.25);
		printf("tan( PI/4): x =%.50lg y =%.50lg\n",x,y);

		x=sinpi(0.75);
		y=sin(PI*0.75);
		printf("sin(3PI/4): x =%.50lg y =%.50lg\n",x,y);

		x=cospi(0.75);
		y=cos(PI*0.75);
		printf("cos(3PI/4): x =%.50lg y =%.50lg\n",x,y);

		x=tanpi(0.75);
		y=tan(PI*0.75);
		printf("tan(3PI/4): x =%.50lg y =%.50lg\n",x,y);

		printf(  "====== fin sinpi cospi tanpi ======\n");
	}

	printf("\n\n===FIN===");getchar();getchar();
	return 1;
}


long INLIMIT_F(long x,long xmax)//funcion equivalente a INLIMIT
{
	if (x<0) return 0;
	else if (x<xmax) return x;
	else return xmax-1;
}

void prue_inlimit() 
{
	printf("======== ini prueba INLIMIT ========\n");
	long x,y,xmax=1020;
	x=10;  y=INLIMIT(x,xmax);printf("x=%li y=%li\n",x,y);
	x=-3;  y=INLIMIT(x,xmax);printf("x=%li y=%li\n",x,y);
	x=1024;y=INLIMIT(x,xmax);printf("x=%li y=%li\n",x,y);
	double x1,y1,xmax1=1020.1;
	x1=10;  y1=INLIMIT(x1,xmax1);printf("x=%lg y=%lg\n",x1,y1);
	x1=-3;  y1=INLIMIT(x1,xmax1);printf("x=%lg y=%lg\n",x1,y1);
	x1=1024;y1=INLIMIT(x1,xmax1);printf("x=%lg y=%lg\n",x1,y1);

	long i,j;
	time_t start, stop;

	x=10;
	start = clock();
	for (i=0;i<100;i++)
		for(j=0;j<1000000L;j++)
		{
			x+=10;
			x=INLIMIT(x,xmax);
		}
	stop=clock();
	printf("DEFINE  INLIMIT Gigagaoperaciones/segundo = %lg\n", 0.1*CLOCKS_PER_SEC / (stop - start));
	x=10;
	start = clock();
	for (i=0;i<100;i++)
		for(j=0;j<1000000L;j++)
		{
			x+=10;
			x=INLIMIT_F(x,xmax);
		}
	stop=clock();
	printf("FUNCION INLIMIT Gigagaoperaciones/segundo = %lg\n", 0.1*CLOCKS_PER_SEC / (stop - start));
	printf("======== fin prueba INLIMIT ========\n");
	printf("====================================\n");
}

void prue_UB(void)
	{	//Prueba de UB 
		printf("======== ini prueba UB  ============\n");
		printf("Extrae dato de matriz 2D comprobando limites\n");

		const int XMAX=200,YMAX=64;
		double image1[XMAX*YMAX];
		long x,y;
		for (y=0;y<YMAX;y++)
		for (x=0;x<XMAX;x++)
		{
			image1[y*XMAX+x]=100*y+x;
		}

		/*for (y=0;y<YMAX;y++)
		{
			for (x=0;x<XMAX;x++)
			{
				printf("%5f ",image1[y*XMAX+x]);
			}
			printf("\n");
		}
		printf("\n");*/
		y=-1;
		for (x=-2;x<6;x++)
		{
			printf("\nxy= %2i %2i UB=%f",x,y,UB(image1,x,y,XMAX,YMAX));
		}
		printf("\n======== fin prueba UB  ============\n");
		printf(  "====================================\n");
	}