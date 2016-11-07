#include <windows.h>
#include <chrono>
#include <thread>
#include <stdio.h>

unsigned int microseconds;

DWORD ms = 1000;

void main()
{

	printf("\nEspera %ims", (int)ms);
	Sleep(ms);
	for (long i = 0; i < 600; i++)
	{
		printf("\nTime=%li Espera %ims", i, (int)ms);
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}
	printf("\nFIN"); getchar(); getchar();
}