#include <stdio.h>

typedef int int2[10][10];
void escribe(int2 &a);

void main()
   {
   int i,j;
   int2 a;
   char c;
   escribe(a);
   for(i=0;i<10;i++)
      {
      printf("\n");
      for(j=0;j<10;j++)
         printf("%5i",a[i][j]);
      }
   scanf("%c%c",&c,&c);
   }


void escribe(int2 &a)
   {
   int i,j;
   for(i=0;i<10;i++)
      for(j=0;j<10;j++)
         a[i][j]=(i+1)*100+j;
   return;
   }
