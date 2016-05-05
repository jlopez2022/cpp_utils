#include <malloc.h>
#include <stdio.h>

struct Tabla
   {
   int a;   
   int Nodo;             /*Numero de nudo*/ 
   struct Tabla_1  *sig;
   } *s1,*s2,t1;
char c,*c1;

void main(void)
{
s1=(Tabla *) calloc(100000,sizeof(Tabla));
printf("\nMemoria1 = %10ld    en la dirección = %Fp",_msize(s1),(void *) s1);
s1=(Tabla *) calloc(10000,sizeof(Tabla));
printf("\nMemoria1 = %10ld    en la dirección = %p",_msize(s1),(void *) s1);
c1=(char *) calloc(4,sizeof(char));
printf("\nMemoria1 = %10ld    en la dirección = %p",_msize(c1),(void *) c1);
free(s1);
printf("\nMemoria2 = %10ld",_msize(s1));
scanf("%c%c",&c,&c);
}												 
