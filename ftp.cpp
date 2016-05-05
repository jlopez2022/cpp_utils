#include <stdio.h>
#include <process.h>

/*
Este programa copia un fichero en una direccion ftp y debe estar en el
mismo directorio que contenga un fichero PUT.bat con las siguientes lineas:

open 192.168.4.27
user /n /n
binary 
put FOTO.PAT FOTO.PAT
close 
bye 
off
*/

void main()
{
	system("ftp -n -s:PUT.bat");
	printf("\nEnd");
	
	getchar();
}
