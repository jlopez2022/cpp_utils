#ifndef  __OPENCL_FUNCTIONS
#define __OPENCL_FUNCTIONS
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

#include <CL/opencl.h>
#include <stdarg.h>  //va_start va_end
#define __CL_ENABLE_EXCEPTIONS
#define DEVICE_TYPE_1 CL_DEVICE_TYPE_GPU
//#define LOCAL_SIZE 256

#ifdef __linux__ 
//linux code goes here
#pragma GCC diagnostic ignored "-Wwrite-strings"
#else _WIN32
// windows code goes here
#pragma warning(disable:4996)
#endif

//This is the class used to attach algorithms to the gpu. It loads the kernel and function and makes all the opencl operations
class c_parallel 
{
public:
	//Constructor
	c_parallel(){init0();}
	void test(){ check_platform(); init0();}//solo para chequear GPU

	//Test functions:
	void PerformCalculationOnDevice1(void);
	void check_platform(void);

	~c_parallel() 
	{
		for (int i=0;i<num_kernels;i++)
		{
			clReleaseKernel(kernel[i]);
		}
		if (num_kernels)
		{
			clReleaseCommandQueue(queue);
			clReleaseContext(context);
			delete[] kernel;
		}
	}
protected:
	//2.2.================= opencl constants ==================
	int LOCAL_SIZE = 256;

	void init_gpu(int platform_number1, int device_number1, char *kernel_filename, char **kernel_function_name, int functions);
	//OpenCL main variables and constants:
	cl_device_id device;
	cl_context context;
	cl_command_queue queue;
	cl_kernel *kernel;
	int num_kernels;

	void checkerror1(int errornum, char *texto) { if (errornum) { cout << texto << endl; avisa_error_nonstop(errornum); getchar(); getchar(); } }

private:
	void init0(){kernel=nullptr;queue=nullptr;context=nullptr;device=NULL;context=NULL;queue=NULL;kernel=NULL;num_kernels=0;}

	//Error detection functions:
	void avisa_error(int error_num1);
	void checkerror2(int errornum, char *texto) { checkError(errornum, texto); getchar(); getchar(); }
	void checkerror2_nonstop(int errornum, char *texto) { checkError(errornum, texto); }
	void avisa_error_nonstop(int error_num1);
	//Como avisa_error pero admite texto y entrega linea y fichero del cpp donde se produjo el error
	void checkError(int status, char *text) { _checkError(__LINE__, __FILE__, status, text); }
	//Funcion esclava de la anterior
	void _checkError(int line, const char *file, cl_int error, const char *msg, ...); // does not return


	const int MAX_SOURCE_SIZE = 0x100000;
	//int DEVICE_TYPE1 = CL_DEVICE_TYPE_DEFAULT;

	//================ opencl errors ======================
	static const char error_flag[60][256];
	static const char error_text[60][1024];
	static const int error_num[60];
};
//================= opencl functions =================




#endif
