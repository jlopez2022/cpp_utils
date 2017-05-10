#include <time.h>
#include <stdio.h>

//ver sleep

void espera(long segundos)
{
  long tiempo_final;
  tiempo_final=clock()+(long) (CLOCKS_PER_SEC*segundos);
  while(clock()<tiempo_final) {};
}


void main()
{
	for (long i=0;i<10;i++)
	{
		printf("\n%li",i);
		espera(3);
	}
}