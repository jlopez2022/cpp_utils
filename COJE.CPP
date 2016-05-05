//lee 280000 caracteres de "prue31.raw"
// Esta rutina es muy importante pues permite leer más de 4k de código
#include <stdio.h>
#include <stdlib.h>
#define ix 256
#define iy 384
#define TOP 768
typedef unsigned long ulong;
typedef unsigned char byte;

int coje(FILE *ptr);

void main()
   {
   ulong i;
   int x=0,x0=0;
   char c;
   char buf[400000];
   FILE *stream;

   if( (stream  = fopen( "prue31.raw", "r" )) == NULL )
      exit(7);
   if( setvbuf( stream, buf, _IOFBF, sizeof( buf ) ) != 0 )
      {
      printf( "Incorrect type or size of buffer for stream1\n" );
      exit(77);
      }

   for (i=0;i<280000;i++)
      {
      x=coje(stream);
      if (x=='H')
         {
         x0++;
         if (x0==4)
            {
            printf("\n %i:%X:%X",i,i,x);
            x0=0;
            }
         }
      else
         x0=0;

      if (ferror(stream))
         {
         printf("\nERROR EN POSICION:%i",i);
         scanf("%c%c",&c,&c);
         }
      if (feof(stream))
         {
         printf("\nFINAL DE FICHERO POSICION:%lu",i);
         printf("\nPosicion=%lX",i,i);
         scanf("%c%c",&c,&c);
         exit(0);
         }
      }
   printf("Meter caracteres:");
   scanf("%c%c",&c,&c);
   }


int coje(FILE *ptr)
   {
   int x;
   x=(int) (unsigned) getc(ptr);
   ptr->_cnt++;
   return(x);
   }


