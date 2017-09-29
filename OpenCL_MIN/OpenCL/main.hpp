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
Configuration Manager : new x64 copy from Win32    caution!!!!!
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
typedef unsigned short ushort;
#include "Parallel.hpp"

const int WINDOW_SIZE=7;

class c_clase:public c_parallel
{
public:
	c_clase(int platform_number1, int device_number1, char *kernel_filename, char **kernel_function_name,int num_functions)
	{
		test();
		start=clock();
		cout<<"=== ini GPU inicialization ==="<<endl;
		init_gpu(platform_number1, device_number1, kernel_filename, kernel_function_name,num_functions);
		cout<<"=== end GPU inicialization ==="<<endl;
		init_c_clase();
		timer(" c_clase::c_clase() ");
	}
	~c_clase(){delete[] gray1;delete[] gray2;delete[] gray3;delete[] grayBG;delete[] coefy;delete[] coefxy1;}
	void funcion_KNP_gpu();
	void funcion_BDP_gpu();

private:
	void init_c_clase();
	uchar *gray1,*gray2,*gray3,*grayBG;
	int data_size; //max=2^31

	time_t start,stop;
	void timer(char *title);
	
	int xmax,ymax,pixels,xmed;
	//Fills data1 or 2 and xmax and ymax:
	bool read_image_ppm(char *filename, uchar  *&data, int &xmax1,int &ymax1);
	bool save_image_ppm(char *filename, uchar  *data,int xmax1,int ymax1);
	void save_int(char *filename,int *data,int size);
	void save_float(char *filename,float *data,int size);

	float *coefy; 	double sum_coefy1,sum_coefy2;
	ushort *coefxy1;  double mask_xy_area1,mask_xy_area2,coefxy_sf;
	//Fills coefy, sum_coefy1 and 2 and xmed:
	void load_videodata(char *filename);
	void rgb_to_gray(uchar *img, uchar *gray) { for (long k = 0; k < pixels; k++)	gray[k] = (uchar) ((img[3 * k] + img[3 * k + 1] + img[3 * k + 2]+1)/3); }
	void gray_to_rgb(uchar *gray,uchar *img ) { for (long k = 0; k < pixels; k++)	img[3 * k] = img[3 * k + 1] = img[3 * k + 2] = gray[k];}
};


#endif

