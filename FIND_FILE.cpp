#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100000//1048576

char line[256];

void find_file(char *s,int &fin)//Inicialmente fin=0
{
	if (fin==1)
		return;

	char fich[256];
	strcpy(fich,s);
	strcat(fich,"\\\\*.*");

    struct _finddata_t c_file;    
	long hFile;

    /* Find first .* file in current directory */
    if( (hFile = _findfirst( fich,&c_file )) == -1L )
       return;   
	else do   
	{
		printf("%s%s\t%X\t%li\n",s,c_file.name,c_file.attrib,c_file.size);
		if (c_file.attrib==_A_SUBDIR)
		{//Es un subdirectorio, mirar dentro
			if (c_file.name[0]!='.')
			{
				char fich1[256];
				strcpy(fich1,s);
				strcat(fich1,"\\\\");
				strcat(fich1,c_file.name);
				find_file(fich1,fin);
			}
		}
		if (c_file.size>SIZE)
		{
			fin=1;
			strcpy(line,s);
			strcat(line,"\\\\");
			strcat(line,c_file.name);
			return;
		}


	}while( _findnext( hFile, &c_file ) == 0 );
	_findclose( hFile );
}

void main( void )
{
	char s1[256]="A:";
	int fin=0;
	find_file(s1,fin);
	if (fin==1)
		printf("Resultado= #%s#\n",line);


	char c;printf("\nFIN");scanf("%c%c",&c,&c);
}
