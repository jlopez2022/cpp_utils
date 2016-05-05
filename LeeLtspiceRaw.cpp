//Lee .raw. Recomiendo hacer en LTspice .save V(1) I(R1) para reducir numero de datos leidos
//Además en el LTspice en Tools->control panel-compression marcar Ascii (luego dar a default para dejar como antes)
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>

void leelinea(FILE *str,char *lin)
{

	char *ptr=lin;

	do
	{
		*ptr=fgetc(str);
		if (*ptr==0x0A)
		{
			*ptr='\0';
			//fgetc(str);
			break;
		}
		ptr++;
	}while(!feof(str));
}


int main()
{
	printf("En LTspice en Tools->control panel-compression marcar Ascii");
	printf("\nUsar el comando .SAVE V(1) I(L1) para indicar que parametros salen en .raw");
	getchar();

    struct _finddata_t c_file;    
	long hFile;

    /* Find first .* file in current directory */
    if( (hFile = _findfirst( "*.raw",&c_file )) == -1L )
       return -1;   
	FILE *strin,*strout;
	strin=fopen(c_file.name, "r");
	_findclose( hFile );
	strout=fopen("out.xls","w");
	if (!strin || !strout)
	{
		printf("\nERRORen apertura de ficheros %s o out.xls",c_file.name);getchar();getchar();return -1;
	}

	char linea[10000],*ptr;

	//1. Leo el numero de variables
	while(!feof(strin))
	{
		leelinea(strin,linea);
		if (ptr=strstr(linea,"No. Variables:"))
			break;
	}
	if (!ptr)
		return -1;
	long numvariables;
	numvariables=strtol(linea+14,&ptr,10);

	//2. Leo el numero de puntos
	while(!feof(strin))
	{
		leelinea(strin,linea);
		if (ptr=strstr(linea,"No. Points:"))
			break;
	}
	if (!ptr)
		return -1;
	long numpuntos;
	numpuntos=strtol(linea+12,&ptr,10);

	//3. Leo nombres de variables
	while(!feof(strin))
	{
		leelinea(strin,linea);
		if (strstr(linea,"Variables:"))
			break;
	}
	char *nombrevar=new char[numvariables*500];
	long i,k;
	for (i=0;i<numvariables;i++)
	{
		fscanf(strin,"%li",&k);
		fscanf(strin,"%s",nombrevar+i*500);
		fscanf(strin,"%s",linea);
		fprintf(strout,"%s\t",nombrevar+i*500);
	}


	//4. Leo el tiempo y las variables
	while(!feof(strin))
	{
		leelinea(strin,linea);
		if (strstr(linea,"Values:"))
			break;
	}

	long j;
	for (j=0;j<numpuntos;j++)
	{
		fprintf(strout,"\n");
		fscanf(strin,"%li",&k);
		for (i=0;i<numvariables;i++)
		{
			double x;
			fscanf(strin,"%lg",&x);
			fprintf(strout,"%lg\t",x);
		}
	}

	delete[] nombrevar;
	fclose(strin);fclose(strout);
	return 1;
}