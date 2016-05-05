//Copia de Imagen4.h en directorio Imagen
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "stat.h"
#define SUPERX 2048
typedef unsigned char byte;
typedef unsigned long DWORD;

class Imagen
   {
   public:
   Imagen(char *fichero);
   ~Imagen();
   void LeeLinea(byte *ptr);
   void Lee();
   void LeeTrozo(long nbytes,byte *ptr);
   byte (*B)[SUPERX];//matriz bidimendional. Usar como B[YMAX][XMAX]
   byte (*G)[SUPERX];//matriz bidimendional. Usar como G[YMAX][XMAX]
   byte (*R)[SUPERX];//matriz bidimendional. Usar como R[YMAX][XMAX]
   long XMAX,YMAX,XMAXF,XMAX3,Size,bits; //Size=XMAXF*YMAX bits=bits/pixel 
   //XMAXF es el ancho en bytes de la matriz a representar.
   // = minimo mayor que 3*XMAX que es multiplo de 4
   //XMAX=num pixels horizontales
   //YMAX=numero de filas
   //Num pixels= XMAX*3*YMAX =XMAX3*YMAX
   void ToYCbCr();
   void ToBGR();

   void ImprimeCabecera();
   void ImprimeMatriz(byte *ptrB,byte *ptrG,byte *ptrR);
   void error(double x,char *linea1="",char *linea2="",char *linea3="",char *linea4="",char *linea5="");
   private:
   FILE *stream,*strout;
   //XMAXF es el ancho en bytes de la matriz a representar.
   //XMAXF = minimo mayor que 3*XMAX que es multiplo de 4
   long lee4bytes(byte *ptr);
   long leeNbytes(byte *ptr,int n); // lee n bytes de ficheros .BMP
   void LeeCabecera();
   };

Imagen::Imagen(char *fichero)
	{
	char fichout[256]="";
	char fichin[256]="";
	//strcpy(fichout,"c:\\ajavier\\c++\\imagen\\ficheros estandard\\");	//fichout=files/
	strcpy(fichin,fichero);
	strcpy(fichout,fichero);
	strcat(fichout,"_out.bmp");	//fichout=files/mallorca_out.bmp
	strcat(fichin,".bmp");		//fichero=files/mallorca.bmp
	if (!(stream=fopen(fichin,"rb")))
	  {
	  error(-1,"No se puede abrir ",fichin);
	  exit(0xFFFF);
	  }
	if (!(strout=fopen(fichout,"wb")))
	  {
	  error(-1,"No se puede abrir ",fichout);
	  exit(0xFFFF);
	  }
	LeeCabecera();
	printf("\nFichero:%s %i x %i x %i",fichero,XMAX,YMAX,bits);
	B=new byte[YMAX][SUPERX];
	G=new byte[YMAX][SUPERX];
	R=new byte[YMAX][SUPERX];
}//Imagen

Imagen::~Imagen()
{
   fclose(stream);
   fclose(strout);
	delete[] B,G,R;
}

void Imagen::LeeLinea(byte *ptr)
{
   long i;
   for(i=0;i<XMAX3;i++)
      {
      *ptr++=(byte) fgetc(stream);
      if (feof(stream)) 
         i=XMAXF;
      }
   if (i<XMAXF)
      for (i=XMAX3;i<XMAXF;i++)
         fgetc(stream);
}

