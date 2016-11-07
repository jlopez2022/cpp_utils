//lee de un fichero linea por linea, sea cual sea el caracter de fin de linea
#include <iostream>
#include <stdio.h>  //fopen
#include <string.h>
using namespace std; //cin,cout

//Lee de ficheros:
void leelin(FILE *strin, char *linea);
//Lee de cadena de caracteres. retorna 1 cuando acaba
int leelin(char *strin, char *linea, char **ptr2);


int main()
{
	char texto[] = "lineas= 7\
				   	Este es el texto a extraer\
					x   y     \
					== == === \
					10, 122.3 \
					11, 130, 5 \
					12, 120.2  \
					13, 130.1";

	char linea[1025], *ptr = texto, *ptr2;
	long top = 100;
	leelin(ptr, linea, &ptr);
	top = strtol(linea + 7, &ptr2, 10);
	int fin = 0;
	for (long i = 0; !fin; i++)
	{
		fin = leelin(ptr, linea, &ptr);
		cout << linea << "#" << endl;
	}


	cout << endl << endl;
	cout << "=================== END ======================" << endl << endl;
	getchar(); getchar();
}

void leelin(FILE *strin,char *linea)
{
	//quito caracter 0x0D ademas de 0x0A
	int i;
	linea[0]='\0';
	char *ptr=linea;
	for (i=0;(i<1024 && !feof(strin)); i++)
	{
		*ptr++ = fgetc(strin);
		//fscanf(strin, "%c", ptr++);  //OLD!!
		if (ptr[-1] == 10)
			break;
	}
	if (i>=1)
		ptr[-1]='\0';
	else
		linea[0]='\0';
	if (i>2 && ptr[-2]==0x0D)
		ptr[-2]='\0';
}

int leelin(char *strin, char *linea, char **ptr2)
{
	//quito caracter 0x0D ademas de 0x0A
	int i;
	for (i = 0;; i++)
	{
		if ((strin[i] == '\t') || (strin[i] == 0x0D) || (strin[i] == 0x0A) || (strin[i] == 0x0) || (i >= 1022))  break;
		linea[i] = strin[i];
	}
	linea[i] = '\0';
	if (strin[i + 1] != '\t')
		*ptr2 = &(strin[i + 1]);
	else
		*ptr2 = &(strin[i + 2]);
	if (strin[i] == 0x0) return 1;
	return 0;
}

