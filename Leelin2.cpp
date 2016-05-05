//extrae datos NMEA y los mete en NMEA.txt
#include <stdio.h>
#include <string.h>

void leelin(FILE *strin,char *linea);


int main()
{
	return 1;
}

void leelin(FILE *strin,char *linea)
{
	//quito caracter 0x0D ademas de 0x0A
	int i;
	linea[0]='\0';
	char *ptr=linea;
	for (i=0;(i<1024 && !feof(strin)); i++)
	{
		fscanf(strin,"%c",ptr++);
		if (ptr[-1]==10)
			break;
	}
	//fscanf(strin,"%c",linea--);
	if (i>=1)
		ptr[-1]='\0';
	else
		linea[0]='\0';
	if (i>2 && ptr[-2]==0x0D)
		ptr[-2]='\0';
}

