//Project->Settings->link->output en reserve poner 0x4000000 (64Mb)
//Meto diferencia de datos en vez de datos

//#include <cv.h>
//#include <cxcore.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "stat.h"
#define DIM 3 //bgr
#define MAXCAP 40000
/*#define zX1 389
#define Y1 132
#define X2 485
#define Y2 260 */





void aleatorio(long *matriz,long longitud);


//====class c_foto
class c_simil
{
public:
	//datos
    long framex,framey;//Informacion de la foto
	IplImage* img;
	StatC *stat;

	double hallasimilaridad(long x,long y,long dx,long dy);//compara trozo de foto entre (x,y) y (x-dx,y-dy) contra el trozo (x-dx,y-dy) y (x-2dx,y-2dy)
	double convol1(uchar *mat1,uchar *mat2,long size);//Da 1 si mat1[]=mat2[]
	double convol1(short *mat1,short *mat2,long size);//Da 1 si mat1[]=mat2[]

	long deltax,deltay;
	uchar *bgr;

	void pintacuadro(uchar* mat,long xmax,long ymax,char *filename);
	void pintacuadro(short* mat,long xmax,long ymax,char *filename);
	c_simil(char *filename,long deltax1,long deltay1);
	~c_simil(void);
};
//*** class c_foto

//===class dibuja
class c_dibuja
{
public:
	IplImage* img;
	c_dibuja(void) 	{   cvNamedWindow("dibuja",1);img=cvCreateImage(cvSize(1000,500),IPL_DEPTH_32F,3);borra();	}
	~c_dibuja(void) {	cvDestroyWindow("dibuja"); }
	void borra();
	void pinta(double *y,long y_size,uchar B=0,uchar G=255,uchar R=0);
	void pinta( uchar *u,long y_size,uchar B=0,uchar G=255,uchar R=0);
	void pruebadibujo();
}*dibujo;
//***class dibuja


//=== MAIN
int main()
{

//	char file1[1024]="imagen2.jpg"; 
	char file1[1024]="IMG_8064.JPG";
	c_simil *simil=new c_simil(file1,1,1);//*/
	double r;

	long x,d;

	for (x=430;x<700;x++)
	{
		printf("\n");
		for (d=3;d<10;d++)
		{
			r=simil->hallasimilaridad(x,900,d,d);
			printf("%10lf ",r);
		}
	}

		
	printf("\nFIN");
	getchar();getchar();


	delete simil;
    return 0;
}



c_simil::c_simil(char *filename,long deltax1,long deltay1)
{
	deltax=deltax1;deltay=deltay1;
    cvNamedWindow("Capturafoto",1);
	img = cvLoadImage(filename,1);
    if( (img = cvLoadImage(filename,1)) == 0 )
	{
		printf("No puedo abrir %s",filename);getchar();getchar();
	}
	framex=img->width;
	framey=img->height;
	printf("\n%s = %li x %li",filename,framex,framey);
    //create windows for output images
    cvShowImage("Capturafoto",img);
	cvWaitKey(20);
	stat=new StatC();
	stat->Borra();
	bgr=(uchar *) img->imageData;
}

c_simil::~c_simil(void)
{
    cvDestroyWindow("Capturafoto"); 
	delete stat;
}

