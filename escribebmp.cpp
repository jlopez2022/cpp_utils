#include <stdio.h>
#include <string.h>
typedef unsigned char byte;
typedef unsigned long DWORD;

//ojo, si es monocromo, *b,*g o *r es NULL
void escribe_bmp(char *nombre,long XMAX,long YMAX,short *b,short *g,short *r)
{
//typedef unsigned char byte;
//typedef unsigned long DWORD;

	//1. Creo el fichero
	FILE *str;
	char fichero[1024];
	strcpy(fichero,nombre);
	if (!strstr(nombre,".bmp"))
		strcpy(fichero,".bmp");
	str=fopen(fichero,"wb");

	//2. hallo datos
	long XMAX3=XMAX*3;
	long XMAXF=XMAX3;
	if (XMAXF % 4)
		XMAXF=XMAXF+4- ( XMAXF % 4 );
	
	//3. creo la cabecera
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
	//4. escribo cabecera
	for (i=0;i<0x36;i++)
		fputc((int) *ptr++,str);
	//5. escribo matriz
	int x,y,delta=XMAXF-XMAX3;
	short *ptrB=b;
	short *ptrG=g;
	short *ptrR=r;
	for (y=0;y<YMAX;y++)
	{
	   for(x=0;x<XMAX;x++)
	   {
		   if (b) fputc((int) *ptrB++,str);
		   else   fputc(0,str);
		   if (g) fputc((int) *ptrG++,str);
		   else   fputc(0,str);
		   if (r) fputc((int) *ptrR++,str);
		   else   fputc(0,str);
	   }
	   for (x=0;x<delta;x++)
		   fputc((int) 0,str);
	}
	
	fclose(str);
}