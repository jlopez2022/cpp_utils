#include "main.hpp"


void c_parallel::avisa_error(int error_num1)
{
	int i;
	for (i = 0; i < 60; i++)
	{
		if (error_num[i] == error_num1)
			break;
	}
	if ((error_num1>0) || (error_num1 < -60))
		printf("ERROR desconocido = %i", error_num1);
	else if (i > -20)
		printf("ERROR de KERNEL de COMPILACION num=%i FLAG=%s %s\n", error_num1, error_flag[i], error_text[i]);
	else
		printf("ERROR de KERNEL de RUNTIME num=%i FLAG=%s %s\n", error_num1, error_flag[i], error_text[i]);
}

void c_parallel::avisa_error_nonstop(int error_num1)
{
	//checkError(error_num1, " ERROR de KERNEL de COMPILACION ");
	int i;
	for (i = 0; i < 60; i++)
	{
		if (error_num[i] == error_num1)
			break;
	}
	if ((error_num1>0) || (error_num1 < -60))
		printf("ERROR desconocido = %i", error_num1);
	else if (error_num1 > -20)
	{
		printf("ERROR de KERNEL de COMPILACION num=%i FLAG=%s %s\n", error_num1, error_flag[i], error_text[i]);
	}
	else
	{
		printf("ERROR de KERNEL de RUNTIME num=%i FLAG=%s %s\n", error_num1, error_flag[i], error_text[i]);
	}
}



// Print line, file name, and error code if there is an error. Exits the
// application upon error.
void c_parallel::_checkError(int line, const char *file, cl_int error, const char *msg, ...)
{
	// If not successful
	if (error != CL_SUCCESS)
	{
		// Print line and file
		printf("ERROR: ");
		avisa_error_nonstop(error);
		printf("\nLocation: %s:%d\n", file, line);

		// Print custom message.
		va_list vl;
		va_start(vl, msg);
		vprintf(msg, vl);
		printf("\n");
		va_end(vl);
	}
}



