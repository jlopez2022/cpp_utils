#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <io.h>


void main()
{
	char directorio[_MAX_PATH];
	_getcwd(directorio,_MAX_PATH);
	printf("\ndirectorio actual= %s",directorio);
	//strcpy(directorio,"d:\\ajavier");
	printf("\nMeter directorio a escanear: ");scanf("%s",directorio);
	char clave[256]="*.*",clave2[256]=".bmp";
	//printf("\nMeter clave: ");scanf("%s",clave2);
	//if (_chdir("d:\\ajavier") )
	if (_chdir(directorio) )
	{
		printf("\nNo se puede abrir directorio");
		char c; scanf("%c%c",&c,&c);
	}
	_getcwd(directorio,_MAX_PATH);
	printf("\ndirectorio actual= %s",directorio);
	long fich;
	struct _finddata_t file; 
	fich=_findfirst(clave,&file);

	do
	{
		if (file.name[0]!='.')
		{
			printf("\n%30s  %li",file.name,file.size);
			if (file.attrib==_A_SUBDIR)
				printf("\t Subdirectorio");
			char nombre[1024];
			strcpy(nombre,file.name);
			int i=0;
			do
			{
				if ( (nombre[i]>='A') && (nombre[i]<='Z') )
					nombre[i]+='a'-'A';
			}while(nombre[i++]!='\0');
			if (strstr(file.name,clave2))
				printf("\t tipo .bmp");
		}
	}while(!_findnext(fich,&file));
	_findclose( fich );

	char c; scanf("%c%c",&c,&c);
}