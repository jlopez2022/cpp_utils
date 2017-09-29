/* It is stated:
It is kicker using if than % operator
It is kicker using standard functions than #define ones
*/
#include <stdio.h>
#include <iostream>
#include <string.h> //memcpy
#include <math.h>   //floor(),sin, cos,tan
#include <time.h>   //time_t, clock()
#pragma warning(disable:4996) //disable deprecateds
using namespace std;
typedef unsigned char uchar;

//Timing functions and data:
time_t start,stop;
void timer(char *title,int data_size=1) { 	stop=clock();	cout<<title<< " time ="<<(double) (stop-start)/(double) CLOCKS_PER_SEC<< " = " << 1e-6*data_size/( (double)(stop-start)/(double)CLOCKS_PER_SEC ) <<  " Mops/seg"   <<endl; 	start=clock(); }


//If x<0 then x=0. If x>xmax then x=xmax-1:
#define INLIMIT_F0(x,xmax) ( (x)<0 ? 0 : ((x)<(xmax) ? (x) : ((xmax)-1)))    //Va 10x en modo debug. En release es 1x (1.13Gops/s)
int INLIMIT_F1(int x, int xmax) { 	if (x<0) return 0; 	else if (x<xmax) return x; 	else return xmax-1; }
//If x<0 then x=x+xmax. If x>xmax then x=x-xmax:
//The best are F4 and F5. F2 and F3 are very sloooow:
#define INLIMIT_F2(x,xmax) ( ((x)+(xmax)) % (xmax))    
int INLIMIT_F3(int x, int xmax) { 	return (x+xmax) % xmax; }
int INLIMIT_F4(int x, int xmax) { 	if (x<0) return x+xmax; 	else if (x<xmax) return x; 	else return x-xmax; } //Mejor que F2 & F3
#define INLIMIT_F5(x,xmax) ( (x)<0 ? ((x)+(xmax)) : ((x)<(xmax) ? (x) : ((x)-(xmax))))
//tests all INLIMIT_Fx:
void prue_inlimit();

typedef unsigned char byte;
//converts anything to byte:
#define TOBYTE(x)  ( (x)<0 ? 0 : ((x)<=255 ? ((byte)(x)) : (255)    ))
//uses: x=INLIMIT2(x,10,100);
#define INLIMIT2(x,xmin,xmax) ( (x)<(xmin) ? (xmin) : ((x)<(xmax) ? (x) : ((xmax)-1)))     //OJO: ASIGNO max-1 no max!!!
#define INLIMIT3(x,xmin,xmax) ( (x)<(xmin) ? (xmin) : ((x)<=(xmax) ? (x) : (xmax)    ))     //OJO: ASIGNO max no max-1!!!
void prue_inlimit2();


#define ROUND(x) (floor(0.5+x))
#define ABS(a) ((a) < 0 ? (-(a)) : (a))
void prueba_abs();
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
#ifndef __linux__   //Introduce this code at the beginning of main() to increase a lot the speed of cout in windows: 
	char buf[4000]; setvbuf(stdout, buf, _IOFBF, sizeof buf);