double c_simil::hallasimilaridad(long x,long y,long dx,long dy)//compara trozo de foto entre (x,y) y (x-dx,y-dy) contra el trozo (x-dx,y-dy) y (x-2dx,y-2dy)
{
	long index1=DIM*( x-dx   +(y-  dy)*framex );
	long index2=DIM*( x-2*dx +(y-2*dy)*framex );
	if ( index2<0 )
	{
		printf("\nERROR en c_simil::hallasimilaridad, x-2dx ó y-2dy es menor que 0");
		getchar();getchar();
		return 0;
	}

	long size=dx*dy*DIM;
	short *mat1=new short[size];
	short *mat2=new short[size];

	long iy,ix,ii,ii2,di;
	di=(dy*framex+dx)*DIM;
	for(iy=0;iy<dy;iy++)
	{
		//memcpy(mat1+iy*dx*DIM,bgr+index1+iy*framex*DIM,dx*DIM);
		//memcpy(mat2+iy*dx*DIM,bgr+index2+iy*framex*DIM,dx*DIM);
		for (ix=0;ix<dx*DIM;ix++)
		{
			ii =(DIM*iy*dx    +ix);
			ii2=(DIM*iy*framex+ix);
			mat1[ii]=bgr[index1+ii2]-bgr[index1+ii2-di];
			mat2[ii]=bgr[index2+ii2]-bgr[index2+ii2-di];
		}
	}
	double r;
	r=this->convol1(mat1,mat2,size);
	/*
	cvLine(img, cvPoint(x-dx,y-dy), cvPoint(x-dx,y   ), cvScalar(255,255,0), 2);//ancho 2 por si hay compresion de imagen, que se vea la linea
	cvLine(img, cvPoint(x-dx,y   ), cvPoint(x,y      ), cvScalar(255,255,0), 2);//ancho 2 por si hay compresion de imagen, que se vea la linea
	cvLine(img, cvPoint(x   ,y   ), cvPoint(x,y-dy   ), cvScalar(255,255,0), 2);//ancho 2 por si hay compresion de imagen, que se vea la linea
	cvLine(img, cvPoint(x   ,y-dy), cvPoint(x-dx,y-dy), cvScalar(255,255,0), 2);//ancho 2 por si hay compresion de imagen, que se vea la linea
	cvLine(img, cvPoint(x-2*dx,y-2*dy),cvPoint(x-2*dx,y-dy),  cvScalar(255,0,255), 2);//ancho 2 por si hay compresion de imagen, que se vea la linea
	cvLine(img, cvPoint(x-2*dx,y-dy)  ,cvPoint(x-dx,  y-dy),  cvScalar(255,0,255), 2);//ancho 2 por si hay compresion de imagen, que se vea la linea
	cvLine(img, cvPoint(x-dx,  y-dy)  ,cvPoint(x-dx,y-2*dy),  cvScalar(255,0,255), 2);//ancho 2 por si hay compresion de imagen, que se vea la linea
	cvLine(img, cvPoint(x-dx,  y-2*dy),cvPoint(x-2*dx,y-2*dy),cvScalar(255,0,255), 2);//ancho 2 por si hay compresion de imagen, que se vea la linea
	cvShowImage( "Capturafoto", img );
	cvWaitKey(20);

	pintacuadro(mat1,dx,dy,"mat1");
	pintacuadro(mat2,dx,dy,"mat2");
	cvDestroyWindow("mat1");
	cvDestroyWindow("mat2");
	*/
	delete[] mat1,mat2;
	return r;
}


double c_simil::convol1(uchar *mat1,uchar *mat2,long size) 
{//ojo, el ancho real es DIM*ancho al haber DIM colores o dimensiones
	long i;
	double sx,sy,sxy;
	sx=sy=sxy=1e-99;
	double convol=0.0;
	for (i=0;i<size;i++)
	{
		sx+=mat1[i]*mat1[i];sy+=mat2[i]*mat2[i];//Conque se halle sx una vez bastaria, 
		sxy+=mat1[i]*mat2[i];
	}
	convol=1.0*sxy*sxy/sx/sy;
	return convol;
}

double c_simil::convol1(short *mat1,short *mat2,long size) 
{//ojo, el ancho real es DIM*ancho al haber DIM colores o dimensiones
	long i;
	double sx,sy,sxy;
	sx=sy=sxy=1e-99;
	double convol=0.0;
	for (i=0;i<size;i++)
	{
		sx+=mat1[i]*mat1[i];sy+=mat2[i]*mat2[i];//Conque se halle sx una vez bastaria, 
		sxy+=mat1[i]*mat2[i];
	}
	convol=1.0*sxy*sxy/sx/sy;
	return convol;
}


void c_simil::pintacuadro(uchar* mat,long xmax,long ymax,char *filename)
{//Coge de img un cuadro en x1,y1->x2,y2 y lo pinta
	IplImage* imgx=cvCreateImage(cvSize(xmax,ymax),IPL_DEPTH_8U,3);
	uchar *bgr2=(uchar *) imgx->imageData;
	//2.0Pinto el cuadrado:
	memcpy(bgr2,mat,xmax*ymax*DIM);
//	cvSaveImage(filename,imgx);
	cvNamedWindow(filename,1);
    cvShowImage(filename,imgx);
	long i=cvWaitKey(0);
    cvDestroyWindow(filename); 
	cvReleaseImage(&imgx); 
}

