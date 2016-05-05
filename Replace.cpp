#include <stdio.h>
#include <string.h>

void replace(char *linea,char *viejo,char *nuevo)
{
	char *ptr=linea;
	ptr=strstr(ptr,viejo);
	if (!ptr) return;

	long lon_v,lon_n;
	lon_v=strlen(viejo);
	lon_n=strlen(nuevo);
	char linea2[1024];
	strncpy(linea2,linea,(ptr-linea));linea2[(long) (ptr-linea)]='\0';
	strcat(linea2,nuevo);
	strcat(linea2,ptr+lon_v);
	strcpy(linea,linea2);
	replace(linea,viejo,nuevo);
}

void leelin(FILE *strin,char *linea)
{
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
}
/*
void main()
{//                    012345678901234567890123456789
	char linea[1024]={"Hola soy Javier Lopez Segura Lopez2 kk"};
	replace(linea,"Lopez","López");
	printf("\n%s",linea);
	char c;scanf("%c%c",&c,&c);
}
*/