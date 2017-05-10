#include <iostream>
#include <chrono> //usleep
#include <thread>  //usleep


unsigned int microseconds;

DWORD ms = 1000;

void main()
{

	printf("\nEspera %ims",(int) ms);
	std::this_thread::sleep_for(std::chrono::microseconds(1000L*ms));
	printf("\nEspera %ims", (int)ms);
	std::this_thread::sleep_for(std::chrono::microseconds(1000L * ms));
	printf("\nEspera %ims", (int)ms);
	std::this_thread::sleep_for(std::chrono::microseconds(1000L * ms));

//	usleep(20000);//espera 20ms obsolete
	printf("\nFIN");getchar();getchar();

}