void c_simil::pintacuadro(short* mat,long xmax,long ymax,char *filename)
{//Coge de img un cuadro en x1,y1->x2,y2 y lo pinta
	IplImage* imgx=cvCreateImage(cvSize(xmax,ymax),IPL_DEPTH_8U,3);
	uchar *bgr2=(uchar *) imgx->imageData;
	//2.0Pinto el cuadrado:
	memcpy(bgr2,mat,xmax*ymax*DIM);
	long i;
	for (i=0;i<xmax*ymax*DIM;i++)
	{
		bgr2[i]=(uchar) mat[i];
	}
//	cvSaveImage(filename,imgx);
	cvNamedWindow(filename,1);
    cvShowImage(filename,imgx);
	i=cvWaitKey(0);
    cvDestroyWindow(filename); 
	cvReleaseImage(&imgx); 
}




void c_dibuja::pinta(double *y,long y_size,uchar B,uchar G,uchar R)
{
	long i;
	double ymax=-1e99,ymin=1e99;
	for (i=0;i<y_size;i++)
	{
		if (ymax<y[i])
			ymax=y[i];
		if (ymin>y[i])
			ymin=y[i];
	}
	double p=500.0/(ymax-ymin);

	long yant,y2,xant,x2;
	yant=(long) ((y[0]-ymin)*p);
	xant=0;
	for (i=1;i<y_size;i++)
	{
		x2=(long) (1000.0*i/y_size);
		y2=(long) (500-(y[i]-ymin)*p);
		cvLine(img, cvPoint(xant,yant), cvPoint(x2,y2), cvScalar(B,G,R), 1);
		yant=y2;xant=x2;
	}
    cvShowImage("dibuja",img);
	yant=cvWaitKey(0);
}


void c_dibuja::pinta(uchar *u,long y_size,uchar B,uchar G,uchar R)
{
	long i;
	double ymax=-1e99,ymin=1e99;
	double *y=new double[y_size]; 
	for (i=0;i<y_size;i++)
	{
		y[i]=(double) u[i];
		if (ymax<y[i])
			ymax=y[i];
		if (ymin>y[i])
			ymin=y[i];
	}
	double p=500.0/(ymax-ymin);

	long yant,y2,xant,x2;
	yant=(long) ((y[0]-ymin)*p);
	xant=0;
	for (i=1;i<y_size;i++)
	{
		x2=(long) (1000.0*i/y_size);
		y2=(long) ((y[i]-ymin)*p);
		cvLine(img, cvPoint(xant,yant), cvPoint(x2,y2), cvScalar(B,G,R), 1);
		yant=y2;xant=x2;
	}
    cvShowImage("dibuja",img);
	yant=cvWaitKey(0);
}


void c_dibuja::borra()
{
	long i;
	for (i=0;i<1000;i++)   cvLine(img, cvPoint(0,0), cvPoint(i,500), cvScalar(0,0,0), 1);
	for (i=0;i<1000;i+=10) cvLine(img, cvPoint(i,0), cvPoint(i,500), cvScalar(0,0,255), 1);
	for (i=0;i<500;i+=10) cvLine(img, cvPoint(0,i), cvPoint(1000,i), cvScalar(0,0,255), 1);
	for (i=0;i<1000;i+=50) cvLine(img, cvPoint(i,0), cvPoint(i,500), cvScalar(255,255,255), 1);
	for (i=0;i<500;i+=50) cvLine(img, cvPoint(0,i), cvPoint(1000,i), cvScalar(255,255,255), 1);
}


void c_dibuja::pruebadibujo()
{
	double y[100];
	long i;
	for (i=0;i<100;i++)
		y[i]=120*sin(i*3.1416*10/100);
	dibujo->pinta(&y[0],100);
}

void aleatorio(long *matriz,long longitud)
{//Mete en matriz indices aleatorios de 0 a longitud
	long i;
	for (i=0;i<longitud;i++) //*ptr++=i;//relleno la matriz mat[]=0,1,2...
		matriz[i]=i;

	long x,dat;
	for (;longitud>1;)
	{
		longitud--;
		x=(long) (1.0*longitud*rand()/RAND_MAX);
		dat=matriz[longitud];
		matriz[longitud]=matriz[x];
		matriz[x]=dat;
	}
}
