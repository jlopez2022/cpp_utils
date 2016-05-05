//Fichero prupointer. Ordena una matriz conforme llegan los datos por orden de numero de apariciones
#include <stdio.h>
#define TOP 65535

typedef struct numdatat
   {
   numdatat *ant; //anterior: el cual tendra un sum mayor despues de la ordenacion)
   numdatat *sig; //Siguiente: el cual tendra un sum menor despues de la ordenacion)
   unsigned sum;  // Numero de apariciones
   unsigned char ind;  // Indic, que coincidira con el indice de la matriz a1
   }kaka;

numdatat a1[256], primero, *dirx, *dir1, *dir2;
int ejemplo[20]={ 3,5,1,1,7, 1,8,9,9,2, 2,8,5,1,4, 2,2,2,1,8};

void main()
   {
   int i,j;
   long suma=0;
   FILE *stream;
   stream=fopen("kaka.txt","w");

   primero.sum=TOP;
   primero.sig=&a1[0];
   a1[0].ant=&primero;

   dir1=&a1[0];
   for (i=0;i<256;i++)
      {
      dir1->sig=(dir1+1);
      dir1->sum=0;
      dir1->ind=i;
      dir1++;
      dir1->ant=dir1-1;
      }

   for (i=0;i<20;i++) //Introduccion de datos y ordenacion
      {
      printf("\n%i",i);
      suma++;
      j=ejemplo[i];
      dir1=&a1[j];
      dir1->sum++;
      dir2=dir1;
      while ((dir2->ant)->sum < dir1->sum) //Busqueda de anteriores mas pequeños
         dir2=dir2->ant;
      if (dir1 != dir2) //recolocacion
         {
         (dir2->ant)->sig=dir1;
         (dir1->sig)->ant=dir1->ant;

         dirx=dir1->sig;dir1->sig=dir2;
         (dir1->ant)->sig=dirx;

         dirx=dir2->ant; dir2->ant=dir1;
         dir1->ant=dirx;
         }

      }//end for i

   
   fprintf(stream," i   ind sum");
   dir1=primero.sig;
   for (i=0;i<10;i++) //Guarda resultados hasta num 10 en fichero
      {
      fprintf(stream,"\n%2i   %u %u",i,dir1->ind,dir1->sum);
      dir1=dir1->sig;
      }
   
   fclose(stream);
   }