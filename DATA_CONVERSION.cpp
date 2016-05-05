#include <stdio.h>
#include <stdlib.h>

void main(void)
{char linea[100],c;
int i;

for (i=0;i<15;i++)
  {
  _ltoa(i,linea,10);
  printf("\n%i=%s#",i,linea);
  }
scanf("%c%c",&c,&c);
}
