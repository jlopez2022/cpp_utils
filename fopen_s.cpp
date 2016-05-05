// Texto.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"


int _tmain()
{
	FILE *strin,*strout;   errno_t err,err1;
	err= fopen_s(&strin,"pruetxt.txt","r");
	err1=fopen_s(&strout,"out.txt","w");
	if ((err)||(err1)) 	{  printf("ERROR en ficheros");getchar();getchar(); return -1;  }
	long contadores[256],i;
	for (i=0;i<256;i++) contadores[i]=0;
	char chant=0,ch;
	while(!feof(strin))
	{
		ch=fgetc(strin);
		if (chant==' ')
			contadores[ch]++;
		chant=ch;
	}
	for (i=0;i<256;i++)
	{
		printf("%li\t%c\t%li\n",i,(char) i,contadores[i]);
		fprintf(strout,"%li\t%c\t%li\n",i,(char) i,contadores[i]);
	}
	getchar();getchar();
	_fcloseall( );
	return 0;
}

