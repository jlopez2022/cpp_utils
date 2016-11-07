#include <windows.h>
#include <unistd.h> usleep

unsigned int microseconds;

DWORD ms = 1000;

void main()
{

	printf("\nEspera %ims",(int) ms);
	Sleep(ms);
	printf("\nEspera %ims", (int)ms);
	Sleep(ms);
	printf("\nEspera %ims", (int)ms);
	Sleep(ms);

	usleep(20000);//espera 20ms 
	printf("\nFIN");getchar();getchar();

}