#endif

	prueba_abs();//prueba de que no funciona ABS con operacione
	prue_inlimit();//prueba INLIMIT_Fx 
	prue_inlimit2();
	prue_UB();


	{//=======prueba de ABS=============
		printf("======== ini prueba ABS ============\n");
		float f[11]={1.0f,-1.5f,0.0f,1.2f,1.9f,-1.9f,-1.1f,-9.99e30f,-1.199e-07f,1.222e-7f,9.87e30f};
		float g[11],h[11];
		int i;
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
		int a=10,b=7;
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




void prue_inlimit() 
{
	char buf[4000]; setvbuf(stdout, buf, _IOFBF, sizeof buf); //speed of cout $ printf increased

	printf("======== ini prueba INLIMIT_Fx ========\n");
	int x,y,xmax=1020;
	x=10;  y=INLIMIT_F0(x,xmax);printf("x=%li y=%li\n",x,y);
	x=-3;  y=INLIMIT_F0(x,xmax);printf("x=%li y=%li\n",x,y);
	x=1024;y=INLIMIT_F0(x,xmax);printf("x=%li y=%li\n",x,y);
	double x1,y1,xmax1=1020.1;
	x1=10;  y1=INLIMIT_F0(x1,xmax1);printf("x=%lg y=%lg\n",x1,y1);
	x1=-3;  y1=INLIMIT_F0(x1,xmax1);printf("x=%lg y=%lg\n",x1,y1);
	x1=1024;y1=INLIMIT_F0(x1,xmax1);printf("x=%lg y=%lg\n",x1,y1);

	int i=INLIMIT_F5(7,xmax);
	int errors=0;
	for (i=-1000;i<2000;i++)
		if( (INLIMIT_F0(i,xmax)!=INLIMIT_F1(i,xmax))||(INLIMIT_F2(i,xmax)!=INLIMIT_F3(i,xmax))|| (INLIMIT_F2(i,xmax)!=INLIMIT_F4(i,xmax))|| (INLIMIT_F2(i,xmax)!=INLIMIT_F5(i,xmax)) )
		{
			cout << i<<": "<< INLIMIT_F0(i,xmax) << " " << INLIMIT_F1(i,xmax) << " " << INLIMIT_F2(i,xmax) << " " << INLIMIT_F3(i,xmax) << " " << INLIMIT_F4(i,xmax) << " " << INLIMIT_F5(i,xmax) << endl; 
			errors++;
		}
	cout<<"Total errors="<<errors<<endl;

	x=10;
	const int size=100000000;
	start = clock();
	for (i=0;i<size;i++)
		x=INLIMIT_F0(x,xmax);
	cout<<"Value:"<<x<<" ";x=10;
	timer("#INLIMIT_F0:",size);
	for (i=0;i<size;i++)
		x=INLIMIT_F1(x,xmax);
	cout<<"Value:"<<x<<" ";x=10;
	timer("#INLIMIT_F1:",size);
	for (i=0;i<size;i++)
		x=INLIMIT_F2(x,xmax);
	cout<<"Value:"<<x<<" ";x=10;
	timer(" INLIMIT_F2:",size);
	for (i=0;i<size;i++)
		x=INLIMIT_F3(x,xmax);
	cout<<"Value:"<<x<<" ";x=10;
	timer(" INLIMIT_F3:",size);
	for (i=0;i<size;i++)
		x=INLIMIT_F4(x,xmax);
	cout<<"Value:"<<x<<" ";x=10;
	timer(" INLIMIT_F4:",size);
	for (i=0;i<size;i++)
		x=INLIMIT_F5(x,xmax);
	cout<<"Value:"<<x<<" ";x=10;
	timer(" INLIMIT_F5:",size);

	printf("======== fin prueba INLIMIT_Fx ========\n");
	printf("====================================\n");
}

void prue_UB(void)
	{	//Prueba de UB 
		printf("======== ini prueba UB  ============\n");
		printf("Extrae dato de matriz 2D comprobando limites\n");

		const int XMAX=200,YMAX=64;
		double image1[XMAX*YMAX];
		int x,y;
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

//#define INLIMIT2(x,xmin,xmax) ( x<xmin ? xmin : (x<xmax ? x : xmax-1))    
void prue_inlimit2()
{
	printf("\n======== ini prueba INLIMIT2  ============\n");
	printf("====================================\n");

	{
		double x1,y1;
		x1 = INLIMIT2(10.0 - 20.0, -3, 10 + 2); y1 = -3; cout << "x1=" << x1 << " <> " << y1 << "  "; if (y1 == x1) cout << "OK\n"; else  cout << "NOK!!!!!!!!!!!\n";
		x1 = INLIMIT2(10.0 - 20.0, -12 + 8, 10 + 2); y1 = -4; cout << "x1=" << x1 << " <> " << y1 << "  "; if (y1 == x1) cout << "OK\n"; else  cout << "NOK!!!!!!!!!!!\n";
		x1 = INLIMIT2(10.0 + 20.2, -12 + 8, 10 + 2); y1 = 11; cout << "x1=" << x1 << " <> " << y1 << "  "; if (y1 == x1) cout << "OK\n"; else  cout << "NOK!!!!!!!!!!!\n";
		x1 = INLIMIT2(20.0 - 19.2, -12 + 8, 10 + 2); y1 = 20.0 - 19.2; cout << "x1=" << x1 << " <> " << y1 << "  "; if (y1 == x1) cout << "OK\n"; else cout << "NOK!!!!!!!!!!!\n";

	}

	int errores = 0;
	{
		double x1, x2,xmin1, xmax1;
		xmin1 = -10.51; xmax1 = 12.21;
		for (int i = 0; i < 300; i++)
		{
			x1 = -12.0 + 0.1*i;
			x2 = INLIMIT2(x1, xmin1, xmax1);
			if (x2 < xmin1)
			{
				cout << "error:" << x2 << " es menor que " << xmin1 << endl;
				errores++;
			}
			if (x2 > xmax1)
			{
				cout << "error:" << x2 << " es mayor que " << xmax1 << endl;
				errores++;
			}
		}
	}
	{
		int x1, x2, xmin1, xmax1;
		xmin1 = -105; xmax1 = 122;
		for (int i = 0; i < 300; i++)
		{
			x1 = -120 + i;
			x2 = INLIMIT2(x1, xmin1, xmax1);
			if (x2 < xmin1)
			{
				cout << "error:" << x2 << " es menor que " << xmin1 << endl;
				errores++;
			}
			if (x2 > xmax1)
			{
				cout << "error:" << x2 << " es mayor que " << xmax1 << endl;
				errores++;
			}
		}
	}
	cout << "Errores de INLIMIT2=" << errores << endl;
	printf("\n======== fin prueba INLIMIT2  ============\n");
	printf("====================================\n");
}


void prueba_abs()
{
	{
		cout << "=========== double ==========" << endl;
		double a = -7.0;
		double b = -3.0;
		double x;

		x = ABS(a - b); cout << "ABS(" << a << "- " << b << ")=" << x << endl;
		x = ABS(b - a); cout << "ABS(" << b << "- " << a << ")=" << x << endl;

		a = 7.0; b = 3.0;
		x = ABS(a - b); cout << "ABS(" << a << "- " << b << ")=" << x << endl;
		x = ABS(b - a); cout << "ABS(" << b << "- " << a << ")=" << x << endl;
	}
	{
		cout << "=========== double ==========" << endl;
		double *a = new double[7];
		double *b = new double[7];
		double x;

		a[1] = -7.0; b[1] = -3.0;
		x = ABS(a[1] - b[1]); cout << "ABS(" << a[1] << "- " << b[1] << ")=" << x << endl;
		x = ABS(b[1] - a[1]); cout << "ABS(" << b[1] << "- " << a[1] << ")=" << x << endl;

		a[1] = 7.0; b[1] = 3.0;
		x = ABS(a[1] - b[1]); cout << "ABS(" << a[1] << "- " << b[1] << ")=" << x << endl;
		x = ABS(b[1] - a[1]); cout << "ABS(" << b[1] << "- " << a[1] << ")=" << x << endl;
	}

	{
		cout << "=========== uchar-1 ==========" << endl;
		uchar *a = new uchar[7];
		uchar *b = new uchar[7];
		int x;

		a[1] = 7; b[1] = 3;
		x = ABS(a[1] - b[1]); cout << "ABS(" << a[1] << "- " << b[1] << ")=" << x << endl;
		x = ABS(b[1] - a[1]); cout << "ABS(" << b[1] << "- " << a[1] << ")=" << x << endl;
	}

	{
		cout << "=========== uchar-2 ==========" << endl;
		uchar a;
		uchar b;
		int x;

		a = 7; b = 3;
		x = ABS(a - b); cout << "ABS(" << a << "- " << b << ")=" << x << endl;
		x = ABS(b - a); cout << "ABS(" << b << "- " << a << ")=" << x << endl;
	}
}