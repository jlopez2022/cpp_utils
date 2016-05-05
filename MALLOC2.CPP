#include <stdio.h>
#include <malloc.h>

int i;

struct Tabla
   {
   int a;   
   int Nodo[100000];             /*Numero de nudo*/ 
   struct Tabla  *sig;
   } *s1,*s2,t1;
char c,*c1;
void Borra_Lista  (Tabla  *ptr);

void main(void)
{
s2=(Tabla *) malloc(sizeof(Tabla));
printf("\nMemoria S2=%Fp",(void *) s2);
printf("\nTamaño de memoria de S1=%d",_msize(s2));
free(s2);

s1=&t1;
//while (s1->sig=(Tabla *) malloc(sizeof(Tabla)))

//{
s1=&t1;
for (int i=0;i<100;i++)
{
s1->sig=(Tabla *) malloc(sizeof(Tabla));
s1->a=i+100;
s1=s1->sig;
}
s1->a=i+100;
s1->sig=NULL;
s1=&t1;

printf(" i=%7d",s1->a);



s1=t1.sig;
printf("\nTamaño de memoria de S1=%d",_msize(s1));
s2=(Tabla *) malloc(sizeof(Tabla));
printf("\nMemoria S2=%Fp",(void *) s2);
free(s2);

Borra_Lista(&t1);


s2=(Tabla *) malloc(sizeof(Tabla));
printf("\nMemoria S2=%Fp",(void *) s2);
free(s2);

scanf("%c%c",&c,&c);
}

void Borra_Lista  (Tabla  *ptr)
    {
    Tabla *Temp,*ini;
    Temp=ptr;ini=ptr;
    ptr=ptr->sig;
//	Temp->sig=NULL;
    while (ptr)
        {
        Temp = ptr;
        ptr = ptr->sig;
        free(Temp);
       }
	ini->sig=NULL;
    }
