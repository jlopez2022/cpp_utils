//HIT KEY
#include <stdio.h>
#include <conio.h>

void main()
   {
   int i;
   printf("\nHit keys,Fin=q\n");
   while ((i=_getche())!='q')
      printf("\nASCII(%c)=%-4i ",i,i);
   }