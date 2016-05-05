#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996) //o cualquier otro 
#define SIZE 100//1048576
#define LINESIZE 0

void leelin(FILE *strin,char *linea);

void main( void )
{
	char fich[256];

    struct _finddata_t c_file;    
	long hFile;
	long total_lineas=0,linea1;
	double total_b=0.0;

    // SOURCE FILES
	printf("==== Looking for *.cpp source files ====\n");
 	strcpy(fich,"*.cpp");linea1=0;
	if( (hFile = _findfirst( fich,&c_file )) != -1L )
	do
	{
		long lineas=0;
		printf("%s\t size=%likb",c_file.name,c_file.size/1024);
		total_b+=c_file.size;
		if (c_file.size>SIZE)
		{
			FILE *str=fopen(c_file.name,"r");
			if (!str)
				printf(" can not be opened\n");
			else
			{
				while(!feof(str))
				{
					char linea[10000];
					leelin(str,linea);
					long longlin=strlen(linea);
					if (longlin > LINESIZE)
						lineas++;
				}
				printf(" lineas=%li\n",lineas);
				linea1+=lineas;
			}
		}
	}while( _findnext( hFile, &c_file ) == 0 );
	total_lineas+=linea1;
	printf("Lineas *.cpp=%li\n\n",linea1);

    // HEADER FILES
	printf("==== Looking for *.h header   files ====\n");
 	strcpy(fich,"*.h");linea1=0;
   if( (hFile = _findfirst( fich,&c_file )) != -1L )
   do
   {
		long lineas=0;
		printf("%s\t size=%likb",c_file.name,c_file.size/1024);
		total_b+=c_file.size;
		if (c_file.size>SIZE)
		{
			FILE *str=fopen(c_file.name,"r");
			if (!str)
				printf(" can not be opened\n");
			else
			{
				while(!feof(str))
				{
					char linea[10000];
					leelin(str,linea);
					long longlin=strlen(linea);
					if (longlin > LINESIZE)
						lineas++;
				}
				printf(" lineas=%li\n",lineas);
				linea1+=lineas;
			}
		}
		else
			printf("\n");
	}while( _findnext( hFile, &c_file ) == 0 );
	total_lineas+=linea1;
	printf("Lineas *.h=%li\n\n",linea1);

	    // OPENCL FILES
	printf("==== Looking for *.cl header   files ====\n");
 	strcpy(fich,"*.cl");linea1=0;
    if( (hFile = _findfirst( fich,&c_file )) != -1L )
	do
	{
		long lineas=0;
		printf("%s\t size=%likb",c_file.name,c_file.size/1024);
		total_b+=c_file.size;
		if (c_file.size>SIZE)
		{
			FILE *str=fopen(c_file.name,"r");
			if (!str)
				printf(" can not be opened\n");
			else
			{
				while(!feof(str))
				{
					char linea[10000];
					leelin(str,linea);
					long longlin=strlen(linea);
					if (longlin > LINESIZE)
						lineas++;
				}
				printf(" lineas=%li\n",lineas);
				linea1+=lineas; 
			}
		}
		else
			printf("\n");
	}while( _findnext( hFile, &c_file ) == 0 );
	total_lineas+=linea1;
	printf("Lineas *.cl=%li\n\n",linea1);

	_findclose( hFile );
	printf("\n TOTAL lineas = %li",total_lineas);
	printf("\n TOTAL kb     = %lg",1.0/1024.0*total_b);
	printf("\n==== FIN ====\n");getchar();getchar();
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