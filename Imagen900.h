/*
usando fputwc y fgetwc (es el doble de rápido)
Como Imagen9.h pero tipo int
Ademas crea fichero bmp !!
probado
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char byte;
typedef unsigned long DWORD;

class Imagen
   {
   public:
   Imagen(char *fichero);
   ~Imagen();
   void Lee();
   void generabmp(int *img,long xmax,long ymax,char *fichero);
   int *imagen;//matriz que contiene la imagen. Usar como b=imagen[y*XMAX3+3*x] g=imagen[y*XMAX3+3*x+1] r=imagen[y*XMAX3+3*x+2]
   long XMAX,YMAX,XMAXF,XMAX3,Colores,Pixels,Size,bits; //Size=XMAXF*YMAX bits=bits/pixel 
   //XMAXF es el ancho en bytes de la matriz a representar.
   // = minimo mayor que 3*XMAX que es multiplo de 4
   //XMAX=num pixels horizontales
   //YMAX=numero de filas
   //Num colores= XMAX*3*YMAX =XMAX3*YMAX
   //Num de pixels=XMAX*YMAX
   void ToYCbCr();
   void ToBGR();

   void error(double x,char *linea1="",char *linea2="",char *linea3="",char *linea4="",char *linea5="");

   private:
   FILE *stream;
   //XMAXF es el ancho en bytes de la matriz a representar.
   //XMAXF = minimo mayor que 3*XMAX que es multiplo de 4
   long lee4bytes(byte *ptr);
   long leeNbytes(byte *ptr,int n); // lee n bytes de ficheros .BMP
   void LeeCabecera();
   };

Imagen::Imagen(char *fichero2)
	{
	char fichero[256];
	strcpy(fichero,fichero2);
	//strcpy(fichout,"c:\\ajavier\\c++\\imagen\\ficheros estandard\\");	//fichout=files/
	if (!(stream=fopen(fichero,"rb")))
		strcat(fichero,".bmp");		//fichero=files/mallorca.bmp
	if (!(stream=fopen(fichero,"rb")))
	{
	  error(-1,"No se puede abrir ",fichero);
	  exit(0xFFFF);
	}
	LeeCabecera();
	printf("\nFichero:%s %i x %i x %i",fichero,XMAX,YMAX,bits);
	imagen=new int[YMAX*XMAX3+1];//el +1 es por si se lee un byte de mas
	Pixels=XMAX*YMAX;
	Colores=Pixels*3;
}//Imagen

Imagen::~Imagen()
{
   fclose(stream);
	delete[] imagen;
}

void Imagen::Lee()
{
   int x,y,delta=XMAXF-XMAX3;
   int *ptr=imagen;
   for (y=0;y<YMAX;y++)
   {
	   int j;
	   for(x=0;x<XMAX3;x+=2)
	   {
		   j=fgetwc(stream);
		   *ptr++=(j & 0xFF);
		   *ptr++=j>>8;
	   }
	   if (x>XMAX3) ptr--;
	   for (;x<XMAXF;x++)
		  fgetc(stream);
       if (feof(stream))
	  	if (y<YMAX)
		{
			printf("Error:fin de fichero en fila %i",y);
			char c;
			scanf("%c%c",&c,&c);
			y=YMAX;
		}
   }
}

			


void Imagen::ToYCbCr()
{
   int r,g,b;
   int x,y;
   int *ptr;
   ptr=imagen;
   for (y=0;y<YMAX;y++)
   {
	   for(x=0;x<XMAX;x++)
	   {
		  b=*ptr++;
		  g=*ptr++;
		  r=*ptr++;
		  *(ptr-3)=(byte) (0.299*r+0.587*g+0.114*b+0.4);//Y
		  *(ptr-2)=(byte) (128.4-0.1687*r-0.3313*g+0.5*b);//Cb
		  *(ptr-1)=(byte) (128.4+0.5*r-0.4187*g-0.0813*b);//Cr
	   }
   }
}

void Imagen::ToBGR()
{
   int Y,Cb,Cr;
   int x,y;
   int *ptr=imagen;
   for (y=0;y<YMAX;y++)
   {
	   for(x=0;x<XMAX;x++)
	   {
		  Y =*ptr++;
		  Cb=*ptr++;
		  Cr=*ptr++;
		  *(ptr-3)=(byte) (-178.654+Y+1.4*Cr);
		  *(ptr-2)=(byte) (135.79+Y-0.34414*Cb-0.71414*Cr);
		  *(ptr-1)=(byte) (-225.958+Y+1.77*Cb);
	   }
   }
}


void Imagen::LeeCabecera()
//Esta funcion lee la cabecera del fichero .BMP
//Es una matriz byte cabecera[n], siendo n>=0x1A
{
   byte cabecera[0x436];
   long i,offset;
   for (i=0;i<0x1A;i++)
      cabecera[i]=(byte) fgetc(stream);

   offset=lee4bytes(&cabecera[0x0A]);
   if ((offset!=0x36) && (offset!=0x1A) && (offset!=0x436))
      error((double) offset,"Error, el fichero no es BMP win/DOS.Offset distinto de 0x36,1A,436=");
   for (i=0x1A;i<offset;i++)
      cabecera[i]=(byte) fgetc(stream);
   if (offset==0x1A)
      {
      XMAX=leeNbytes(&cabecera[0x12],2);
      YMAX=leeNbytes(&cabecera[0x14],2);
      }
   else
      {
      XMAX=lee4bytes(&cabecera[0x12]);
      YMAX=lee4bytes(&cabecera[0x16]);
      }
   if ((offset>0x1A)&&(cabecera[0x1C]==8)) XMAX3=XMAX;
   else XMAX3=XMAX*3;
   XMAXF=XMAX3;
   if (XMAXF % 4)
      XMAXF=XMAXF+4- ( XMAXF % 4 );
   Size=XMAXF*YMAX;
   if (offset<=0x1A) 
	   bits=cabecera[0x18];
   else
	   bits=cabecera[0x1C]; 
   if ((bits!=8) && (bits!=24))
      error(0,"No se leer bmp de cabeceras!=8 o 24 bits/pixel");
}

long Imagen::lee4bytes(byte *ptr) // lee los DWORD de ficheros .BMP
{
   int i;
   long x=0;
   for (i=0;i<4;i++)
      x+=((long) *ptr++)<<(i*8);
   return x;
}


long Imagen::leeNbytes(byte *ptr,int n) // lee n bytes de ficheros .BMP
{
   int i;
   long x=0;
   for (i=0;i<n;i++)
      x+=((long) *ptr++)<<(i*8);
   return x;
}

//Esta funcion crea la cabecera del fichero .BMP y lo pone todo
void Imagen::generabmp(int *img,long xmax,long ymax,char *fichero)
{
	if (!strstr(fichero,".bmp"))
		error(-1,fichero," no tiene la extension .bmp");
	FILE *strout=fopen(fichero,"wb");
	if (!strout)
		error(-1,"No se puede abrir",fichero);
   byte cabecera[0x36],*ptr;
   long i,m;
   for (i=0;i<0x36;i++) cabecera[i]=0;

   //Cabecera:
   cabecera[0]=0x42;cabecera[1]=0x4D;

   long xmaxf=xmax*3;
   if (xmaxf % 4)
      xmaxf=xmaxf+4- ( xmaxf % 4 );
   long size=xmaxf*ymax;

   m=xmaxf*ymax+0x36;
   for (i=0;i<4;i++) cabecera[i+2]=(m>>(8*i)) & 0xFF;  
   cabecera[10]=0x36;cabecera[14]=0x28;
   //Segunda fila:
   m=xmax;
   for (i=0;i<4;i++) cabecera[i+0x12]=(m>>(8*i)) & 0xFF;  
   m=ymax;
   for (i=0;i<4;i++) cabecera[i+0x16]=(m>>(8*i)) & 0xFF;  
   cabecera[0x1A]=0X1;cabecera[0x1C]=0X18;
   //Tercera fila:
   m=xmaxf*ymax;
   for (i=0;i<4;i++) cabecera[i+0x22]=(m>>(8*i)) & 0xFF;  
   cabecera[0x26]=0x3C;cabecera[0x27]=0x0F; //100ppp eje x
   cabecera[0x2A]=0x3C;cabecera[0x2B]=0x0F; //100ppp eje y

   ptr=cabecera;
   for (i=0;i<0x36;i++)
      fputc((int) *ptr++,strout);
   //El resto es la matriz BGR (mas los ceros)
   int *ptr2=img;
	for (long y=0;y<ymax;y++)
	{       long x;
		for (x=0;x<xmax*3;x++)
		{
			fputc(*ptr2++,strout);
		}
		for (long xx=x;xx<xmaxf;xx++)
			fputc(0,strout);
	}
	fclose(strout);
}


void Imagen::error(double x,char *linea1,char *linea2,char *linea3,char *linea4,char *linea5)
{
   char c;
   printf("\nError:%s%s%s%s%s",linea1,linea2,linea3,linea4,linea5);
   if (x!=-1.)
      printf("%f",x);
   scanf("%c%c",&c,&c);
   _fcloseall();
   exit(-2);
}
/*===============================================
Imagen 536x385 (0x218,0x181) con offset=1A 
      0  1  2  3  4  5  6  7   8  9  A  B  C  D  E  F
0000  42 4d 62 72 09 00 00 00  00 00 1A 00 00 00 0C 00
0010  00 00 18 02 81 01 01 00  18 00 FF FF FF FF FF FF

Imagen 1084x778 (0x43C,0x30A) con offset=1A 
      0  1  2  3  4  5  6  7   8  9  A  B  C  D  E  F
0000  42 4D 22 9b 26 00 00 00  00 00 1A 00 00 00 0C 00
0010  00 00 3C 04 0A 03 01 00  18 00 FF FF FF FF FF FF

*/
/*
void main(void)
{
	char imagen[256];
	//Imagen *Im;
	//GeneralC gen;

	printf("Imagen:");scanf("%s",imagen);
	//Im=new Imagen(imagen);
	Imagen Im(imagen);
	Im.Lee();
	Im.ImprimeCabecera();
	Im.ImprimeMatriz(&Im.B[0][0],&Im.G[0][0],&Im.R[0][0]);
	printf("\nImagen:%s %i x %i x %i",imagen,Im.XMAX,Im.YMAX,Im.bits);
	//if (Im->bits!=24) 
	//	gen.error(2,Im->bits,"Imagen es de "," bits/pixel");
	printf("\nfin");
}
*/