void c_parallel::check_platform(void)
{
	cl_uint nplatforms, status;
	cout << "clGetPlatformIDs():" << endl;
	status = clGetPlatformIDs(0, NULL, &nplatforms); if (nplatforms <= 0) { cout << "ERROR in c_parallel::c_parallel no GPUs. Exiting" << endl; getchar(); getchar(); exit(0); }
	cl_platform_id* platforms = new cl_platform_id[nplatforms];//FALTA el delete final!!!!!!!!!!!!!!!!!!!!!
	status = clGetPlatformIDs(nplatforms, platforms, NULL);	checkerror1(status, "ERROR in c_parallel::c_parallel clGetPlatformIDs-2 ");


	//cl_uint buf_uint;
	//cl_ulong buf_ulong;
	unsigned int iDevice, iPlatform;
	printf("Num of Platforms=%i \n", (int)nplatforms);
	for (iPlatform = 0; iPlatform < nplatforms; iPlatform++)
	{
		cl_uint ndevices;
		status = clGetDeviceIDs(platforms[iPlatform], DEVICE_TYPE_1, 0, NULL, &ndevices);	checkerror1(status, "ERROR in c_parallel::check_platform clGetDeviceIDs ");
		if (ndevices <= 0) { cout << "ERROR in c_parallel::c_parallel no opencl devices. Exiting" << endl; getchar(); getchar(); exit(0); }
		cl_device_id* devices = new cl_device_id[ndevices]; 
		cout << "clGetDeviceIDs():" << endl;
		status = clGetDeviceIDs(platforms[iPlatform], DEVICE_TYPE_1, 0, NULL, &ndevices);	checkerror1(status, "ERROR in c_parallel::check_platform clGetDeviceIDs ");
		if (ndevices <= 0) { cout << "ERROR in c_parallel::c_parallel no opencl devices. Exiting" << endl; getchar(); getchar(); exit(0); }
		delete devices;
		devices = new cl_device_id[ndevices]; 
		status = clGetDeviceIDs(platforms[iPlatform], DEVICE_TYPE_1, ndevices, devices, NULL);	checkerror1(status, "ERROR in c_parallel::check_platform clGetDeviceIDs-2 ");


		printf("============ INIT OF PLATFORM NUMBER %i ===============\n", iPlatform);
		printf("Num of devices: %i \n", (int)ndevices);
		for (iDevice = 0; iDevice < ndevices; iDevice++)
		{   //VER: https://www.khronos.org/registry/cl/sdk/1.0/docs/man/xhtml/clGetDeviceInfo.html
			printf("\t============ INIT OF DEVICE NUMBER %i ===============\n", iDevice);

			device = devices[iDevice];
			char buffer[1024];
			cout << "clGetDeviceInfo:" << endl;
			status = clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(buffer), buffer, NULL); checkerror1(status, "ERROR in c_parallel::check_platform CL_DEVICE_NAME ");
			printf("\tDEVICE_NAME = %s\n", buffer);
			status = clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof(buffer), buffer, NULL); checkerror1(status, "ERROR in c_parallel::check_platform CL_DEVICE_VENDOR ");
			printf("\tDEVICE_VENDOR = %s\n", buffer);
			status = clGetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(buffer), buffer, NULL); checkerror1(status, "ERROR in c_parallel::check_platform CL_DEVICE_TYPE ");

			printf("\tDEVICE_TYPE = ");
			if (buffer[0] & CL_DEVICE_TYPE_CPU) printf(" CPU");
			if (buffer[0] & CL_DEVICE_TYPE_GPU) printf(" GPU");
			if (buffer[0] & CL_DEVICE_TYPE_ACCELERATOR) printf(" ACCELERATOR");
			if (buffer[0] & CL_DEVICE_TYPE_DEFAULT) printf(" DEFAULT DEVICE");
			printf("\n");

			cl_uint buf_uint;
			cl_ulong buf_ulong;
			status = clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(buf_uint), &buf_uint, NULL); checkerror1(status, "ERROR in c_parallel::check_platform CL_DEVICE_MAX_COMPUTE_UNITS ");
			printf("  DEVICE_MAX_COMPUTE_UNITS = %u\n", (unsigned int)buf_uint);
			status = clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(buf_uint), &buf_uint, NULL); checkerror1(status, "ERROR in c_parallel::check_platform CL_DEVICE_MAX_CLOCK_FREQUENCY ");
			printf("  DEVICE_MAX_CLOCK_FREQUENCY = %u\n", (unsigned int)buf_uint);
			status = clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(buf_ulong), &buf_ulong, NULL); checkerror1(status, "ERROR in c_parallel::check_platform CL_DEVICE_GLOBAL_MEM_SIZE ");
			printf("  DEVICE_GLOBAL_MEM_SIZE = %llu\n", (unsigned long long)buf_ulong);
			printf("\t============ END  OF DEVICE NUMBER %i ===============\n", iDevice);
		}
		delete devices;
		printf("============ END  OF PLATFORM NUMBER %i ===============\n", iPlatform);
	}//iPlatform
	delete platforms;
	cout<<"============ END  OF check_platform() ===============\n";
}



