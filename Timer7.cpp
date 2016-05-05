#include <io.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define TOP   200   // Numero de bucles, max 32000
#define SECS  2    
#define SIZE 1048576 //Size fichero cd-rom min 1Mb
                     
                    

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
char line[256]="Prue";
void find_file(char *s,int &fin);//Inicialmente fin=0


typedef unsigned char byte;
typedef unsigned short ushort;

void main()
   {
   unsigned long ul=0;
   int i;
   unsigned long j;
   unsigned int ui=0;
   int ii=0;
   char test[256];
   byte c=0;
   ushort us1=0;
//   ushort *u;u=new ushort[100000];
   clock_t fin;
   double  inicio,duracion;
   float x,y;
   double d1=1.13,d2=1.17,d3;
   FILE *stream=fopen("out.txt","w");
   FILE *stream2;

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
   fprintf(stream,"tics/seg=%lf\n",(double) CLOCKS_PER_SEC);
   printf(        "Numero de operaciones=%lf x veces\n",50.*TOP);
   fprintf(stream,"Numero de operaciones=%lf x veces\n",50.*TOP);


   char s1[256];
   printf("\nMeter un cd en el lectores de cd's\nMeter nombre del USB: (ej: E: F: ...):");scanf("%s",s1);
 
   printf("\n               Tipo de accion  veces     segundos      Megaops/sec.\n");
   fprintf(stream,"\n               Tipo de accion  veces     segundos      Megaops/sec.\n");
//******************// 
   { 
	   //char s1[256];

	   int fin=0;
	   //find_file(s1,fin);
	   strcpy(line,"c:\\\\aa.a");
	   stream2=fopen(line,"rb");
	   if (!stream2)
	   {
			strcpy(line,"d:\\\\aa.a");
			stream2=fopen(line,"rb");
	   }

	   if (stream2)
	   {
		   stream2=fopen(line,"rb");
		   strcpy(test,"Lectura de disco duro");
		   double con=1.00001;
		   j=0;
		   fin=clock()+(long) (CLOCKS_PER_SEC*SECS);
		   inicio=clock();
		   while(clock()<fin)
		   {
			  j++;
			  for (i=0;i<TOP;i++)
			  {
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
			  }
			  if (j>(512000-TOP*50))
				  break;
		   }
		   fin=clock();
		   duracion = 1.0*(fin-inicio)/CLOCKS_PER_SEC;
		   printf( "%28s: %6lu %12f %13f %s\n", test, j, duracion, 50.0*j*TOP/duracion/1e6,line);
		   fprintf( stream,"%28s: %6lu %12f %13f %s\n", test, j, duracion, 50.0*j*TOP/duracion/1e6,line);
		   fclose(stream2);

		   stream2=fopen("kaka.txt","wb");
		   long i1;
   		   for (i1=0;i1<1000;i1++)//retardo para que arranque el disco duro
			   fputwc(12000,stream2);
		   strcpy(test,"Escribe en disco duro");
		   con=1.00001;
		   unsigned short us=1200;
		   j=0;
		   fin=clock()+(long) (CLOCKS_PER_SEC*SECS);
		   inicio=clock();
		   while(clock()<fin)
		   {
			  j++;
			  for (i=0;i<TOP;i++)
			  {
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
			  }
			  if (j>(512000-TOP*50))
				  break;
		   }
		   fin=clock();
		   duracion = 1.0*(fin-inicio)/CLOCKS_PER_SEC;
		   printf( "%28s: %6lu %12f %13f %s\n", test, j, duracion, 50.0*j*TOP/duracion/1e6,line);
		   fprintf( stream,"%28s: %6lu %12f %13f %s\n", test, j, duracion, 50.0*j*TOP/duracion/1e6,line);
		   fclose(stream2);
		   stream2=fopen("kaka.txt","wb");
		   fclose(stream2);
	   }
	   else
		   printf("No encuentro en c: o d: fichero de mas de 1 Mega 'aa.a'\n");
   }
	//******************// 
   { 

	   int fin=0;
	   find_file(s1,fin);
	   if (fin==0)
		   printf("Error, fichero en USB >1Mb no encontrado\n");

	   if (fin==1)
	   {
		   stream2=fopen(line,"rb");
		   long i1;
   		   for (i1=0;i1<1000;i1++)//retardo para que arranque el cd
				ii=fgetwc(stream2);
		   fclose(stream2);
		   stream2=fopen(line,"rb");
		   strcpy(test,"Lectura de CD 16x512000");
		   double con=1.00001;
		   j=0;
		   fin=clock()+(long) (CLOCKS_PER_SEC*SECS);
		   inicio=clock();
		   while(clock()<fin)
		   {
			  j++;
			  for (i=0;i<TOP;i++)
			  {
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
					 ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);ii=fgetwc(stream2);
			  }
			  if (j>(513000-TOP*50))
				  break;
		   }
		   fin=clock();
		   duracion = 1.0*(fin-inicio)/CLOCKS_PER_SEC;
		   printf( "%28s: %6lu %12f %13f %s\n", test, j, duracion, 50.0*j*TOP/duracion/1e6,line);
		   fprintf( stream,"%28s: %6lu %12f %13f %s\n", test, j, duracion, 50.0*j*TOP/duracion/1e6,line);
		   fclose(stream2);


		   strcpy(line,s1);
		   strcat(line,"\\\\kaka.txt");
		   stream2=fopen(line,"wb");
   		   for (i1=0;i1<1000;i1++)//retardo para que arranque el disco duro
			   fputwc(12000,stream2);
		   strcpy(test,"Escribe en USB");
		   con=1.00001;
		   unsigned short us=1200;
		   j=0;
		   fin=clock()+(long) (CLOCKS_PER_SEC*SECS);
		   inicio=clock();
		   while(clock()<fin)
		   {
			  j++;
			  for (i=0;i<TOP;i++)
			  {
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
					 fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);fputwc(us,stream2);
			  }
			  if (j>(512000-TOP*50))
				  break;
		   }
		   fin=clock();
		   duracion = 1.0*(fin-inicio)/CLOCKS_PER_SEC;
		   printf( "%28s: %6lu %12f %13f %s\n", test, j, duracion, 50.0*j*TOP/duracion/1e6,line);
		   fprintf( stream,"%28s: %6lu %12f %13f %s\n", test, j, duracion, 50.0*j*TOP/duracion/1e6,line);
		   fclose(stream2);
		   stream2=fopen(line,"wb");//borrando kaka.txt
		   fclose(stream2);
	   }
   }


