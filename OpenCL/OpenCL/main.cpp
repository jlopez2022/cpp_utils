#include "main.hpp"



int main()
{
#ifndef __linux__   //Introduce this code at the beginning of main() to increase a lot the speed of cout in windows: 
	char buf[4000]; setvbuf(stdout, buf, _IOFBF, sizeof buf);
#endif

	char funciones0[2][300]={"hallamedia","hallaRMS"},*funciones[2]={funciones0[0],funciones0[1]};
	c_clase clase1(0,0,"kernel.c",funciones,2);
	clase1.init_rms(200000000);//200 megas
	double rms;
	rms=clase1.function_rms_cpu();
	cout << "CPU RMS calculation=" << rms<<endl;
	rms=clase1.function_rms_gpu();
	cout << "GPU RMS calculation=" << rms<<endl;
	cout<<endl<<"=== FIN ==="<<endl;getchar();
	return 1;
}

void c_clase::init_rms(int size1)
{
	data=new float[size1];
	data_size=size1;
	start=clock();
	for (int i=0;i<size1;i++)
		data[i]=100.0f+1.0f*rand()/RAND_MAX;
	timer("c_clase::init_rms(): ");
}

//Add this command to the beginning of the function to be measured: start=clock();
void c_clase::timer(char *title)
{
	stop=clock();
	cout<<title<< " time ="<<(double) (stop-start)/(double) CLOCKS_PER_SEC<< " = " << 1e-6*data_size/( (double)(stop-start)/(double)CLOCKS_PER_SEC ) <<  " Mops/seg"   <<endl;
	start=clock();//it must be done better in the beginning of the function to be measured
}

double c_clase::function_rms_cpu()
{
	start=clock();
	double media=0.0;
	for (int i=0;i<data_size;i++)
	{
		media+=data[i];
	}
	media=media/(double) data_size;
	float x; double result=0.0;
	for (int i=0;i<data_size;i++)
	{
		x=data[i]-(float) media;
		result+=x*x;
	}
	result=sqrt(result/(double) data_size);
	timer("/nc_clase::function_rms_cpu() :");
	return result;
}

double c_clase::function_rms_gpu()
{
	//1.0 Calculates with and height
	int width,height;//width*height=data_size; height=2*width as long as CPU speed is double than GPU nucleous
	calculate_width_height(width,height);
	double *sumout=new double[height];
	size_t local_size = LOCAL_SIZE, global_size = height;

	start=clock(); 
	time_t start0=start;
	//2.0 data to gpu:
	cl_int status = 0;
	//data input to kernels (gpu reads only)
	cl_mem cl_data = clCreateBuffer(context, CL_MEM_READ_ONLY, data_size * sizeof(float), NULL, &status); checkerror1(status, "Failed to create buffer cl_data");//Read only
	status = clEnqueueWriteBuffer(queue, cl_data, CL_TRUE, 0, data_size * sizeof(float), (void *)data, 0, NULL, NULL); checkerror1(status, "Failed to enqueue write buffer cl_data");
	//data output from kernels (gpu writes only)
	cl_mem cl_sumout = clCreateBuffer(context, CL_MEM_WRITE_ONLY, height * sizeof(double), NULL, &status); checkerror1(status, "Failed to create buffer  cl_movex");//write only

	status |= clSetKernelArg(kernel[0], 0, sizeof(cl_mem), (void *)&cl_data);	checkerror1(status, "Failed to set kernel argument 0");
	status |= clSetKernelArg(kernel[0], 1, sizeof(int), (void *)&width );		checkerror1(status, "Failed to set kernel argument 1");
	status |= clSetKernelArg(kernel[0], 2, sizeof(int), (void *)&height);		checkerror1(status, "Failed to set kernel argument 2");
	status |= clSetKernelArg(kernel[0], 3, sizeof(cl_mem), (void *)&cl_sumout); checkerror1(status, "Failed to set kernel argument 3");
	clFinish(queue);
	//3.0 Execution kernel at GPU:
	status = clEnqueueNDRangeKernel(queue, kernel[0], 1, NULL, &global_size, &local_size, 0, NULL, NULL); checkerror1(status, "Failed to enqueue kernel-0!");
	clFinish(queue);
	//4.0. Data extraction:
	status = clEnqueueReadBuffer(queue, cl_sumout, CL_TRUE, 0, height * sizeof(double), (void *)sumout, 0, NULL, NULL); checkerror1(status, "Failed to read out data!");
	//timer("c_clase::function_rms_gpu() kernel 0 :");

	//calculates media:
	double media=0.0;
	for(int i=0;i<height;i++) media+=sumout[i];
	media=media/(double) data_size;
	cout<<"media="<<media<<endl;

	//calculates rms:
	start=clock();
	//2.0 data to gpu:
	status |= clSetKernelArg(kernel[1], 0, sizeof(cl_mem), (void *)&cl_data);	checkerror1(status, "Failed to set kernel argument 0");
	status |= clSetKernelArg(kernel[1], 1, sizeof(int), (void *)&width );		checkerror1(status, "Failed to set kernel argument 1");
	status |= clSetKernelArg(kernel[1], 2, sizeof(int), (void *)&height);		checkerror1(status, "Failed to set kernel argument 2");
	status |= clSetKernelArg(kernel[1], 3, sizeof(double), (void *)&media);		checkerror1(status, "Failed to set kernel argument 3");
	status |= clSetKernelArg(kernel[1], 4, sizeof(cl_mem), (void *)&cl_sumout); checkerror1(status, "Failed to set kernel argument 4");
	clFinish(queue);
	//3.0 Execution kernel at GPU:
	status = clEnqueueNDRangeKernel(queue, kernel[1], 1, NULL, &global_size, &local_size, 0, NULL, NULL); checkerror1(status, "Failed to enqueue kernel-1!");
	clFinish(queue);
	//4.0. Data extraction:
	status = clEnqueueReadBuffer(queue, cl_sumout, CL_TRUE, 0, height * sizeof(double), (void *)sumout, 0, NULL, NULL); checkerror1(status, "Failed to read out data!");
	double rms=0.0;
	for(int i=0;i<height;i++) rms+=sumout[i];
	rms=sqrt(rms/(double) data_size);
	//timer("c_clase::function_rms_gpu() kernel 1 :");

	start=start0;
	timer("/nGlobal c_clase::function_rms_gpu() timing :");

	delete[] sumout;

	return rms;
}

	//calculates width and height where width*height=data_size; height=2*width as long as CPU speed is double than GPU nucleous
	void c_clase::calculate_width_height(int &width,int &height)
	{
	int w0=(int) sqrt((double) data_size/3.0);
	int i;
	for (i=0;i<data_size/2;i++)
	{
		width=w0+i;
		if (data_size % width==0)
			break;
		width=w0-i;
		if (data_size % width==0)
			break;
	}
	if (i==data_size/2)
	{
		cout << "Warning at calculate_width_height(): width=1"<<endl;
		width=1;
	}
	height=data_size / width;
	if (height*width!=data_size)
	{
		cout << "ERROR at calculate_width_height(): data_size="<<data_size<<" != " <<" width*height= "<<width*height<<endl;
	}
	cout << "data_size="<<data_size<< " width="<<width<<" height="<<height<<endl;
}