void c_parallel::init_gpu(int platform_number1, int device_number1, char *kernel_filename, char **kernel_function_name,int num_kernels1)
{
	init0();
	num_kernels=num_kernels1;
	kernel=new cl_kernel[num_kernels1]; 

	int status = -999;
	cl_program program;
	try
	{
		//cl_platform_id platform_id = NULL;
		cl_uint nplatforms;
		cout << "clGetPlatformIDs():" << endl;
		status = clGetPlatformIDs(0, NULL, &nplatforms); if (nplatforms <= 0) { cout << "ERROR in c_parallel::c_parallel no GPUs. Exiting" << endl; getchar(); getchar(); exit(0); }
		cl_platform_id* platforms = new cl_platform_id[nplatforms];//FALTA el delete final!!!!!!!!!!!!!!!!!!!!!
		status = clGetPlatformIDs(nplatforms, platforms, NULL);	checkerror1(status, "ERROR in c_parallel::c_parallel clGetPlatformIDs-2 ");

		cout << "clGetDeviceIDs():" << endl;
		cl_uint ndevices;
		cl_device_id* devices;
		status = clGetDeviceIDs(platforms[platform_number1], DEVICE_TYPE_1, 0, NULL, &ndevices);	checkerror1(status, "ERROR in c_parallel::c_parallel clGetDeviceIDs ");
		if (ndevices <= 0) { cout << "ERROR in c_parallel::c_parallel no opencl devices. Exiting" << endl; getchar(); getchar(); exit(0); }
		devices = new cl_device_id[ndevices]; //FALTA el delete final!!!!!!!!!!!!!!!!!!!!!
		status = clGetDeviceIDs(platforms[platform_number1], DEVICE_TYPE_1, ndevices, devices, NULL);	checkerror1(status, "ERROR in c_parallel::c_parallel clGetDeviceIDs-2 ");

		device = devices[device_number1];
		char buffer[1024];
		cout << "clGetDeviceInfo:" << endl;
		status = clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(buffer), buffer, NULL);
		//		if (!(buffer[0] & CL_DEVICE_TYPE_GPU)) 		{ 			cout << "ERROR en c_parallel::c_parallel clGetDeviceInfo: no es una GPU!!!!!!!!!!!!!!! salirse del programa" << endl; 			checkerror1(status, ""); 		}
		context = clCreateContext(0, 1, &device, NULL, NULL, &status); checkerror1(status, "ERROR en c_parallel::c_parallel   clCreateContext()");

		// Create a command queue  
#ifdef CL_USE_DEPRECATED_OPENCL_1_2_APIS
		queue = clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, &status); checkerror1(status, "ERROR en c_parallel::c_parallel   clCreateCommandQueue()");
#else
		cl_command_queue_properties *propers;
		cl_command_queue_properties prop = 0;  //prop |= CL_QUEUE_PROFILING_ENABLE; //prop |= CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE;
		propers = &prop;
		queue = clCreateCommandQueueWithProperties(context, device, propers, &status); checkerror1(status, "ERROR en c_parallel::c_parallel   clCreateCommandQueue()");
		checkerror1(status, " ERROR at c_parallel::init_gpu()   clCreateCommandQueueWithProperties() ");
		if (!queue) 
		{
		  cout<<"FATAL ERROR at c_parallel::init_gpu() Cannot create OpenCL command cue: NULL\n";getchar();
		}
#endif

		size_t length;
		FILE *kernelFile = fopen(kernel_filename, "r");
		if (!kernelFile)
		{
			cout << "ERROR: canot open " << kernel_filename << endl; getchar(); getchar(); exit(0);
		}
		char *source = new char[MAX_SOURCE_SIZE];
		length = fread(source, 1, MAX_SOURCE_SIZE, kernelFile);
		fclose(kernelFile);
		cout << "Kernel filename=" << kernel_filename << " length=" << length << endl;

		program = clCreateProgramWithSource(context, 1, (const char **)&source, (const size_t *)&length, &status);
		checkerror1(status, "ERROR en c_parallel::init_gpu() clCreateProgramWithSource() Failed to create program with source!");
		delete source;//no borrar


		status = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
		if (status == CL_BUILD_PROGRAM_FAILURE)
		{
			char *log;
			size_t logLength;
			status = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logLength);
			log = (char *)malloc(sizeof(char)*logLength); log[0] = 0;
			status = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, logLength, log, NULL);
			fprintf(stderr, "Kernel build error! Log:\n%s", log);
			getchar(); getchar(); free(log); exit(0);
		}
		checkerror1(status, "Failed to build program!");

		for (int i=0;i<num_kernels;i++)
		{
			cout <<"Create kernel with function "<<kernel_function_name[i]<<endl;
			kernel[i] = clCreateKernel(program, kernel_function_name[i], &status);
			char s[1024];sprintf(s,"Failed to create kernel num %i function: %s",i,kernel_function_name[i]);
			checkerror1(status,s );
		}
	}
	catch (int error)
	{
		//std::cout << "ERROR PerformCalculationOnDevice:" << error.what() << "(" << error.err() << ")" << " ver:https://streamcomputing.eu/blog/2013-04-28/opencl-1-2-error-codes/" << std::endl;
		cout << "ERROR en c_parallel::init_gpu(): " << endl;
		checkerror2_nonstop(status, "ERROR en c_parallel::c_parallel() try catch");
		checkerror2_nonstop(error, "ERROR en c_parallel::c_parallel() try catch");
		getchar(); getchar(); exit(0);
	}
	clReleaseProgram(program);
}





