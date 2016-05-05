//Prueba matriz de punteros
#include <stdio.h>


void main()
{
	int mat1[500];
	int i;
	for (i=0;i<500;i++)
	  mat1[i]=1000+i;

	int *ptr[100];
	for (i=0;i<100;i++)
	  ptr[i]=&mat1[i*2];
	i=10;
	for (i=0;i<100;i++)
	  if (*ptr[i]!=mat1[i*2])
	  {
		  printf("Error:no correcto");
		  char c;scanf("%c%c",&c,&c);
	  }
}