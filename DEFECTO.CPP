//Funciones con valores por defecto

#include <stdio.h>

//void prueba(int,...);

int prueba(int i=0,int j=100,int k=10000);

int prueba(int i,int j,int k)
   {
   return(i+j+k);
   }

void main()
{
char c;
printf("%i\n",prueba() );
printf("%i\n",prueba(1));
printf("%i\n",prueba(2,200));
printf("%i\n",prueba(3,300,30000));
scanf("%c%c",&c,&c);
}
