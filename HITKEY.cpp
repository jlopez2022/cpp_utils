// resolucion de ecuaciones por método de ?

#include <math.h>
#include <stdio.h>
#include <conio.h>

double y(double x)
   {
   double a;
   a=(1/pow(14.971,x) -1.)/5.5;
   printf("a=%.15lg",a);
   return(x-log(8.77)/log(a*4.5+1));
   }

void main()
{
   double delta;
   double x=1.13;
   char c;

	do
	  {
		  int c = getchar();
		  delta=x*1e-7;
		  x+= delta*y(x)/( y(x)-y(x+delta) );
		  printf("\nx=%.15lg",x);
	  }while (c!='q');
   c=scanf("%c%c",&c,&c);
}