#include <urlmon.h> //OJOO: añadir urlmon.lib en Projects->settings->linker: "urlmon.lib kernel32.lib user32.lib..."
#include <stdio.h>

#include <time.h>

int main()
{

	char urlname[1024]="http://finance.yahoo.com/d/quotes.csv?s=BBDB.TO+NT.TO+GE+MSFT&f=snl1d1t1ohgdr";


	int ini;double tiempo0,tiempo1;
	long i;

	//Primer sistema: guardo en fichero los datos de 1 valor solo:
	ini=clock();
	for (i=0;i<10;i++)
	if(URLDownloadToFile(0,urlname,"output.txt",0,0))
	{
		return -1;
	}
	tiempo0=1.0*(clock()-ini)/CLOCKS_PER_SEC;

	//Segundo sistema: Cojo datos de varios tickers directamente en un buffer
	IStream *pStream;
	ini=clock();
	for (i=0;i<10;i++)
	{
		URLOpenBlockingStream( 0, urlname, &pStream, 0, 0);
		char buffer[10240];
		DWORD dwGot;
		HRESULT hr = NOERROR;
		do //No hace falta el bucle do{} si el tamaño del buffer es suficientemente grande
		{
			hr = pStream->Read( buffer, sizeof(buffer), &dwGot );

			char *ch=buffer;
			ch=ch;
    
			//.. do something with contents of buffer ...
		} while( !hr );
	}
	tiempo1=1.0*(clock()-ini)/CLOCKS_PER_SEC;

	printf("\nTiempo 10 veces URLDownloadToFile:%lg",tiempo0);
	printf("\nTiempo 10 veces pStream->Read    :%lg",tiempo1);
	printf("\nFIN");getchar();getchar();

	return 1;
}

