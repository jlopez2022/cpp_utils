#include <time.h>
#include <string.h>
#include <stdio.h>
#define TOP   200000   // Numero de bucles, max 32000
#define SECS  4    
                     
                    

/*
	ZONA COMUN:

   //----------------------//
   strcpy(test,"tipo de test");
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*SECS);
   inicio=clock();
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);
         ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);
         ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);
         ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);
         ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);
         ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);
         ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);
         ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);
         ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);
         ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);ii=fgetwc(stream2);fputwc(ii,stream3);
         }
      }
   fin=clock();
   duracion = 1.0*(fin-inicio)/CLOCKS_PER_SEC;
   printf( "%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);
   fprintf( stream,"%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);

*/

void main()
   {
   unsigned long ul=0;
   int i;
   unsigned long j;
   unsigned int ui=0;
   int ii=0;
   char test[256];
   clock_t fin;
   double  inicio,duracion;
   float x,y;
   double d1=1.13,d2=1.17;

   printf("Solo es valida la primera ejecucion del programa. Para correr otra vez, reiniciar el ordenador.\n");
   printf("Copiar en C: un fichero de + de 1Mb (ej: hoja excel) y renombrarlo como 'aa.a'\n");
   printf("Se recomienda cerrar otras aplicaciones e Internet antes de ejecutar el programa. \nAsimismo, no efectuar operaciones durante la ejecucion del mismo.\n");
   printf("Este programa chequea los accesos a disco duro, RAM, velocidad de placa base y micro\n");
   printf("Se recomienda pasar con antivirus y Red para ver el efecto de los mismos\n");
   printf("Se recomienda pasar sin antivirus ni red para chequear el Windows+hardware\n");
   printf("Se recomienda pasar en MS-DOS para chequear el hardware\n");
   printf("Llenado RAM:\nFunciona solo si hay mas de 56Mb de RAM libres (si no, sale error de falta de memoria virtual)\n");

   printf("\nPC_SPEED_V1.01  Javier Luis Lopez Segura  freeware\n\n");

   x=(float) 1.13;y=(float) 1.17;
   printf("tics/seg = %lf\n",(double) CLOCKS_PER_SEC);
   printf(        "Numero de operaciones=%lf x veces\n",1.0*TOP);






	//******************// 
   {
	   long index=0L;
	   strcpy(test,"Suma long");
	   double con=1.00001;
	   j=0;
	   fin=clock()+(long) (CLOCKS_PER_SEC*SECS);
	   inicio=clock();
	   double duracion_bucle;
	   while(clock()<fin)
	   {
		  j++;
		  for (i=0;i<TOP;i++)
		  {
			  index++;
		  }
	   }
	   fin=clock();
	   duracion = 1.0*(fin-inicio)/CLOCKS_PER_SEC;
	   duracion_bucle=1.0*duracion/j/TOP*1e6;
	   printf( "%s: ciclos=%lu duracion del test=%12f MIPS=%13f duracion_iteracion=%lgus\n", test, j, duracion, j*TOP/duracion/1e6,duracion_bucle);
	   if ((j*TOP/duracion/1e6)<2)
	   {
		   printf( "ERROR: Acceso realizado a Disco Duro en vez de a RAM por: haber menos de 56Mb libres, error de RAM o Sistema Operativo o Configurtacion\n");
	   }
   }



   




   printf("=====================================================================\n");
   printf("                          FIN FIN FIN\n");
   printf("=====================================================================\n");
   char c;
   scanf("%c%c",&c,&c);
   }




