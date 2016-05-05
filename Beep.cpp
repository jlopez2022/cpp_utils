#include <stdio.h>
#include <windows.h>


int main()
{
	Beep(523,500); // 523 hertz (C5) for 500 milliseconds
	Beep(587,500);
	Beep(659,500);
	Beep(698,500);
	Beep(784,500);
	return 1;
}