void Imagen::Lee()
{
   int x,y,delta=XMAXF-XMAX3;
   byte *ptrB,*ptrG,*ptrR;
   for (y=0;y<YMAX;y++)
   {
	   ptrB=&B[y][0];
	   ptrG=&G[y][0];
	   ptrR=&R[y][0];
	   for(x=0;x<XMAX;x++)
	   {
	      *ptrB++=(byte) fgetc(stream);
	      *ptrG++=(byte) fgetc(stream);
	      *ptrR++=(byte) fgetc(stream);
	   }
	   for (x=0;x<delta;x++)
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
   byte r,g,b;
   int x,y;
   byte *ptrB,*ptrG,*ptrR;
   for (y=0;y<YMAX;y++)
   {
	   ptrB=&B[y][0];
	   ptrG=&G[y][0];
	   ptrR=&R[y][0];
	   for(x=0;x<XMAX;x++)
	   {
		  b=*ptrB;
		  g=*ptrG;
		  r=*ptrR;
		  *ptrB++=(byte) (0.299*r+0.587*g+0.114*b+0.4);//Y
		  *ptrG++=(byte) (128.4-0.1687*r-0.3313*g+0.5*b);//Cb
		  *ptrR++=(byte) (128.4+0.5*r-0.4187*g-0.0813*b);//Cr
	   }
   }
}

void Imagen::ToBGR()
{
   byte Y,Cb,Cr;
   int x,y;
   byte *ptrB,*ptrG,*ptrR;
   for (y=0;y<YMAX;y++)
   {
	   ptrB=&B[y][0];
	   ptrG=&G[y][0];
	   ptrR=&R[y][0];
	   for(x=0;x<XMAX;x++)
	   {
		  Y =*ptrB;
		  Cb=*ptrG;
		  Cr=*ptrR;
		  *ptrB++=(byte) (-178.654+Y+1.4*Cr);
		  *ptrG++=(byte) (135.79+Y-0.34414*Cb-0.71414*Cr);
		  *ptrR++=(byte) (-225.958+Y+1.77*Cb);
	   }
   }
}

void Imagen::LeeTrozo(long nbytes,byte *ptr)
   {
   long i;
   for(i=0;i<nbytes;i++)
      *ptr++=(byte) fgetc(stream);
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


void Imagen::ImprimeCabecera()
//Esta funcion calcula la cabecera del fichero .BMP
//cabecera es la cabecera BMP, que es una matriz byte cabecera[0x36]
//El resto del fichero es la matriz byte formada por los colores 
//en orden BGR empezando por la esquina izquierda abajo haciendo 
//barridos de derecha a izquierda desde la fila de abajo.
//Atencion: Si ancho*3 no es multiplo de 4, se debe añadir 0 hasta
//que lo sea al llenar la matriz
//La funcion retorna el numero de ceros a añadir cada vez que se 
//escriba una linea
   {
   byte cabecera[0x36],*ptr;
   long i,m;
   for (i=0;i<0x36;i++) cabecera[i]=0;

   //Cabecera:
   cabecera[0]=0x42;cabecera[1]=0x4D;
   m=XMAXF*YMAX+0x36;
   for (i=0;i<4;i++) cabecera[i+2]=(m>>(8*i)) & 0xFF;  
   cabecera[10]=0x36;cabecera[14]=0x28;
   //Segunda fila:
   m=XMAX;
   for (i=0;i<4;i++) cabecera[i+0x12]=(m>>(8*i)) & 0xFF;  
   m=YMAX;
   for (i=0;i<4;i++) cabecera[i+0x16]=(m>>(8*i)) & 0xFF;  
   cabecera[0x1A]=0X1;cabecera[0x1C]=0X18;
   //Tercera fila:
   m=XMAXF*YMAX;
   for (i=0;i<4;i++) cabecera[i+0x22]=(m>>(8*i)) & 0xFF;  
   cabecera[0x26]=0x3C;cabecera[0x27]=0x0F; //100ppp eje x
   cabecera[0x2A]=0x3C;cabecera[0x2B]=0x0F; //100ppp eje y

   ptr=cabecera;
   for (i=0;i<0x36;i++)
      fputc((int) *ptr++,strout);
   //El resto es la matriz BGR (mas los ceros)
   }

void Imagen::ImprimeMatriz(byte *ptrB,byte *ptrG,byte *ptrR)
{
   int x,y,delta=XMAXF-XMAX3;
   for (y=0;y<YMAX;y++)
   {
	   ptrB=&B[y][0];
	   ptrG=&G[y][0];
	   ptrR=&R[y][0];
	   for(x=0;x<XMAX;x++)
	   {
		   fputc((int) *ptrB++,strout);
		   fputc((int) *ptrG++,strout);
		   fputc((int) *ptrR++,strout);
	   }
	   for (x=0;x<delta;x++)
		   fputc((int) 0,strout);
   }
   fclose(strout);
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