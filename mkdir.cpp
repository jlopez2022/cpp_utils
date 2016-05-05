#include <stdio.h>
#include <direct.h>


void main()
{
	_mkdir("FILE");
	FILE *str=fopen("FILE\\pru.txt","w");
	if (str)
		for (long i=0;i<100;i++)
			fprintf(str,"%li %04X\n",i,i);
	else
	{
		printf("\nERRORRRR");
		getchar();
	}
	fclose(str);
}