#include <stdio.h>

void main()
   {
   char formato[]="\nfichero num=%i nombre='%s'";
   char fichero[]="ficha.raw";
   int i=133;

   printf(formato,i,fichero);
   }
