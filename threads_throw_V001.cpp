#include <iostream>
#include <thread>  //threads
#include <stdlib.h> //system
#ifndef __linux__
#pragma warning(disable:4996) 
#endif
#define NUM_THREADS 4


// compilation:         g++ -std=c++11 -pthread -o throw_threads throw_V001.cpp
//execution: ./throw_threads


using namespace std;

int autoejecuta(char *command)
{
	system(command);
	return 1;
}

int main()
{
	std::thread tarea[NUM_THREADS];
#ifdef __linux__
	char command1[] = "./ecoscale_exe 0 KNP 0"; 
	char command2[] = "./ecoscale_exe 1 BCP 1";
	char command3[] = "./ecoscale_exe 0 BCP 2";
	char command4[] = "./ecoscale_exe 1 BCP 3";
#else
	char command1[] = "Ecoscale_41.exe 0 KNP 0"; 
	char command2[] = "Ecoscale_41.exe 0 BCP 1";
	char command3[] = "Ecoscale_41.exe 0 BCP 2";
	char command4[] = "Ecoscale_41.exe 0 BCP 3";
#endif
	cout << "Throwing thread-0 using KNP on board-0"<<endl;
	tarea[0] = std::thread(autoejecuta, command1);
	cout << "Throwing thread-1 using BCP on board-1"<<endl;
	tarea[1] = std::thread(autoejecuta, command2);
	cout << "Throwing thread-2 using BCP on board-0"<<endl;
	tarea[2] = std::thread(autoejecuta, command3);
	cout << "Throwing thread-3 using BCP on board-1"<<endl;
	tarea[3] = std::thread(autoejecuta, command4);
	for (int i = 0; i < NUM_THREADS; i++)
	{
		if (tarea[i].joinable())
			tarea[i].join();
	}
	cout << "END all threads" << endl;
	return 0;
}