//================ opencl errors ======================
const char c_parallel::error_flag[60][256] = { "CL_SUCCESS", "CL_DEVICE_NOT_FOUND", "CL_DEVICE_NOT_AVAILABLE", "CL_COMPILER_NOT_AVAILABLE", "CL_MEM_OBJECT_ALLOCATION_FAILURE", "CL_OUT_OF_RESOURCES", "CL_OUT_OF_HOST_MEMORY",
"CL_PROFILING_INFO_NOT_AVAILABLE", "CL_MEM_COPY_OVERLAP", "CL_IMAGE_FORMAT_MISMATCH", "CL_IMAGE_FORMAT_NOT_SUPPORTED", "CL_BUILD_PROGRAM_FAILURE", "CL_MAP_FAILURE",
"CL_MISALIGNED_SUB_BUFFER_OFFSET", "CL_EXEC_STATUS_ERROR_ FOR_EVENTS_IN_WAIT_LIST", "CL_COMPILE_PROGRAM_FAILURE", "CL_LINKER_NOT_AVAILABLE", "CL_LINK_PROGRAM_FAILURE",
"CL_DEVICE_PARTITION_FAILED", "CL_KERNEL_ARG_INFO_NOT_AVAILABLE", "CL_INVALID_VALUE", "CL_INVALID_DEVICE_TYPE", "CL_INVALID_PLATFORM", "CL_INVALID_DEVICE", "CL_INVALID_CONTEXT",
"CL_INVALID_QUEUE_PROPERTIES", "CL_INVALID_COMMAND_QUEUE", "CL_INVALID_HOST_PTR", "CL_INVALID_MEM_OBJECT", "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR", "CL_INVALID_IMAGE_SIZE", "CL_INVALID_SAMPLER",
"CL_INVALID_BINARY", "CL_INVALID_BUILD_OPTIONS", "CL_INVALID_PROGRAM", "CL_INVALID_PROGRAM_EXECUTABLE", "CL_INVALID_KERNEL_NAME", "CL_INVALID_KERNEL_DEFINITION", "CL_INVALID_KERNEL",
"CL_INVALID_ARG_INDEX", "CL_INVALID_ARG_VALUE", "CL_INVALID_ARG_SIZE", "CL_INVALID_KERNEL_ARGS", "CL_INVALID_WORK_DIMENSION", "CL_INVALID_WORK_GROUP_SIZE", "CL_INVALID_WORK_ITEM_SIZE",
"CL_INVALID_GLOBAL_OFFSET", "CL_INVALID_EVENT_WAIT_LIST", "CL_INVALID_EVENT", "CL_INVALID_OPERATION", "CL_INVALID_GL_OBJECT", "CL_INVALID_BUFFER_SIZE", "CL_INVALID_MIP_LEVEL",
"CL_INVALID_GLOBAL_WORK_SIZE", "CL_INVALID_PROPERTY", "CL_INVALID_IMAGE_DESCRIPTOR", "CL_INVALID_COMPILER_OPTIONS", "CL_INVALID_LINKER_OPTIONS", "CL_INVALID_DEVICE_PARTITION_COUNT" };

