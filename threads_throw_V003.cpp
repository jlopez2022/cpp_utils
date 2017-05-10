#include <iostream>
#include <thread>  //threads
#include <stdlib.h> //system
#include <stdio.h> //to read data from file
#ifndef __linux__
#pragma warning(disable:4996) 
#endif


// linux compilation:         g++ -std=c++11 -pthread -o throw_threads throw_V001.cpp
//needs a file throw.txt with parameters:

//Lee linea:
void leelin(FILE *strin, char *linea);

using namespace std;

int autoejecuta(char *command)
{
	system(command);
	return 1;
}

int main()
{
	std::thread tarea[64];//100=maximum number of threads
	FILE *str=fopen("throw.txt","r");
	if(!str)
	{
		cout << "ERROR at throw.exe the file thread.txt is not found" << endl;getchar();return -777;
	}

#ifdef __linux__
	char cmd0[1024] = "./ecoscale_exe ";
#else
	char cmd0[1024] = "Ecoscale.exe ";
#endif

	char linea[1024], command[64][100];
	leelin(str, linea);//flush first line
	int i,numthreads;
	for (i = 0; i < 64; i++)
	{
		leelin(str, linea);
		if (strlen(linea) < 5)
			break;
		strcpy(command[i], cmd0);
		strcat(command[i], linea);
	}
	numthreads=i;
	fclose(str); 

	for (i = 0; i < numthreads; i++)
	{
		cout << "Throwing thread " << i << " " << command[i] << endl;
		tarea[i] = std::thread(autoejecuta, command[i]);
	}
	for (int i = 0; i < numthreads; i++)
	{
		if (tarea[i].joinable())
			tarea[i].join();
	}
	cout << "END all threads" << endl;
	getchar();
	return 0;
}


void leelin(FILE *strin, char *linea)
{
	//quito caracter 0x0D ademas de 0x0A
	int i;
	linea[0] = '\0';
	char *ptr = linea;
	for (i = 0; (i<1024 && !feof(strin)); i++)
	{
		*ptr++ = fgetc(strin);
		//fscanf(strin, "%c", ptr++);  //OLD!!
		if (ptr[-1] == 10)
			break;
	}
	if (i >= 1)
		ptr[-1] = '\0';
	else
		linea[0] = '\0';
	if (i>2 && ptr[-2] == 0x0D)
		ptr[-2] = '\0';
}