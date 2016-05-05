/***************************************************************************
*                                                                          *
*                                                                          *
*       C lculo de MATRIZ INVERSA NxN  usando DETERNXN.pas                 *
*                                                                          *
*       meter  [Y]=1 en los N casos cuando no haya factor de multiplicacion*
*                                                                          *
*                                                                          *
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX 10    /*Maximo posible*/

double detN(int i3);
double det3();

double a[MAX][MAX], x[MAX], y[MAX], z[MAX];
double m[MAX-2][MAX][MAX];
double resul[MAX][MAX];

void main()
{
float ix;
int i,j,k,N,n;
double det;
char c;

FILE *stream=fopen("matriz.txt","r");
if (!stream)
   {
   printf("\nNo se puede abrir fichero matriz.txt");scanf("%c%c",&c,&c);
   exit(-2);
   }
fscanf(stream,"%i",&N);

for (i=0;i<N;i++)
   {
   for (j=0;j<N;j++)
      {
      z[i]=1;
      fscanf(stream,"%f",&ix);a[i][j]=ix;
      }
   z[i]=1;
   }

printf("====================================================\n");

/* C lculo del determinante: */
for (i=0;i<N;i++) for (j=0;j<N;j++) m[N-3][i][j]=a[i][j];
det=detN(N-3);printf("\n DET =%lg",det);

/* Calculo de las X(k): */
printf("\nMatriz traspuesta:");
for (n=0;n<N;n++)
   {
   for (i=0;i<N;i++) if (i==n) y[i]=z[i]; else y[i]=0;
   printf("\n");
   for (k=0;k<N;k++)
      {
      for (i=0;i<N;i++)
         if (i==k) for (j=0;j<N;j++) m[N-3][j][i]=y[j];
         else      for (j=0;j<N;j++) m[N-3][j][i]=a[j][i];

      x[k]=detN(N-3)/det;
      printf(" %-12.7lg",x[k]);
      }
   }
scanf("%c%c",&c,&c);
}

double detN(int i3)
{
int top=i3+3;
int j1,j2,j3,u=0;
double r=0;
int signo=1;

if (i3>0)
{for (j1=0;j1<top;j1++)
 {u=0;for (j2=0;j2<top;j2++)
     if (j2!=j1) {for (j3=1;j3<top;j3++) m[i3-1][j3-1][u]=m[i3][j3][j2];
		  u++;
		 }  /* end if */


  if (i3==1)  r = r + m[i3][0][j1]*signo*det3();
  else        r = r + m[i3][0][j1]*signo*detN(i3-1);
  signo=-signo;
 }
 return r;
}
 else return det3();

} /* END funcion */


double det3()
{
double x1,x2;

x1=m[0][0][0]*m[0][1][1]*m[0][2][2]+m[0][0][2]*m[0][1][0]*m[0][2][1]+
   m[0][2][0]*m[0][0][1]*m[0][1][2];
x2=m[0][0][2]*m[0][1][1]*m[0][2][0]+m[0][2][1]*m[0][1][2]*m[0][0][0]+
   m[0][2][2]*m[0][0][1]*m[0][1][0];

return x1-x2;
}

