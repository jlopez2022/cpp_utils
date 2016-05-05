#include <urlmon.h> //OJOO: añadir urlmon.lib en Projects->settings->linker: "urlmon.lib kernel32.lib user32.lib..."
#include <stdio.h>



int main()
{
	char urlname[1024]="http://finance.yahoo.com/d/quotes.csv?s=BBDB.TO+NT.TO+GE+MSFT&f=snl1d1t1ohgdr";
	if(URLDownloadToFile(0,urlname,"output.txt",0,0))
	{
		return -1;
	}
	return 1;
}

