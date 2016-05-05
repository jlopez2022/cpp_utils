//Ordenaciones rapida y shell 
//(comprobadas hasta 2800 elementos)
#define TOP 40000
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void error(double x,char *linea1="",char *linea2="",char *linea3="",char *linea4="",char *linea5="");
void rapida       //ordenacion rapida
   (
   double *matriz,
   int izq,       // desde donde se ordena
   int cont       // hasta donde se ordena
   );
void rapida11(double *matriz,int izq,int der); /* ordenacion rapida */
void shell(double *matriz,int cont); //ordenacion shell
long contador=0;  // contador de veces (suprimir)
int *orden;

void main()
   {
   int i,longitud,metodo;
   double matriz[TOP],matriz2[TOP];
   char linea[3000];
   FILE *stream,*stream2;
   clock_t inicio,fin;
   printf("Introducir fichero de entrada:");scanf("%s",linea);
   printf("Ahora elegir el método: 1=rrapida, 2=shell, 11=rapida con salida orden :");scanf("%i",&metodo);

   stream=fopen(linea,"r");
   if (!stream)
      error(-1.,"Error al abrir fichero",linea);
   char *buffer;buffer= new char[TOP];
   if( setvbuf( stream, buffer, _IOFBF, sizeof( buffer ) ) != 0 )
      error(-1., "Incorrect type or size of buffer for stream1\n" );
   i=0;
   float ix;
   while(!feof(stream))
      {
      fscanf(stream,"%f",&ix);
      matriz[i]=(double) ix;
      i++;
      }
   fclose(stream);
   longitud=i;
   switch(metodo)
      {
      case 2:
      {
      printf("La salida es shell.txt\n");
      contador=0;
      for (i=0;i<longitud;i++)   matriz2[i]=matriz[i];
      inicio=clock();
      shell(matriz2,longitud);
      fin=clock();
      printf("\nPrueba de tiempos con %i elementos",longitud);
      printf("\nShell :%i %li",contador,(long) (fin-inicio));
      stream2=fopen("shell.txt","w");
      for (i=0;i<longitud;i++)  fprintf(stream2,"%f\n",matriz2[i]);
      fclose(stream2);
      break;
      }
      case 1:
      {
      printf("La salida es rapida.txt\n");
      contador=0;
      for (i=0;i<longitud;i++)   matriz2[i]=matriz[i];
      inicio=clock();
      rapida(matriz2,0,longitud-1);
      fin=clock();
      printf("\nRapido:%i %li",contador,(long) (fin-inicio));
      printf("\nLongitud=%i",longitud);
      stream2=fopen("rapida.txt","w");
      for (i=0;i<longitud;i++)  fprintf(stream2,"%f\n",matriz2[i]);
      fclose(stream2);break;
      }
      case 11:
      {
      int *ptr;
      orden=new int[longitud];ptr=orden;
      for (i=0;i<longitud;i++)  *ptr++=i;
      printf("La salida es rapida.txt\n");
      contador=0;
      for (i=0;i<longitud;i++)   matriz2[i]=matriz[i];
      inicio=clock();
      rapida11(matriz2,0,longitud-1);
      fin=clock();
      printf("\nRapido:%i %li",contador,(long) (fin-inicio));
      printf("\nLongitud=%i",longitud);
      stream2=fopen("rapida.txt","w");
      for (i=0;i<longitud;i++)  fprintf(stream2,"%10i : %f\n",orden[i],matriz2[i]);
      fclose(stream2);break;
      }
      }//fin switch

   char c;
   scanf("%c%c",&c,&c);
   }

void rapida(double *matriz,int izq,int der) /* ordenacion rapida */
   {
   int i,j;
   double x,y;
   i=izq;j=der;
//   x=matriz[(int)(.5+(izq+der)/2.)];
   x=.5*(matriz[izq]+matriz[der]);
   do
      {
      while(matriz[i]<x && i<der) i++;
      while(x<matriz[j] && j>izq) j--;
      
      if (i<=j)
         {
         y=matriz[i];
         matriz[i]=matriz[j];
         matriz[j]=y;
         i++;j--;
         contador++; // QUITAR:solo cuenta nº veces
         }
      } while(i<=j);

   if (izq<j) rapida(matriz,izq,j);
   if (i<der) rapida(matriz,i,der);
   }

void shell(double *matriz,int cont)
   {
   int i,j,k,s,w,a[5]={9,5,3,3,1};
   double x;
   
   for(w=0;w<5;w++)
      {
      k=a[w];s=-k;
      for(i=k;i<cont;++i)
         {
         x=matriz[i];
         j=i-k;
         if(s==0)
            {
            s=-k;
            s++;
            matriz[s]=x;
            }
         while(x<matriz[j] && j>=0 && j<=cont)
            {
            matriz[j+k]=matriz[j];
            j=j-k;
            contador++;
            }
         matriz[j+k]=x;
         }
      }
   }


void rapida11(double *matriz,int izq,int der) /* ordenacion rapida */
   {
   int i,j,k;
   double x,y;
   i=izq;j=der;
//   x=matriz[(int)(.5+(izq+der)/2.)];
   x=.5*(matriz[izq]+matriz[der]);
   do
      {
      while(matriz[i]<x && i<der) i++;
      while(x<matriz[j] && j>izq) j--;
      
      if (i<=j)
         {
         y=matriz[i];         k=orden[i];
         matriz[i]=matriz[j]; orden[i]=orden[j];
         matriz[j]=y;         orden[j]=k;
         i++;j--;
         contador++; // QUITAR:solo cuenta nº veces
         }
      } while(i<=j);

   if (izq<j) rapida(matriz,izq,j);
   if (i<der) rapida(matriz,i,der);
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
