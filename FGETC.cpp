//Pone y saca mas de 4k de código en MODO BINARIO
#include <stdio.h>
#include <stdlib.h>
#define TOP 5000
void error(double x,char *linea1="",char *linea2="",char *linea3="",char *linea4="",char *linea5="");

void main()
   {
   char *buffer;
   int i;
   char file[]="kaka.txt";
   FILE *stream=fopen(file,"wb");//"wb" sirve para escribir en modo binario
   if (!stream)
      error(-1.,"Error al abrir fichero",file);
   buffer= new char[TOP];
   for(i=0;i<TOP;i++)
      fputc(i,stream);
   fclose(stream);
   stream=fopen(file,"rb");
   if (!stream)
      error(-1.,"Error al abrir fichero",file);
   if( setvbuf( stream, buffer, _IOFBF, sizeof( buffer ) ) != 0 )
      error(-1., "Incorrect type or size of buffer for stream1\n" );
   int longitud=0,*valor,*ptr;
   valor=new int[TOP];ptr=valor;
   while(!feof(stream))
      {
      longitud++;
      *ptr++=fgetc(stream);
      }
   longitud--;
   fclose(stream);
   ptr=valor;
   for (i=0;i<TOP;i++) printf(" %7i",*ptr++);
   delete[] buffer,valor;
   error((double)longitud,"Longitud de fichero=");
   }

void error(double x,char *linea1,char *linea2,char *linea3,char *linea4,char *linea5)
   {
   char c;
   printf("\nError:%s%s%s%s%s",linea1,linea2,linea3,linea4,linea5);
   if (x!=-1.)
      printf("%f",x);
   scanf("%c%c",&c,&c);
   exit(-2);
   }
