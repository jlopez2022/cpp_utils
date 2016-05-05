//PROBLEMA: tarda en leer porque los guarda en un fichero del disco duro!!!
//#include <stdio.h>
#include <tchar.h>

#include <windows.h>
#include <Urlmon.h> //You also need to link Urlmon.lib to compile!!!!!
#include <string.h>

int main()
{
	printf("URLDownloadToFile test function.\n");

	TCHAR url[] = TEXT("http://google.com");

	printf("Url: %S\n", url);

	TCHAR path[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, path);
	strcat_s(path,sizeof(path),"/index.html");

//	wsprintf(path, TEXT("%s\\index.html"), path);

	printf("Path: %s  \n", path);

	HRESULT res = URLDownloadToFile(NULL, url, path, 0, NULL);

	if (res == S_OK) {
		printf("Ok\n");
	}
	else if (res == E_OUTOFMEMORY) {
		printf("Buffer length invalid, or insufficient memory\n");
	}
	else if (res == INET_E_DOWNLOAD_FAILURE) {
		printf("URL is invalid\n");
	}
	else {
		printf("Other error: %d\n", res);
	}
	printf("\nEND");getchar(); getchar();

	return 0;
}