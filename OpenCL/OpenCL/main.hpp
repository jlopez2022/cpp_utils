#ifndef __main_hpp
#define __main_hpp
/*
================= installation OpenCL================= 
En tarjeta AMD: 
Install last AMD driver
Install the AMD-SDK para for windows or linux as example at C:\Program Files (x86)\AMD APP SDK\3.0
copy directories 
	C:\Program Files (x86)\AMD APP SDK\3.0\bin\x86_64 en C:\Program Files (x86)\AMD APP SDK\3.0\bin\x64
	C:\Program Files (x86)\AMD APP SDK\3.0\lib\x86_64 en C:\Program Files (x86)\AMD APP SDK\3.0\lib\x64

Setup:
Project properties:
Configuration Manager : new x64 copy from Win32    eye!!!!!
If board is not AMD but a CUDA one then use environment variable AMDAPPSDKROOT or CUDA_PATH
C/C++  -> General: Additional include Directories:  $(AMDAPPSDKROOT)\include    ó  ..\libs\OpenCL\include
linker -> General: Additional library Directories: $(AMDAPPSDKROOT)\lib\x64    ó  ..\libs\OpenCL\lib
linker -> Input  : Additional Dependencies       : OpenCL.lib
*/

#include <iostream>
#include <time.h>
#include <stdlib.h> //rand()
#include <math.h> //sqrt
using namespace std;
typedef unsigned char uchar;
#include "Parallel.hpp"

class c_clase:public c_parallel
{
public:
	c_clase(int platform_number1, int device_number1, char *kernel_filename, char **kernel_function_name,int num_functions)
	{
		start=clock();
		init_gpu(platform_number1, device_number1, kernel_filename, kernel_function_name,num_functions);
		init_c_clase();timer(" c_clase::c_clase() ");
	}
	~c_clase(){delete[] data;}
	void init_rms(int size1);
	double function_rms_cpu();
	double function_rms_gpu();
	//calculates width and height where width*height=data_size; height=2*width as long as CPU speed is double than GPU nucleous
	void calculate_width_height(int &width,int &height);
private:
	void init_c_clase() { data=NULL;data_size=0; }
	float *data;
	int data_size; //max=2^31
	time_t start,stop;
	void timer(char *title);
};


#endif

