#include <iostream>

int main()
{
#ifndef __linux__   //Introduce this code at the beginning of main() to increase a lot the speed of cout in windows: 
	char buf[4000]; setvbuf(stdout, buf, _IOFBF, sizeof buf);
#endif



	printf("\n\n===FIN===");getchar();getchar();
	return 1;
}

