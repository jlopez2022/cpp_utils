//Inversa 17-2-97 : MUY RAPIDA!! :FALTA COMPROBAR
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
double *matriz,*matriz2;
int ancho;
void error(int tipo,double x,char *linea1="",char *linea2="",char *linea3="",char *linea4="",char *linea5="");
void intercambiafilas(int i);

void main()
   {
   int i,j;
   FILE *stream;
   char fichero[64];
   //entrada de datos
   printf("Introducir fichero entrada datos.\n(Ojo elemento 1 es ancho de matriz) :");
   scanf("%s",fichero);
   stream=fopen(fichero,"r");
   if (!stream)
      error(2,-1,"No se puede abrir fichero : ",fichero);
   fscanf(stream,"%i",&ancho);
   matriz =(double *)malloc(ancho*ancho*sizeof(double));
   matriz2=(double *)malloc(ancho*ancho*sizeof(double));
   float x1;double *ptr=matriz;
   for(i=0;i<ancho*ancho;i++)
      {fscanf(stream,"%g",&x1);*ptr++=(double) x1;}
   fclose(stream);
   //matriz identidad:
   ptr=matriz2;
   for(i=0;i<ancho;i++)
      for(j=0;j<ancho;j++)
      if(i==j)
         *ptr++=1;
      else
         *ptr++=0;

   //cálculo:
   ptr=matriz;int k;double x,determinante=1;
   for(i=0;i<ancho;i++)
      {
      if (matriz[i*ancho+i]==0)
         intercambiafilas(i);
      for(j=0;j<ancho;j++)
      if (matriz[i*ancho+j]!=0)
         {
         if(j!=i)
            {
            x=matriz[i*ancho+j]/matriz[i*ancho+i];
            for (k=0;k<ancho;k++)
               matriz2[k*ancho+j]-=matriz2[k*ancho+i]*x;

            for (k=i;k<ancho;k++)
               matriz[k*ancho+j]-=matriz[k*ancho+i]*x;
            }
         else
            {
            determinante*=matriz[i*ancho+i];
            x=1./matriz[i*ancho+i];
            for (k=0;k<ancho;k++)
               matriz2[k*ancho+j]*=x;

            for (k=i;k<ancho;k++)
               matriz[k*ancho+j]*=x;
            }
         }
      }
   //impresion de resultados en out.txt
   stream=fopen("out.txt","w");
   fprintf(stream,"%i",ancho);ptr=matriz2;
   for(i=0;i<ancho*ancho;i++)
      {
      if(i%ancho==0) 
         fprintf(stream,"\n");
      x1=(float) *ptr;ptr++;
      fprintf(stream,"%g ",x1);
      }
   fclose(stream);
   free(matriz);
   free(matriz2);
   char c;
   printf("Resultado en 'out.txt'\nDeterminante=%f",determinante);scanf("%c%c",&c,&c);
   }

void error(int tipo,double x,char *linea1,char *linea2,char *linea3,char *linea4,char *linea5)
   {
   char c;
   switch(tipo)
      {
      case 0:{printf("\n%s%s%s%s%s",linea1,linea2,linea3,linea4,linea5);break;}
      case 1:{printf("\nWarning:%s%s%s%s%s",linea1,linea2,linea3,linea4,linea5);break;}
      case 2:{printf("\nError:%s%s%s%s%s",linea1,linea2,linea3,linea4,linea5);break;}
      }
   if (x!=-1.)
      printf("%f",x);
   scanf("%c%c",&c,&c);
   if (tipo>1) 
      exit(-2);
   }


void intercambiafilas(int lin)
   {
   int j;
   for(j=lin+1;j<ancho;j++)
      if (matriz[lin*ancho+j]!=0)
         break;
   if(j==ancho)
      {error(1,(double) lin,"Fila nula : ");return;}
   double x;
   int i;
   for(i=0;i<ancho;i++)
      {
      x=matriz2[i*ancho+lin];
      matriz2[i*ancho+lin]=matriz2[i*ancho+j];
      matriz2[i*ancho+j]=x;
      }
   for(i=lin;i<ancho;i++)
      {
      x=matriz[i*ancho+lin];
      matriz[i*ancho+lin] = matriz[i*ancho+j];
      matriz[i*ancho+j  ] = x;
      }
   return;
   }