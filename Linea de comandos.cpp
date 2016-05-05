#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leedato_long(FILE *str,long *dato,char *nombre);
void leelin(FILE *strin,char *lin);


void main(int argc,char *argv[],char **env)
{
	char directorio[1024]="DEFAULT";
	if (argc>1)
		strcpy(directorio,argv[1]);
	printf("\nDato=%s\n",directorio);
	getchar();
}

void leedato_long(FILE *str,long *dato,char *nombre)
{
	char linea[1024];
	long i;
	for (i=0;i<1024;i++)
	{
		linea[i]=fgetc(str); 
		if ((linea[i]==' ') || (linea[i]=='\t') || (linea[i]=='/') ) break;
	}
	linea[i]='\0';
	if (!strstr(linea,nombre))
	{
		printf("\nError en c_AWG420::leedato_ushort: no encuentro en LIB\\TABLA_CH1.txt la variable %s", nombre);
		getchar();getchar();
		exit(0xFF);
	}
	fscanf(str,"%i",&dato);leelin(str,linea);
}


void leelin(FILE *strin,char *lin)
{
	char c;
	while(!feof(strin))
	{
		c=fgetc(strin);
		if (c==0x0A)
			break;
		if (c!=0x0D)
			*lin++=c;
	}
	*lin='\0';
}