const char c_parallel::error_text[60][1024] = { "OK!!!!", "if no OpenCL devices that matched device_type were found.", "if a device in devices is currently not available even though the device was returned by clGetDeviceIDs.", "if program is created with clCreateProgramWithSource and a compiler is not available i.e.CL_DEVICE_COMPILER_AVAILABLE specified in the table of OpenCL Device Queries for clGetDeviceInfo is set to CL_FALSE.", "if there is a failure to allocate memory for buffer object.", "if there is a failure to allocate resources required by the OpenCL implementation on the device.", "if there is a failure to allocate resources required by the OpenCL implementation on the host.", "if the CL_QUEUE_PROFILING_ENABLE flag is not set for the command - queue, if the execution status of the command identified by event is not CL_COMPLETE or if event is a user event object.", "if src_buffer and dst_buffer are the same buffer or subbuffer object and the source and destination regions overlap or if src_buffer and dst_buffer are different sub - buffers of the same associated buffer object and they overlap.The regions overlap if src_offset ? to dst_offset ? to src_offset + size – 1, or if dst_offset ? to src_offset ? to dst_offset + size – 1.", "if src_image and dst_image do not use the same image format.", "if the image_format is not supported.", "if there is a failure to build the program executable.This error will be returned if clBuildProgram does not return until the build has completed.", " if there is a failure to map the requested region into the host address space.This error cannot occur for image objects created with CL_MEM_USE_HOST_PTR or CL_MEM_ALLOC_HOST_PTR.", "if a sub - buffer object is specified as the value for an argument that is a buffer object and the offset specified when the sub - buffer object is created is not aligned to CL_DEVICE_MEM_BASE_ADDR_ALIGN value for device associated with queue.", "if the execution status of any of the events in event_list is a negative integer value.", "if there is a failure to compile the program source.This error will be returned if clCompileProgram does not return until the compile has completed.", "if a linker is not available i.e.CL_DEVICE_LINKER_AVAILABLE specified in the table of allowed values for param_name for clGetDeviceInfo is set to CL_FALSE.", "if there is a failure to link the compiled binaries and / or libraries.", " if the partition name is supported by the implementation but in_device could not be further partitioned.", "if the argument information is not available for kernel", "This depends on the function : two or more coupled parameters had errors.", "if an invalid device_type is given", "if an invalid platform was given", "if devices contains an invalid device or are not associated with the specified platform.", "if context is not a valid context.", "if specified command - queue - properties are valid but are not supported by the device.", "if command_queue is not a valid command - queue.", "This flag is valid only if host_ptr is not NULL.If specified, it indicates that the application wants the OpenCL implementation to allocate memory for the memory object and copy the data from memory referenced by host_ptr.CL_MEM_COPY_HOST_PTR and CL_MEM_USE_HOST_PTR are mutually exclusive.CL_MEM_COPY_HOST_PTR can be used with CL_MEM_ALLOC_HOST_PTR to initialize the contents of the cl_mem object allocated using host - accessible(e.g.PCIe) memory.", "if memobj is not a valid OpenCL memory object.", "if the OpenGL / DirectX texture internal format does not map to a supported OpenCL image format.", "if an image object is specified as an argument value and the image dimensions(image width, height, specified or compute row and / or slice pitch) are not supported by device associated with queue.", "if sampler is not a valid sampler object.", "The provided binary is unfit for the selected device.", "if program is created with clCreateProgramWithBinary and devices listed in device_list do not have a valid program binary loaded.", "if the build options specified by options are invalid.", "if program is a not a valid program object.", "if there is no successfully built program executable available for device associated with command_queue.", "if kernel_name is not found in program.", "if the function definition for __kernel function given by kernel_name such as the number of arguments, the argument types are not the same for all devices for which the program executable has been built.", "if kernel is not a valid kernel object.", "if arg_index is not a valid argument index.", "if arg_value specified is not a valid value.", "if arg_size does not match the size of the data type for an argument that is not a memory object or if the argument is a memory object and arg_size != sizeof(cl_mem) or if arg_size is zero and the argument is declared with the __local qualifier or if the argument is a sampler and arg_size != sizeof(cl_sampler).", "if the kernel argument values have not been specified.", "if work_dim is not a valid value(i.e.a value between 1 and 3).", "if local_work_size is specified and number of work - items specified by global_work_size is not evenly divisable by size of work - group given by local_work_size or does not match the work - group size specified for kernel using the __attribute__((reqd_work_group_size(X, Y, Z))) qualifier in program source.if local_work_size is specified and the total number of work - items in the work - group computed as local_work_size[0] * … local_work_size[work_dim – 1] is greater than the value specified by CL_DEVICE_MAX_WORK_GROUP_SIZE in the table of OpenCL Device Queries for clGetDeviceInfo.if local_work_size is NULL and the __attribute__((reqd_work_group_size(X, Y, Z))) qualifier is used to declare the work - group size for kernel in the program source.", "if the number of work - items specified in any of local_work_size[0], … local_work_size[work_dim – 1] is greater than the corresponding values specified by CL_DEVICE_MAX_WORK_ITEM_SIZES[0], ….CL_DEVICE_MAX_WORK_ITEM_SIZES[work_dim – 1].", "if the value specified in global_work_size + the corresponding values in global_work_offset for any dimensions is greater than the sizeof(size_t) for the device on which the kernel execution will be enqueued.", "if event_wait_list is NULL and num_events_in_wait_list > 0, or event_wait_list is not NULL and num_events_in_wait_list is 0, or if event objects in event_wait_list are not valid events.", "if event objects specified in event_list are not valid event objects.", "if interoperability is specified by setting CL_CONTEXT_ADAPTER_D3D9_KHR, CL_CONTEXT_ADAPTER_D3D9EX_KHR or CL_CONTEXT_ADAPTER_DXVA_KHR to a non - NULL value, and interoperability with another graphics API is also specified. (only if the cl_khr_dx9_media_sharing extension is supported).", "if texture is not a GL texture object whose type matches texture_target, if the specified miplevel of texture is not defined, or if the width or height of the specified miplevel is zero.", "if size is 0.Implementations may return CL_INVALID_BUFFER_SIZE if size is greater than the CL_DEVICE_MAX_MEM_ALLOC_SIZE value specified in the table of allowed values for param_name for clGetDeviceInfo for all devices in context.", "if miplevel is greater than zero and the OpenGL implementation does not support creating from non - zero mipmap levels.", "if global_work_size is NULL, or if any of the values specified in global_work_size[0], …global_work_size[work_dim – 1] are 0 or exceed the range given by the sizeof(size_t) for the device on which the kernel execution will be enqueued.", "Vague error, depends on the function", "if values specified in image_desc are not valid or if image_desc is NULL.", "if the compiler options specified by options are invalid.", "if the linker options specified by options are invalid.", "if the partition name specified in properties is CL_DEVICE_PARTITION_BY_COUNTS and the number of sub - devices requested exceeds CL_DEVICE_PARTITION_MAX_SUB_DEVICES or the total number of compute units requested exceeds CL_DEVICE_PARTITION_MAX_COMPUTE_UNITS for in_device, or the number of compute units requested for one or more sub - devices is less than zero or the number of sub - devices requested exceeds CL_DEVICE_PARTITION_MAX_COMPUTE_UNITS for in_device" };

const int c_parallel::error_num[60] = { 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16, -17, -18, -19, -30,
-31, -32, -33, -34, -35, -36, -37, -38, -39, -40, -41, -42, -43, -44, -45, -46, -47, -48, -49,
-50, -51, -52, -53, -54, -55, -56, -57, -58, -59, -60, -61, -62, -63, -64, -65, -66, -67, -68 };
