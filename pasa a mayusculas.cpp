#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main()
{

	FILE* strin=fopen("simbolos.txt","rb");
	FILE* strout=fopen("simbolos_out.txt","wb");

	while(!feof(strin))
	{
		char c;
		c=fgetc(strin);c=toupper(c);
		fputc(c,strout);
	}
	fclose(strin);
	fclose(strout);

	char orden;//q=salir c=continue
	while(1)
	{
		Sleep(500);
		if (_kbhit())
		{
			orden=_getch();getchar();
			if (orden=='q')
				break;
			else
				printf("\nQue hacemos: q=salir, c=continuar:");scanf("%c",&orden);orden=tolower(orden);
		}
		if (orden=='q')
			break;
	}
	return 1;
}