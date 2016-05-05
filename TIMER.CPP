//¡¡Atención, dá tiempos 2-3 veces menores en modo "Release"!!
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define TOP   2000   // max 32000
#define FACTOR 1    //factor 1=mayor velocidad,<precision
                    //factor 4=mas precision 
                    // minimo recomendado=2.0/7


typedef unsigned char byte;
typedef unsigned short ushort;

void main()
   {
   unsigned long ul=0;
   int i,i1,i2,i3;
   unsigned long j;
   unsigned int ui=0;
   int ii=0,in[100000];
   char ch,line[256]="Prue";
   byte c=0,c1[100000],b1,b2;
   short sh1,sh2;
   ushort us1=0,us2,us3;
   ushort u[100000];
   clock_t fin;
   double  inicio,duracion;
   float x,y,ff[8000],z;
   double d1=1.13,d2=1.17,dd[8000],d3;
   FILE *stream=fopen("out.txt","w");
   FILE *stream2;

   printf("Atencion, da resultados mucho menores en modo Release!!\n");
   x=(float) 1.13;y=(float) 1.17;
   printf("tics/seg = %lf\n",(double) CLOCKS_PER_SEC);
   fprintf(stream,"tics/seg=%lf\n",(double) CLOCKS_PER_SEC);
   printf(        "Numero de bucles=%lf\n",50.*TOP);
   fprintf(stream,"Numero de bucles=%lf\n",50.*TOP);
   printf("               Tipo de accion  veces      miliseg   MHZ\n");
   fprintf(stream,"               Tipo de accion  veces      miliseg   MHZ\n");
//calculo de bucle
   u[0]=1;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         }
      }
   inicio = 1000.*FACTOR/j;
   u[0]=1;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         }
      }
   duracion = 1000.*FACTOR/j;
   duracion=(2.*duracion-inicio)*50;
   strcpy(line,"Bucle(x50)");
   printf("%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   c=250;stream2=fopen("kaka.txt","w");
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);
         fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);
         fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);
         fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);
         fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);
         fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);
         fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);
         fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);
         fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);
         fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);fputc(c,stream2);
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"escribe fich byte");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   j=j*50*TOP;
   for (;j>0;j--) fputc(c,stream2);
   fclose(stream2);

   stream2=fopen("kaka.txt","r");
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);
         c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);
         c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);
         c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);
         c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);
         c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);
         c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);
         c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);
         c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);
         c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);c=fgetc(stream2);
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"lee fich byte");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fclose(stream2);

   ch=1;stream2=fopen("kaka.txt","w");
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);
         fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);
         fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);
         fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);
         fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);
         fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);
         fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);
         fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);
         fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);
         fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);fputc(ch,stream2);
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"escribe fich char");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   j=j*50*TOP;
   for (;j>0;j--) fputc(ch,stream2);
   fclose(stream2);

   stream2=fopen("kaka.txt","r");
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);
         ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);
         ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);
         ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);
         ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);
         ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);
         ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);
         ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);
         ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);
         ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);ch=fgetc(stream2);
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"lee fich char");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fclose(stream2);

   ii=255;stream2=fopen("kaka.txt","w");
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);
         fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);
         fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);
         fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);
         fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);
         fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);
         fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);
         fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);
         fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);
         fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);fputc(ii,stream2);
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"escribe fich int");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   j=j*50*TOP;
   for (;j>0;j--) fputc(ii,stream2);
   fclose(stream2);

   stream2=fopen("kaka.txt","r");
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);
         ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);
         ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);
         ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);
         ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);
         ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);
         ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);
         ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);
         ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);
         ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);ii=fgetc(stream2);
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"lee fich int");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fclose(stream2);

   j=0;i1=1;i2=3;i3=2;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1; 
         if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1; 
         if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1; 
         if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1; 
         if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1; 
         if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1; 
         if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1; 
         if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1; 
         if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1; 
         if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1;if(i3<i2) i3=i2; if(i3>i1) i3=i1; 
         } 
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"comparacion int");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;x=(float)1.12;y=(float)3.33;z=(float)2.;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         if(z>x) z=x;if(z<y) z=y; if(z>x) z=x;if(z<y) z=y; if(z>x) z=x; 
         if(z>x) z=x;if(z<y) z=y; if(z>x) z=x;if(z<y) z=y; if(z>x) z=x; 
         if(z>x) z=x;if(z<y) z=y; if(z>x) z=x;if(z<y) z=y; if(z>x) z=x; 
         if(z>x) z=x;if(z<y) z=y; if(z>x) z=x;if(z<y) z=y; if(z>x) z=x; 
         if(z>x) z=x;if(z<y) z=y; if(z>x) z=x;if(z<y) z=y; if(z>x) z=x; 
         if(z>x) z=x;if(z<y) z=y; if(z>x) z=x;if(z<y) z=y; if(z>x) z=x; 
         if(z>x) z=x;if(z<y) z=y; if(z>x) z=x;if(z<y) z=y; if(z>x) z=x; 
         if(z>x) z=x;if(z<y) z=y; if(z>x) z=x;if(z<y) z=y; if(z>x) z=x; 
         if(z>x) z=x;if(z<y) z=y; if(z>x) z=x;if(z<y) z=y; if(z>x) z=x; 
         if(z>x) z=x;if(z<y) z=y; if(z>x) z=x;if(z<y) z=y; if(z>x) z=x; 
         } 
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"comparacion float");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;d1=1.12;d2=3.33;d3=2;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1; 
         if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1; 
         if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1; 
         if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1; 
         if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1; 
         if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1; 
         if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1; 
         if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1; 
         if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1; 
         if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1;if(d3<d2) d3=d2; if(d3>d1) d3=d1; 
         } 
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"comparacion double");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   c1[i]=1;c1[j]=1;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];
         c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];
         c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];
         c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];
         c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];
         c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];
         c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];
         c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];
         c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];
         c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];c1[j+1]=c1[i];c1[j]=c1[i];
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"byte[]=byte[]");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   in[0]=1;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         in[i]=in[j];in[j]=in[i];in[i]=in[j];in[j]=in[i];in[i]=in[i];
         in[i]=in[j];in[j]=in[i];in[i]=in[j];in[j]=in[i];in[i]=in[i];
         in[i]=in[j];in[j]=in[i];in[i]=in[j];in[j]=in[i];in[i]=in[i];
         in[i]=in[j];in[j]=in[i];in[i]=in[j];in[j]=in[i];in[i]=in[i];
         in[i]=in[j];in[j]=in[i];in[i]=in[j];in[j]=in[i];in[i]=in[i];
         in[i]=in[j];in[j]=in[i];in[i]=in[j];in[j]=in[i];in[i]=in[i];
         in[i]=in[j];in[j]=in[i];in[i]=in[j];in[j]=in[i];in[i]=in[i];
         in[i]=in[j];in[j]=in[i];in[i]=in[j];in[j]=in[i];in[i]=in[i];
         in[i]=in[j];in[j]=in[i];in[i]=in[j];in[j]=in[i];in[i]=in[i];
         in[i]=in[j];in[j]=in[i];in[i]=in[j];in[j]=in[i];in[i]=in[i];
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"llamada int");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   in[0]=1;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;d1=(double) j;
      for (i=0;i<TOP;i++)
         {
         in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[i];
         in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[i];
         in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[i];
         in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[i];
         in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[i];
         in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[i];
         in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[i];
         in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[i];
         in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[i];
         in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[(int) d1];in[(int) d1]=in[i];in[i]=in[i];
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"llamada int[double]");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   int *iiptr=&in[0];
   in[0]=12;in[1]=13;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++) 
         {
         in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;
         in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;
         in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;
         in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;
         in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;
         in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;
         in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;
         in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;
         in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;
         in[i]=*iiptr++;in[i+1]=*iiptr++;in[i]=*iiptr++;in[i+1]=*iiptr++;iiptr-=49;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"int[int]=*ptr++");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   for (i=0;i<100000;i++) in[i]=i;
   int *iiptr2=&in[0];
   iiptr=&in[1];
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++) 
         {
         *iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;
         *iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;
         *iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;
         *iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;
         *iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;
         *iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;
         *iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;
         *iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;
         *iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;
         *iiptr2=*iiptr++;*iiptr=*iiptr2++;*iiptr2=*iiptr++;
         iiptr-=29;
         iiptr2-=19;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"*intptr=*intptr++");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   u[i]=1;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         u[i]=u[j];u[j]=u[i];u[i]=u[j];u[j]=u[i];u[i]=u[i];
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"ushort[int]");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   ff[i+1]=(float) 12.13;ff[7900]=(float) 12.13;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];
         ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];
         ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];
         ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];
         ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];
         ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];
         ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];
         ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];
         ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];
         ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];ff[i]=ff[7900];ff[7900]=ff[i+1];
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"float[int]=float[int]");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   dd[i+1]=12.13;dd[i+1]=12.14;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++) 
         {
         dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];
         dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];
         dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];
         dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];
         dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];
         dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];
         dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];
         dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];
         dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];
         dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];dd[i+1]=dd[i];dd[i]=dd[i+1];
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"double[int]=double[int]");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   double *ddptr=&dd[0];
   dd[0]=12.13;dd[1]=12.14;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++) 
         {
         dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;
         dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;
         dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;
         dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;
         dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;
         dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;
         dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;
         dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;
         dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;
         dd[i]=*ddptr++;dd[i+1]=*ddptr++;dd[i]=*ddptr++;dd[i+1]=*ddptr++;ddptr-=49;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"double[int]=*ptr++");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   for (i=0;i<8000;i++) dd[i]=(double)i;
   double *ddptr2=&dd[0];
   ddptr=&dd[1];
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++) 
         {
         *ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;
         *ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;
         *ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;
         *ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;
         *ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;
         *ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;
         *ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;
         *ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;
         *ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;
         *ddptr2=*ddptr++;*ddptr=*ddptr2++;*ddptr2=*ddptr++;
         ddptr-=29;
         ddptr2-=19;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"*doubleptr=*doubleptr++");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   dd[1]=12.13;dd[0]=12.14;d1=0;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++) 
         {
         d1=dd[i];dd[i+1]=d1;d1=dd[i];dd[i+1]=d1;d1=dd[i+2];
         d1=dd[i];dd[i+1]=d1;d1=dd[i];dd[i+1]=d1;d1=dd[i+2];
         d1=dd[i];dd[i+1]=d1;d1=dd[i];dd[i+1]=d1;d1=dd[i+2];
         d1=dd[i];dd[i+1]=d1;d1=dd[i];dd[i+1]=d1;d1=dd[i+2];
         d1=dd[i];dd[i+1]=d1;d1=dd[i];dd[i+1]=d1;d1=dd[i+2];
         d1=dd[i];dd[i+1]=d1;d1=dd[i];dd[i+1]=d1;d1=dd[i+2];
         d1=dd[i];dd[i+1]=d1;d1=dd[i];dd[i+1]=d1;d1=dd[i+2];
         d1=dd[i];dd[i+1]=d1;d1=dd[i];dd[i+1]=d1;d1=dd[i+2];
         d1=dd[i];dd[i+1]=d1;d1=dd[i];dd[i+1]=d1;d1=dd[i+2];
         d1=dd[i];dd[i+1]=d1;d1=dd[i];dd[i+1]=d1;d1=dd[i+2];
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"double=double[int]");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   {
   double xx[1000];
   short i1=1;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++) 
         {
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         i1=(short) (0*j);
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"float[short]=float[short]");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   }

   {
   double xx[1000];
   int i1=1;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++) 
         {
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];xx[i1++]=xx[i1+1];
         i1=0*j;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"float[int]=float[int]");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   }

   j=0;c=1;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         c=c>>1; c=c>>1; c=c>>1; c=c>>1; c=c>>1; 
         c=c>>1; c=c>>1; c=c>>1; c=c>>1; c=c>>1; 
         c=c>>1; c=c>>1; c=c>>1; c=c>>1; c=c>>1; 
         c=c>>1; c=c>>1; c=c>>1; c=c>>1; c=c>>1; 
         c=c>>1; c=c>>1; c=c>>1; c=c>>1; c=c>>1; 
         c=c>>1; c=c>>1; c=c>>1; c=c>>1; c=c>>1; 
         c=c>>1; c=c>>1; c=c>>1; c=c>>1; c=c>>1; 
         c=c>>1; c=c>>1; c=c>>1; c=c>>1; c=c>>1; 
         c=c>>1; c=c>>1; c=c>>1; c=c>>1; c=c>>1; 
         c=c>>1; c=c>>1; c=c>>1; c=c>>1; c=c>>1; 
         } 
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"byte>>1");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;c=1;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         c=c>>4; c=c>>4; c=c>>4; c=c>>4; c=c>>4; 
         c=c>>4; c=c>>4; c=c>>4; c=c>>4; c=c>>4; 
         c=c>>4; c=c>>4; c=c>>4; c=c>>4; c=c>>4; 
         c=c>>4; c=c>>4; c=c>>4; c=c>>4; c=c>>4; 
         c=c>>4; c=c>>4; c=c>>4; c=c>>4; c=c>>4; 
         c=c>>4; c=c>>4; c=c>>4; c=c>>4; c=c>>4; 
         c=c>>4; c=c>>4; c=c>>4; c=c>>4; c=c>>4; 
         c=c>>4; c=c>>4; c=c>>4; c=c>>4; c=c>>4; 
         c=c>>4; c=c>>4; c=c>>4; c=c>>4; c=c>>4; 
         c=c>>4; c=c>>4; c=c>>4; c=c>>4; c=c>>4; 
         } 
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"byte>>4");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;ch=1;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; 
         ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; 
         ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; 
         ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; 
         ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; 
         ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; 
         ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; 
         ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; 
         ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; 
         ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; ch=ch>>4; 
         } 
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"char>>4");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;i1=1;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; 
         i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; 
         i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; 
         i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; 
         i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; 
         i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; 
         i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; 
         i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; 
         i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; 
         i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; i1=i1>>4; 
         } 
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"int>>4");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;ui=1;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; 
         ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; 
         ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; 
         ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; 
         ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; 
         ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; 
         ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; 
         ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; 
         ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; 
         ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; ui=ui>>4; 
         } 
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"unsigned int>>4");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;ui=1;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); 
         ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); 
         ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); 
         ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); 
         ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); 
         ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); 
         ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); 
         ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); 
         ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); 
         ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); ui=_rotl(ui,4); 
         } 
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"rotacion unsigned int 4");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;c=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         c++; c++; c++; c++; c++; 
         c++; c++; c++; c++; c++; 
         c++; c++; c++; c++; c++; 
         c++; c++; c++; c++; c++; 
         c++; c++; c++; c++; c++; 
         c++; c++; c++; c++; c++; 
         c++; c++; c++; c++; c++; 
         c++; c++; c++; c++; c++; 
         c++; c++; c++; c++; c++; 
         c++; c++; c++; c++; c++; 
         } 
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"byte++");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;ui=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         ui++; ui++; ui++; ui++; ui++; 
         ui++; ui++; ui++; ui++; ui++; 
         ui++; ui++; ui++; ui++; ui++; 
         ui++; ui++; ui++; ui++; ui++; 
         ui++; ui++; ui++; ui++; ui++; 
         ui++; ui++; ui++; ui++; ui++; 
         ui++; ui++; ui++; ui++; ui++; 
         ui++; ui++; ui++; ui++; ui++; 
         ui++; ui++; ui++; ui++; ui++; 
         ui++; ui++; ui++; ui++; ui++; 
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"unsigned int ++");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         ii++; ii++; ii++; ii++; ii++; 
         ii++; ii++; ii++; ii++; ii++; 
         ii++; ii++; ii++; ii++; ii++; 
         ii++; ii++; ii++; ii++; ii++; 
         ii++; ii++; ii++; ii++; ii++; 
         ii++; ii++; ii++; ii++; ii++; 
         ii++; ii++; ii++; ii++; ii++; 
         ii++; ii++; ii++; ii++; ii++; 
         ii++; ii++; ii++; ii++; ii++; 
         ii++; ii++; ii++; ii++; ii++; 
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"int++");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;us1=1;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         us1++; us1++; us1++; us1++; us1++; 
         us1++; us1++; us1++; us1++; us1++; 
         us1++; us1++; us1++; us1++; us1++; 
         us1++; us1++; us1++; us1++; us1++; 
         us1++; us1++; us1++; us1++; us1++; 
         us1++; us1++; us1++; us1++; us1++; 
         us1++; us1++; us1++; us1++; us1++; 
         us1++; us1++; us1++; us1++; us1++; 
         us1++; us1++; us1++; us1++; us1++; 
         us1++; us1++; us1++; us1++; us1++; 
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"ushort++");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;ul=1;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         ul++; ul++; ul++; ul++; ul++; 
         ul++; ul++; ul++; ul++; ul++; 
         ul++; ul++; ul++; ul++; ul++; 
         ul++; ul++; ul++; ul++; ul++; 
         ul++; ul++; ul++; ul++; ul++; 
         ul++; ul++; ul++; ul++; ul++; 
         ul++; ul++; ul++; ul++; ul++; 
         ul++; ul++; ul++; ul++; ul++; 
         ul++; ul++; ul++; ul++; ul++; 
         ul++; ul++; ul++; ul++; ul++; 
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"unsigned long++");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;
         x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;
         x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;
         x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;
         x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;
         x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;
         x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;
         x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;
         x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;
         x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;x=x+(float) 1;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"float+1");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   x=(float) 1.;
   j=0;d1=2.2;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;
         d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;
         d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;
         d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;
         d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;
         d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;
         d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;
         d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;
         d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;
         d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;d1=d1+1;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"double+1");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;d1=1.1;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;
         d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;
         d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;
         d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;
         d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;
         d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;
         d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;
         d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;
         d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;
         d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;d1=d1+1.;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"double+1.");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;us3=1;us2=1;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; 
         us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; 
         us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; 
         us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; 
         us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; 
         us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; 
         us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; 
         us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; 
         us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; 
         us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; us2=us2+us3; 
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"suma ushort");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; 
         x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; 
         x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; 
         x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; 
         x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; 
         x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; 
         x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; 
         x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; 
         x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; 
         x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; x=(float) us2 +x; 
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"(float) ushort");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   d1=1e-100;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; 
         d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; 
         d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; 
         d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; 
         d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; 
         d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; 
         d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; 
         d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; 
         d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; 
         d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) us2+d1; d1=(double) (us2+us3+d1); 
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"(double) ushort");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   d1=1e-100;ii=2;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; 
         d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; 
         d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; 
         d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; 
         d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; 
         d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; 
         d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; 
         d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; 
         d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; 
         d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=d1*(double)ii; d1=(double) (us2+us3+d1); 
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"double*(double)int");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   d1=1e-100;x=(float)1.0001;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; 
         d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; 
         d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; 
         d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; 
         d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; 
         d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; 
         d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; 
         d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; 
         d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; 
         d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=d1*(double)x; d1=(double) (us2+us3+d1); 
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"double*(double)float");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;b1=1;b2=1;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;
         b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;
         b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;
         b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;
         b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;
         b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;
         b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;
         b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;
         b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;
         b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;b1=b1+b2;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"suma byte");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;b1=1;b2=1;i1=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;
         i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;
         i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;
         i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;
         i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;
         i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;
         i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;
         i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;
         i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;
         i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;i1=i1+b1;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"int=suma byte");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;sh1=0;sh2=1;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;
         sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;
         sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;
         sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;
         sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;
         sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;
         sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;
         sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;
         sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;
         sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;sh1=sh1+sh2;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"suma short");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);


   j=0;sh1=0;sh2=1;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;
         sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;
         sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;
         sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;
         sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;
         sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;
         sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;
         sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;
         sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;
         sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;sh1=sh1-sh2;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"resta short");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;i1=0;i2=1;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;
         i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;
         i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;
         i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;
         i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;
         i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;
         i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;
         i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;
         i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;
         i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;i1=i1+i2;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"suma int");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;i1=0;i2=1;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         i1+=i2;i1+=i2;i1+=i2;i1+=i2;i1+=i2;
         i1+=i2;i1+=i2;i1+=i2;i1+=i2;i1+=i2;
         i1+=i2;i1+=i2;i1+=i2;i1+=i2;i1+=i2;
         i1+=i2;i1+=i2;i1+=i2;i1+=i2;i1+=i2;
         i1+=i2;i1+=i2;i1+=i2;i1+=i2;i1+=i2;
         i1+=i2;i1+=i2;i1+=i2;i1+=i2;i1+=i2;
         i1+=i2;i1+=i2;i1+=i2;i1+=i2;i1+=i2;
         i1+=i2;i1+=i2;i1+=i2;i1+=i2;i1+=i2;
         i1+=i2;i1+=i2;i1+=i2;i1+=i2;i1+=i2;
         i1+=i2;i1+=i2;i1+=i2;i1+=i2;i1+=i2;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"suma +=int");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);


   j=0;i1=0;i2=1;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;
         i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;
         i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;
         i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;
         i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;
         i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;
         i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;
         i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;
         i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;
         i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;i1=i1-i2;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"resta int");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   y=(float)1e-20;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         y=x+y;y=x+y;y=x+y;y=x+y;y=x+y;
         y=x+y;y=x+y;y=x+y;y=x+y;y=x+y;
         y=x+y;y=x+y;y=x+y;y=x+y;y=x+y;
         y=x+y;y=x+y;y=x+y;y=x+y;y=x+y;
         y=x+y;y=x+y;y=x+y;y=x+y;y=x+y;
         y=x+y;y=x+y;y=x+y;y=x+y;y=x+y;
         y=x+y;y=x+y;y=x+y;y=x+y;y=x+y;
         y=x+y;y=x+y;y=x+y;y=x+y;y=x+y;
         y=x+y;y=x+y;y=x+y;y=x+y;y=x+y;
         y=x+y;y=x+y;y=x+y;y=x+y;y=x+y;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"suma float");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   d1=1.;d2=1e-100;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;
         d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;
         d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;
         d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;
         d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;
         d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;
         d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;
         d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;
         d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;
         d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;d2=d1+d2;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"suma double");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   x=(float)1.01;y=(float)1.1;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         y=y*x;y=y*x;y=y*x;y=y*x;y=y*x;
         y=y*x;y=y*x;y=y*x;y=y*x;y=y*x;
         y=y*x;y=y*x;y=y*x;y=y*x;y=y*x;
         y=y*x;y=y*x;y=y*x;y=y*x;y=y*x;
         y=y*x;y=y*x;y=y*x;y=y*x;y=y*x;
         y=y*x;y=y*x;y=y*x;y=y*x;y=y*x;
         y=y*x;y=y*x;y=y*x;y=y*x;y=y*x;
         y=y*x;y=y*x;y=y*x;y=y*x;y=y*x;
         y=y*x;y=y*x;y=y*x;y=y*x;y=y*x;
         y=y*x;y=y*x;y=y*x;y=y*x;y=y*x;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"float*float");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   d1=1.000001;d2=1.1315;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;
         d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;
         d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;
         d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;
         d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;
         d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;
         d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;
         d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;
         d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;
         d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;d2=d2*d1;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"double*double");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;ii=1;i1=2;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         ii=i1/j;i1=ii/j;ii=i1/j;i1=ii/j;i3=ii/j;
         ii=i1/j;i1=ii/j;ii=i1/j;i1=ii/j;i3=ii/j;
         ii=i1/j;i1=ii/j;ii=i1/j;i1=ii/j;i3=ii/j;
         ii=i1/j;i1=ii/j;ii=i1/j;i1=ii/j;i3=ii/j;
         ii=i1/j;i1=ii/j;ii=i1/j;i1=ii/j;i3=ii/j;
         ii=i1/j;i1=ii/j;ii=i1/j;i1=ii/j;i3=ii/j;
         ii=i1/j;i1=ii/j;ii=i1/j;i1=ii/j;i3=ii/j;
         ii=i1/j;i1=ii/j;ii=i1/j;i1=ii/j;i3=ii/j;
         ii=i1/j;i1=ii/j;ii=i1/j;i1=ii/j;i3=ii/j;
         ii=i3/j;i1=ii/j;ii=i1/j;i1=ii/j;i3=ii/j;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"int / int");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   j=0;ii=1;i1=2;i2=1;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         ii=i1*i2;i1=ii*i2;ii=i1*i2;i1=ii*i2;i2=ii*i1;
         ii=i1*i2;i1=ii*i2;ii=i1*i2;i1=ii*i2;i2=ii*i1;
         ii=i1*i2;i1=ii*i2;ii=i1*i2;i1=ii*i2;i2=ii*i1;
         ii=i1*i2;i1=ii*i2;ii=i1*i2;i1=ii*i2;i2=ii*i1;
         ii=i1*i2;i1=ii*i2;ii=i1*i2;i1=ii*i2;i2=ii*i1;
         ii=i1*i2;i1=ii*i2;ii=i1*i2;i1=ii*i2;i2=ii*i1;
         ii=i1*i2;i1=ii*i2;ii=i1*i2;i1=ii*i2;i2=ii*i1;
         ii=i1*i2;i1=ii*i2;ii=i1*i2;i1=ii*i2;i2=ii*i1;
         ii=i1*i2;i1=ii*i2;ii=i1*i2;i1=ii*i2;i2=ii*i1;
         ii=i1*i2;i1=ii*i2;ii=i1*i2;i1=ii*i2;i2=ii*i1;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"int x int");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   y=(float)1.1322;x=(float)2.2;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         x=x/y;x=x/y;x=x/y;x=x/y;x=x/y;
         x=x/y;x=x/y;x=x/y;x=x/y;x=x/y;
         x=x/y;x=x/y;x=x/y;x=x/y;x=x/y;
         x=x/y;x=x/y;x=x/y;x=x/y;x=x/y;
         x=x/y;x=x/y;x=x/y;x=x/y;x=x/y;
         x=x/y;x=x/y;x=x/y;x=x/y;x=x/y;
         x=x/y;x=x/y;x=x/y;x=x/y;x=x/y;
         x=x/y;x=x/y;x=x/y;x=x/y;x=x/y;
         x=x/y;x=x/y;x=x/y;x=x/y;x=x/y;
         x=x/y;x=x/y;x=x/y;x=x/y;x=x/y;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"division float");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   d2=1.44445e20;
   d1=1.013145;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;d1=(double)(j);
      for (i=0;i<TOP;i++)
         {
         d2=d3/d1;d3=d2/d1;d2=d3/d1;d3=d2/d1;d2=d3/d1;
         d2=d3/d1;d3=d2/d1;d2=d3/d1;d3=d2/d1;d2=d3/d1;
         d2=d3/d1;d3=d2/d1;d2=d3/d1;d3=d2/d1;d2=d3/d1;
         d2=d3/d1;d3=d2/d1;d2=d3/d1;d3=d2/d1;d2=d3/d1;
         d2=d3/d1;d3=d2/d1;d2=d3/d1;d3=d2/d1;d2=d3/d1;
         d2=d3/d1;d3=d2/d1;d2=d3/d1;d3=d2/d1;d2=d3/d1;
         d2=d3/d1;d3=d2/d1;d2=d3/d1;d3=d2/d1;d2=d3/d1;
         d2=d3/d1;d3=d2/d1;d2=d3/d1;d3=d2/d1;d2=d3/d1;
         d2=d3/d1;d3=d2/d1;d2=d3/d1;d3=d2/d1;d2=d3/d1;
         d2=d3/d1;d3=d2/d1;d2=d3/d1;d3=d2/d1;d2=d3/d1;
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"double / double");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   x=(float) 0.1;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);
         x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);
         x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);
         x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);
         x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);
         x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);
         x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);
         x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);
         x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);
         x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);x=(float)log(1.+x);
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"log(float)");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   d2=0.2;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);
         d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);
         d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);
         d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);
         d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);
         d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);
         d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);
         d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);
         d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);
         d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);d2=log(d2+1.);
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"log(double)");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   x=(float) 0.1;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
      j++;
      for (i=0;i<TOP;i++)
         {
         x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);
         x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);
         x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);
         x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);
         x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);
         x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);
         x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);
         x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);
         x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);
         x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);x=(float)pow((double)x,0.1);
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"pow(float)");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   d2=0.1;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
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
   duracion = 1000.*FACTOR/j;
   strcpy(line,"pow(double)");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   d2=0.1;
   j=0;
   fin=clock()+(long) (CLOCKS_PER_SEC*FACTOR);
   while(clock()<fin)
      {
	   int k;
      j++;
      for (i=0;i<TOP;i++)
         {
         frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);
         frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);
         frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);
         frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);
         frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);
         frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);
         frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);
         frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);
         frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);
         frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);frexp(d2,&k);
         }
      }
   duracion = 1000.*FACTOR/j;
   strcpy(line,"frexp(double,&int)");
   printf( "%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);
   fprintf( stream,"%28s: %6lu %12f %10f\n", line, j, duracion, 50*TOP/duracion/1000);

   printf("=====================================================================\n");
   fclose(stream);
   scanf("%c%c",&c,&c);
   }
