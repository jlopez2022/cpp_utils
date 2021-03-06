//Funciona fen�meno!!!
//Devuelve un valor < dimension si hay una fila que es 
//multiplo de las otras. El valor devuelto es la fila correspondiente 
#include <stdio.h>
#include <time.h>

class matrizc
{
public:
	int inversa(double *x,double *y);
    void imprimematriz(double *x,char s[256]="");
	matrizc(int dim);
    int dimension;
};

matrizc::matrizc(int dim)
{
	dimension=dim;
}

int matrizc::inversa(double *x,double *y)
   {
   int i,j,ord;
   double *ptrx,*ptrx0,*ptry,*ptry0,*ptrx00,*ptry00,x0;
   for (ord=0;ord<dimension;ord++)
      {
      //Hacemos elemento diagonal=1
      ptrx0=x+ord*dimension+ord;
      ptry=y+ord*dimension;
      if (!*ptrx0) return ord;
      for (i=0;i<ord;i++)
         *ptry++/=*ptrx0; //y(ord,i<ord)=y/x(ord,ord)
      *ptry=1./ *ptrx0;   //y(ord,ord)  =1/x(ord,ord)
      ptrx=ptrx0+1;
      for (i=ord+1;i<dimension;i++)
         *ptrx++ /= *ptrx0; //x(ord,i>ord)=x/x(ord,ord)

      //Hacemos toda la columna "ord" =0 salvo el valor en (ord,ord)
      ptry00=y+dimension*ord;
      ptrx00=x+dimension*ord+ord+1;
      for (j=0;j<dimension;j++)  //todas las filas
      if (j!=ord)          //salvo la ord
         {
         ptrx=x+j*dimension+ord;x0=*ptrx;
         ptry=y+j*dimension;ptry0=ptry00;
         for (i=0;i<ord;i++) //columnas Y desde 0 a ord
            *ptry=(*ptry++)-(*ptry0++)*x0;
         *ptry=-(*ptry0++)*x0;//columna Y ord;
         
         ptrx++;ptrx0=ptrx00;
         for (i=ord+1;i<dimension;i++) //columnas x desde ord a dim
            *ptrx=(*ptrx++)-(*ptrx0++)*x0;
         }
      //imprimematriz(x,dim);
      //imprimematriz(y,dim);
      }//end ord
   return dimension;
   }

void matrizc::imprimematriz(double *x,char s[256])
   {
   int i,j;

   printf("matriz:%s\n",s);
   for (i=0;i<dimension;i++)
      {
      for (j=0;j<dimension;j++)
         printf(" %12g",x[i*dimension+j]);
      printf("\n");
      }
   }


void main()
   {
//   double x[4]={1.,2.,2.,3.};
   double x[25]={
         2.,	-5.,	-3.,	2.,	12.,
         -6.,	4.,	-2.,	1.,	13.,
         1.,	3.,	6.,	4.,	5.,
         -7.,	5.,	4.,	8.,	-9.,
         1.,	6.,	9.,	2.,	13.};
   char c;
   int i;
   int dimension=5;
   double *y=new double[dimension*dimension];
   matrizc matriz1(dimension);
   matriz1.imprimematriz(&x[0]," input");

   time_t antes,despues;
   time(&antes);
   int j;
   for (j=0;j<250000;j++)
     i=matriz1.inversa(&x[0],&y[0]);
   time(&despues); 
   if (i<dimension) printf("\nAtencion, la fila %i es multiplo de las anteriores",i);
   matriz1.imprimematriz(&y[0]," output");

   printf("\nTiempo=%ld",despues-antes);
   scanf("%c%c",&c,&c);
   }