/********************************/   
   do
   {
	   strcpy(test,"escribe 16bits en diskete");
	   ii=250;stream2=fopen("a:kaka.txt","wb");
	   if (stream2==NULL)
		   break;
	   unsigned long bucles;
  	   for (i=0;i<TOP;i++)
		 fputwc(ii,stream2);
	   j=0;
	   fin=clock()+(long) (CLOCKS_PER_SEC*SECS);
	   inicio=clock();
	   while(clock()<fin)
	   {
		 j++;
	     for (i=0;i<TOP;i++)
		 {
			 fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);
			 fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);
			 fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);
			 fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);
			 fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);
			 fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);
			 fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);
			 fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);
			 fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);
			 fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);fputwc(ii,stream2);
		 }
	   }
	   fin=clock();
	   duracion = 1.0*(fin-inicio)/CLOCKS_PER_SEC;
	   bucles=j;
	   printf( "%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);
	   fprintf( stream,"%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);
   	   remove("a:kaka.txt");
	   fclose(stream2);
	   j=0;
   }while (j==7); 



	//******************// 
   {
	   long index=0L;
	   strcpy(test,"Escritura en RAM 8x7Mb");
	   double *vector;vector=new double[7300000];
	   double con=1.00001;
	   j=0;
	   fin=clock()+(long) (CLOCKS_PER_SEC*SECS);
	   inicio=clock();
	   while(clock()<fin)
		  {
		  j++;
		  if (index>(7300000-TOP*50-2000)) 
			  index=0;
		  for (i=0;i<TOP;i++)
			 {
			 vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;
			 vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;
			 vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;
			 vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;
			 vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;
			 vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;
			 vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;
			 vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;
			 vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;
			 vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;vector[index++]=con;
			 }
		  }
	   fin=clock();
	   duracion = 1.0*(fin-inicio)/CLOCKS_PER_SEC;
	   printf( "%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);
	   fprintf( stream,"%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);
	   if ((50.0*j*TOP/duracion/1e6)<2)
	   {
		   printf( "ERROR: Acceso realizado a Disco Duro en vez de a RAM por: haber menos de 56Mb libres, error de RAM o Sistema Operativo o Configurtacion\n");
		   fprintf( stream,"ERROR: Acceso realizado a Disco Duro en vez de a RAM por: haber menos de 56Mb libres, error de RAM o Sistema Operativo o Configurtacion\n");
	   }

	   index=0L;
	   strcpy(test,"Lectura de RAM 8x7Mb");
	   j=0;
	   fin=clock()+(long) (CLOCKS_PER_SEC*SECS);
	   inicio=clock();
	   while(clock()<fin)
		  {
		  j++;
		  if (index>(7300000-TOP*50-2000)) 
			  index=0;
		  for (i=0;i<TOP;i++)
			 {
			 con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];
			 con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];
			 con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];
			 con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];
			 con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];
			 con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];
			 con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];
			 con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];
			 con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];
			 con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];con=vector[index++];
			 }
		  }
	   fin=clock();
	   duracion = 1.0*(fin-inicio)/CLOCKS_PER_SEC;
	   printf( "%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);
	   fprintf( stream,"%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);

	   
	   delete[] vector;
   }


	//*************************//
   {
	   strcpy(test,"int: (i+i)*i-i*cte");
	   int i1,i2,i3;
	   i1=2;i2=10;i3=11;
	   j=0;
	   fin=clock()+(long) (CLOCKS_PER_SEC*SECS);
	   inicio=clock();
	   while(clock()<fin)
	   {
		  j++;
		  for (i=0;i<TOP;i++)
		  {
			  i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;
			  i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;
			  i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;
			  i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;
			  i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;
			  i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;
			  i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;
			  i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;
			  i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;
			  i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;i1=(i1+i2)*i1-2*i3;
		  }
	   }
	   fin=clock();
	   duracion = 1.0*(fin-inicio)/CLOCKS_PER_SEC;
	   printf( "%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);
	   fprintf( stream,"%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);
   }

	//*************************//
   strcpy(test,"doble prec: (d+d)/d-d+cte*d");
   d3=1.000001;
   d2=1.01;
   d1=1.013145E-20;
   double d5=1.003E20;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*SECS);
   inicio=clock();
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;
         d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;
         d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;
         d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;
         d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;
         d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;
         d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;
         d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;
         d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;
         d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;d2=(d2+d3)/d5-d1+1.0001*d3;
         }
      }
   fin=clock();
   duracion = 1.0*(fin-inicio)/CLOCKS_PER_SEC;
   printf( "%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);
   fprintf( stream,"%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);

   //***********************//
   strcpy(test,"pow(double)");
   d2=1.00001;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*SECS);
   inicio=clock();
   while(clock()<fin)
   {
      j++;d3=10.00003;
      for (i=0;i<TOP;i++)
      {
         d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;
         d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;
         d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;
         d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;
         d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;
         d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;
         d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;
         d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;
         d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;
         d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;d2=log(d2)+1.0;
      }
   }
   fin=clock();
   duracion = 1.0*(fin-inicio)/CLOCKS_PER_SEC;
   printf( "%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);
   fprintf( stream,"%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);

   //***********************//
   strcpy(test,"log(double)");
   d2=0.1;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*SECS);
   inicio=clock();
   while(clock()<fin)
   {
      j++;
      for (i=0;i<TOP;i++)
      {
         d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);
         d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);
         d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);
         d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);
         d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);
         d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);
         d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);
         d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);
         d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);
         d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);d2=pow(d2,0.1);
      }
   }
   fin=clock();
   duracion = 1.0*(fin-inicio)/CLOCKS_PER_SEC;
   printf( "%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);
   fprintf( stream,"%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);

   //***********************//
   strcpy(test,"fabs(double)");
   d2=0.1;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*SECS);
   inicio=clock();
   while(clock()<fin)
   {
      j++;
      for (i=0;i<TOP;i++)
      {
         d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);
         d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);
         d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);
         d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);
         d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);
         d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);
         d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);
         d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);
         d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);
         d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);d2=-fabs(d2);
      }
   }
   fin=clock();
   duracion = 1.0*(fin-inicio)/CLOCKS_PER_SEC;
   printf( "%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);
   fprintf( stream,"%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);
 
   //***********************//
   strcpy(test,"(double*double)");
   d2=0.1;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*SECS);
   inicio=clock();
   while(clock()<fin)
   {
      j++;
      for (i=0;i<TOP;i++)
      {
         d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=1.00000000001;
         d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=1.00000000001;
         d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=1.00000000001;
         d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=1.00000000001;
         d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=1.00000000001;
         d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=1.00000000001;
         d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=1.00000000001;
         d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=1.00000000001;
         d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=1.00000000001;
         d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=-d2*d2;d2=1.00000000001;
      }
   }
   fin=clock();
   duracion = 1.0*(fin-inicio)/CLOCKS_PER_SEC;
   printf( "%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);
   fprintf( stream,"%28s: %6lu %12f %13f\n", test, j, duracion, 50.0*j*TOP/duracion/1e6);
   




   printf("=====================================================================\n");
   printf("                          FIN FIN FIN\n");
   printf("=====================================================================\n");
   fclose(stream);
   scanf("%c%c",&c,&c);
   }



void find_file(char *s,int &fin)//Inicialmente fin=0
{
	if (fin==1)
		return;

	char fich[256];
	strcpy(fich,s);
	strcat(fich,"\\\\*.*");

    struct _finddata_t c_file;    
	long hFile;

    /* Find first .* file in current directory */
    if( (hFile = _findfirst( fich,&c_file )) == -1L )
       return;   
	else do   
	{
		//printf("%s%s\t%X\t%li\n",s,c_file.name,c_file.attrib,c_file.size);
		/*
		int atr=c_file.attrib;
		atr=(atr >>4) <<4;
		if (atr==0x10)//atr=0x10 o 0x11 es tipo subdirectorio
		{//Es un subdirectorio, mirar dentro
			if (c_file.name[0]!='.')
			{
				char fich1[256];
				strcpy(fich1,s);
				strcat(fich1,"\\\\");
				strcat(fich1,c_file.name);
				find_file(fich1,fin);
			}
		}
		*/
		if (c_file.size>SIZE)
		{
			fin=1;
			strcpy(line,s);
			strcat(line,"\\\\");
			strcat(line,c_file.name);
			return;
		}


	}while( _findnext( hFile, &c_file ) == 0 );
	_findclose( hFile );
}

