#include "main.hpp"

#define COMPRESSED2 //COMPRESSED1 or COMPRESSED2 uses compressed output algorithm. Comment the line to use UNCOMPRESSED algorithm

#ifdef COMPRESSED1
	#define SIZEOUT num_groups   
	#define KERNELNAME "algoritmo_KNP_COMPRESSED1"
	#define NUMOUT num_groups
#else
	#ifdef COMPRESSED2
	#define SIZEOUT num_groups   
	#define KERNELNAME "algoritmo_KNP_COMPRESSED2"
	#define NUMOUT num_groups
	#define KERNELNAME_BDP "algoritmo_BDP_COMPRESSED2"
	#else
		#define UNCOMPRESSED
		#define SIZEOUT pixels
		#define KERNELNAME "algoritmo_KNP_UNCOMPRESSED"
		#define NUMOUT ymax
	#define KERNELNAME_BDP "algoritmo_BDP_UNCOMPRESSED"
	#endif
#endif



int main()
{
#ifndef __linux__   //Introduce this code at the beginning of main() to increase a lot the speed of cout in windows: 
	char buf[4000]; setvbuf(stdout, buf, _IOFBF, sizeof buf);
#endif

	{	// === BCP ===
		char funciones0[2][300]={KERNELNAME_BDP,""},*funciones[2]={funciones0[0],funciones0[1]};
		c_clase clase1(0,0,"Algoritmo_BDP.cl",funciones,1);
		clase1.funcion_BDP_gpu();
		cout<<endl<<"===== END BDP ====="<<endl<<endl;getchar();
	}

	{	// === KNP ===
		char funciones0[2][300]={KERNELNAME,""},*funciones[2]={funciones0[0],funciones0[1]};
		c_clase clase1(0,0,"Algoritmo_KNP.cl",funciones,1);
		clase1.funcion_KNP_gpu();
		cout<<endl<<"===== END KNP ====="<<endl<<endl;getchar();
	}



	return 1;
}


//Add this command to the beginning of the function to be measured: start=clock();
void c_clase::timer(char *title)
{
	stop=clock();
	cout<<title<< " time ="<<(double) (stop-start)/(double) CLOCKS_PER_SEC<< " = " << 1e-6*data_size/( (double)(stop-start)/(double)CLOCKS_PER_SEC ) <<  " Mops/seg"   <<endl;
	start=clock();//it must be done better in the beginning of the function to be measured
}

//if move1,2,count1,2 are compressed SIZEOUT=ymax else SIZEOUT=pixelsalgoritmo_KNP_UNCOMPRESSED
  
//#define SIZEOUT pixels

void c_clase::funcion_KNP_gpu()
{
	size_t local_size = max_local_size, global_size =pixels;
	long num_groups=xmax*ymax/(long) max_local_size; //to be used by compressed-1
	cout << "num_groups="<<num_groups<<endl;

	//1. Initialization:
	start=clock();
	cl_mem cl_move1,cl_move2,cl_count1,cl_count2, cl_im1,cl_im2, cl_imageout;
	cl_int status=0;
	try
	{

		//status = clSetKernelArg(kernel[0], 0, sizeof(cl_mem), (void *)&cl_gpuvideo[gpunum]); checkerror1(status, "Failed to set kernel argument 0");
		//Initialization:
		size_t size;
		size=pixels*sizeof(uchar);
		cl_im1 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_im1");
		status = clSetKernelArg(*kernel, 0, sizeof(cl_mem), (void *)&cl_im1); checkerror1(status, "Failed to set kernel argument 0");

		size= xmax*ymax*sizeof(float);
		cl_mem cl_coefx = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_coefx[]");
		// NOT NEEDED: status = clEnqueueWriteBuffer(queue, cl_coefx, CL_TRUE, 0, size, (void *)videobuffer->processing[videoindex]->coefx, 0, NULL, NULL); checkerror1(status, "Failed to enqueue write buffer cl_coefx[]");
		status = clSetKernelArg(*kernel, 1, sizeof(cl_mem), (void *)&cl_coefx); checkerror1(status, "Failed to set kernel argument 1");
		cl_mem cl_coefy = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_coefy[]");
		status = clEnqueueWriteBuffer(queue, cl_coefy, CL_TRUE, 0, size, (void *)coefy, 0, NULL, NULL); checkerror1(status, "Failed to enqueue write buffer cl_coefy[]");
		status = clSetKernelArg(*kernel, 2, sizeof(cl_mem), (void *)&cl_coefy); checkerror1(status, "Failed to set kernel argument 2");

		size = 3 * xmax*ymax* sizeof(uchar);
		cl_imageout = clCreateBuffer(context, CL_MEM_READ_ONLY, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_imageout");
		status = clSetKernelArg(*kernel, 3, sizeof(cl_mem), (void *)&cl_imageout); checkerror1(status, "Failed to set kernel argument 3");

		size = xmax*ymax* sizeof(float);
		cl_mem cl_move = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_move");
		status = clSetKernelArg(*kernel, 4, sizeof(cl_mem), (void *)&cl_move); checkerror1(status, "Failed to set kernel argument 4");


		size = SIZEOUT* sizeof(float);//CAUTION *xmax para pruebas!!!!!!!!!!!!
		cl_move1 = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_move1");
		status = clSetKernelArg(*kernel, 5, sizeof(cl_mem), (void *)&cl_move1); checkerror1(status, "Failed to set kernel argument 5");
		cl_move2 = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_move2");
		status = clSetKernelArg(*kernel, 6, sizeof(cl_mem), (void *)&cl_move2); checkerror1(status, "Failed to set kernel argument 6");

		size = SIZEOUT* sizeof(int);  //CAUTION *xmax para pruebas!!!!!!!!!!!!
		//Changed from CL_MEM_READ_ONLY to CL_MEM_READ_WRITE to allow put to zero!!!!
		cl_count1 = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_count1");
		status = clSetKernelArg(*kernel, 7, sizeof(cl_mem), (void *)&cl_count1); checkerror1(status, "Failed to set kernel argument 7");
		cl_count2 = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_count2");
		status = clSetKernelArg(*kernel, 8, sizeof(cl_mem), (void *)&cl_count2); checkerror1(status, "Failed to set kernel argument 8");

		status = clSetKernelArg(*kernel, 9, sizeof(int), (void *)&xmax); checkerror1(status, "Failed to set kernel argument 9");
		status = clSetKernelArg(*kernel, 10, sizeof(int), (void *)&ymax); checkerror1(status, "Failed to set kernel argument 10");


		status = clSetKernelArg(*kernel, 11, sizeof(int), (void *)&WINDOW_SIZE); checkerror1(status, "Failed to set kernel argument 11");
		status = clSetKernelArg(*kernel, 12, sizeof(int), (void *)&xmed); checkerror1(status, "Failed to set kernel argument 12");

		//int framebuffersize = -777;
		//status = clSetKernelArg(*kernel, 13, sizeof(int), (void *)&framebuffersize); checkerror1(status, "Failed to set kernel argument 13");

		size=pixels*sizeof(uchar);
		cl_im2 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_im2");
		status = clSetKernelArg(*kernel, 13, sizeof(cl_mem), (void *)&cl_im2); checkerror1(status, "Failed to set kernel argument 13");

#ifdef COMPRESSED2
		status = clSetKernelArg(*kernel, 14, max_local_size*sizeof(float), NULL); checkerror1(status, "Failed to set kernel argument 14 lmov1");
		status = clSetKernelArg(*kernel, 15, max_local_size*sizeof(float), NULL); checkerror1(status, "Failed to set kernel argument 15 lmov2");
		status = clSetKernelArg(*kernel, 16, max_local_size*sizeof(int  ), NULL); checkerror1(status, "Failed to set kernel argument 16 lcount1");
		status = clSetKernelArg(*kernel, 17, max_local_size*sizeof(int  ), NULL); checkerror1(status, "Failed to set kernel argument 17 lcount2");
#endif
	}
	catch (int error)
	{
		//std::cout << "ERROR PerformCalculationOnDevice:" << error.what() << "(" << error.err() << ")" << " ver:https://streamcomputing.eu/blog/2013-04-28/opencl-1-2-error-codes/" << std::endl;
		cout << "ERROR en c_clase::funcion_KNP_gpu(): " << endl;
		checkerror2_nonstop(status, "ERROR at c_clase::funcion_KNP_gpu() initialization try catch");
		checkerror2_nonstop(error, "ERROR at c_clase::funcion_KNP_gpu() initialization try catch");
		getchar(); getchar(); exit(0);
	}
	timer("\n c_clase::funcion_KNP_gpu() initialization timing :");

	//2. Usage: introduces image1 & 2 and then executes and extract data from kernel
	float *move1=new float[SIZEOUT];
	float *move2=new float[SIZEOUT];
	int *count1=new int[SIZEOUT];
	int *count2=new int[SIZEOUT];
	uchar *out=new uchar[3*pixels];

	start=clock();
	try
	{
		status = clEnqueueWriteBuffer(queue, cl_im1, CL_TRUE, 0, pixels * sizeof(uchar), (void *)gray1, 0, NULL, NULL); checkerror1(status, "Failed to enqueue write buffer cl_im1");
		status = clEnqueueWriteBuffer(queue, cl_im2, CL_TRUE, 0, pixels * sizeof(uchar), (void *)gray2, 0, NULL, NULL); checkerror1(status, "Failed to enqueue write buffer cl_im2");
		clFinish(queue);

		//RUN gpu
		status = clEnqueueNDRangeKernel(queue, *kernel, 1, NULL, &global_size, &local_size, 0, NULL, NULL); checkerror1(status, "Failed to enqueue kernel!");
		clFinish(queue);
		//Data extraction:
		status = clEnqueueReadBuffer(queue, cl_imageout, CL_TRUE, 0, 3 * pixels * sizeof(uchar), (void *)out, 0, NULL, NULL); checkerror1(status, "Failed to read out data!");
		status = clEnqueueReadBuffer(queue, cl_move1, CL_TRUE, 0, SIZEOUT * sizeof(float), (void *)move1, 0, NULL, NULL); checkerror1(status, "Failed to read cl_move1 data!");
		status = clEnqueueReadBuffer(queue, cl_move2, CL_TRUE, 0, SIZEOUT * sizeof(float), (void *)move2, 0, NULL, NULL); checkerror1(status, "Failed to read cl_move2 data!");
		status = clEnqueueReadBuffer(queue, cl_count1, CL_TRUE, 0, SIZEOUT * sizeof(int), (void *)count1, 0, NULL, NULL); checkerror1(status, "Failed to read count1 data!");
		status = clEnqueueReadBuffer(queue, cl_count2, CL_TRUE, 0, SIZEOUT * sizeof(int), (void *)count2, 0, NULL, NULL); checkerror1(status, "Failed to read count2 data!");
		clFinish(queue);
	}
	catch (int error)
	{
		//std::cout << "ERROR PerformCalculationOnDevice:" << error.what() << "(" << error.err() << ")" << " ver:https://streamcomputing.eu/blog/2013-04-28/opencl-1-2-error-codes/" << std::endl;
		cout << "ERROR en c_clase::funcion_KNP_gpu() usage: " << endl;
		checkerror2_nonstop(status, "ERROR at c_clase::funcion_KNP_gpu() usage try catch");
		checkerror2_nonstop(error, "ERROR at c_clase::funcion_KNP_gpu() usage try catch");
		getchar(); getchar(); exit(0);
	}
	timer("\n c_clase::funcion_KNP_gpu() usage :");
	save_image_ppm("out.ppm",out,xmax,ymax);

#ifdef UNCOMPRESSED
	{
		for (int y=0;y<ymax;y++)
		{
			float f=0.0f;int sum=0;
			int x;
			for(x=0;x<xmed;x++)
			{
				f+=move1[y*xmax+x];
				sum+=count1[y*xmax+x];
			}
			move1[y]=f;count1[y]=sum;
			f=0.0f;sum=0;
			for(;x<xmax;x++)
			{
				f+=move2[y*xmax+x];
				sum+=count2[y*xmax+x];
			}
			move2[y]=f;count2[y]=sum;
		}
	}
#endif

	double summove1 = 0.0, summove2 = 0.0, sumcount1 = 0.0, sumcount2 = 0.0;
	{	//data results
		for (int i = 0; i < NUMOUT; i++)  //NUMPOUT==ymax if uncompressed 
		{
			summove1 += move1[i];
			summove2 += move2[i];
			sumcount1 += count1[i];
			sumcount2 += count2[i];
		}	
		const double coef_speed = 30.0*3.6*4.0; //passes movement in meters in a frame to km/h. =30frames/second*3600seconds/1000m in a km. Passes to km/hour
		if (sumcount1 > 0) summove1 = 1.0*summove1 / sumcount1*coef_speed; else summove1 = 0.0;
		if (sumcount2 > 0) summove2 = 1.0*summove2 / sumcount2*coef_speed; else summove2 = 0.0;
		printf("  summove1=%lg summove2=%lg\n sumcount1=%lg sumcount2=%lg\n",summove1,summove2,sumcount1,sumcount2);
	}

	{	//check results!

			cout<<endl<<endl<<"======= CHECK RESULTS INI ======= "<<endl;
			if (fabs(summove1-118.55837f)<0.01f)
				cout<<"Sumove1   test = OK  ";
			else
				cout<<"Sumove1   test = FAIL";
			cout<<"    DIFF="<<summove1-118.55837f<<endl;

			if (fabs(summove2 - -67.516002f)<0.01f)
				cout<<"Sumove2   test = OK  ";
			else
				cout<<"Sumove2   test = FAIL";
			cout<<"    DIFF="<<summove2 - -67.516002f<<endl;

			if (fabs(sumcount1-69861)<0.9f)
				cout<<"sumcount1 test = OK  ";
			else
				cout<<"sumcount1 test = FAIL";
			cout<<"    DIFF="<<sumcount1-69861 <<endl;

			if (fabs(sumcount2-43604)<0.9f)
				cout<<"sumcount2 test = OK  ";
			else
				cout<<"sumcount2 test = FAIL";
			cout<<"    DIFF="<<sumcount2-43604 <<endl;
			cout<<"======= CHECK RESULTS END ======= "<<endl;
	}

	{	/*Printf results to file!
		char filename[1024];sprintf(filename,"%s_output.csv",KERNELNAME);
		FILE *str=fopen(filename,"w");
		if(!str) { cout<<"ERROR at c_clase::save_float() opening "<<filename<<endl;getchar();return;}
		fprintf(str,"KERNEL = %s\n",KERNELNAME);
		fprintf(str,"sumove1=,%.8lg,sumove2=,%.8lg\nsumcount1=,%lg,sumcount2=,%lg\n\n",summove1,summove2,sumcount1,sumcount2);
		fprintf(str,"row,move1,move2,count1,count2\n");
		for (int i=0;i<NUMOUT;i++)
			fprintf(str,"%i ,%.7f ,%.7f ,%i ,%i \n",i,move1[i],move2[i],count1[i],count2[i]);
		fclose(str);*/
	}

	//End: delete part
	delete[] out;delete[]move1;delete[] move2;delete[] count1;delete[] count2;
}

void c_clase::funcion_BDP_gpu()
{

	short coefs_bcp[7] = { 72, 5, 110, 14, 1280, 720, 704 }; //VIDEO 2956 !!!!
	double bcp_coefficient=0.58; //VIDEO 2956 !!!!

	size_t local_size = max_local_size, global_size =pixels;
	long num_groups=pixels/(long) max_local_size; //to be used by compressed
	cout << "num_groups="<<num_groups<<endl;
	//1. Initialization:
	start=clock();
	cl_mem cl_im0,cl_im1,cl_im2,cl_bg,cl_bgcount,cl_imageout,cl_move1,cl_move2;
	cl_mem cl_coefxy1, cl_coefs, cl_move;
	cl_int status=0;
	try
	{

		//status = clSetKernelArg(kernel[0], 0, sizeof(cl_mem), (void *)&cl_gpuvideo[gpunum]); checkerror1(status, "Failed to set kernel argument 0");
		//Initialization:
		size_t size;
		size=pixels*sizeof(uchar);
		cl_im0 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_im0");
		status = clSetKernelArg(*kernel, 0, sizeof(cl_mem), (void *)&cl_im0); checkerror1(status, "Failed to set kernel argument 0");

		size= pixels*sizeof(ushort);
		cl_coefxy1 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_coefxy");
		status = clEnqueueWriteBuffer(queue, cl_coefxy1, CL_TRUE, 0, size, (void *)coefxy1, 0, NULL, NULL); checkerror1(status, "Failed to enqueue write buffer cl_coefxy1");
		status = clSetKernelArg(*kernel, 1, sizeof(cl_mem), (void *)&cl_coefxy1); checkerror1(status, "Failed to set kernel argument 1");

		size = 7 * sizeof(short);
		cl_coefs = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_coefs[]");
		status = clEnqueueWriteBuffer(queue, cl_coefs, CL_TRUE, 0, size, (void *)coefs_bcp, 0, NULL, NULL); checkerror1(status, "Failed to enqueue write buffer cl_coefs[]");
		status = clSetKernelArg(*kernel, 2, sizeof(cl_mem), (void *)&cl_coefs); checkerror1(status, "Failed to set kernel argument 2");

		size=pixels*sizeof(uchar);
		cl_bg = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_bg");
		status = clEnqueueWriteBuffer(queue, cl_bg, CL_TRUE, 0, pixels * sizeof(uchar), (void *)grayBG, 0, NULL, NULL); checkerror1(status, "Failed to enqueue write buffer cl_bg");
		status = clSetKernelArg(*kernel, 3, sizeof(cl_mem), (void *)&cl_bg); checkerror1(status, "Failed to set kernel argument 3");

		cl_bgcount = clCreateBuffer(context, CL_MEM_READ_WRITE, pixels*sizeof(cl_uchar), NULL, &status);checkerror1(status, "Failed to create buffer for cl_bgcount");
		uchar bgcount0=10;
		status = clEnqueueFillBuffer(queue, cl_bgcount, &bgcount0, sizeof(cl_uchar), 0, pixels*sizeof(cl_uchar), 0, NULL, NULL);checkerror1(status, "Failed to fill cl_bgcount");
		status = clSetKernelArg(*kernel, 4, sizeof(cl_mem), (void *)&cl_bgcount); checkerror1(status, "Failed to set kernel argument 4");

		cl_move = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(cl_ushort), NULL, &status); checkerror1(status, "Failed to create buffer for cl_move");//NOT USED
		status = clSetKernelArg(*kernel, 5, sizeof(cl_mem), (void *)&cl_move); checkerror1(status, "Failed to set kernel argument 5");

		size=pixels*sizeof(uchar);
		cl_imageout = clCreateBuffer(context, CL_MEM_READ_ONLY, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_imageout");
		status = clSetKernelArg(*kernel, 6, sizeof(cl_mem), (void *)&cl_imageout); checkerror1(status, "Failed to set kernel argument 6");

		size = SIZEOUT* sizeof(float);
		cl_move1 = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_move1");
		status = clSetKernelArg(*kernel, 7, sizeof(cl_mem), (void *)&cl_move1); checkerror1(status, "Failed to set kernel argument 7");
		cl_move2 = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_move2");
		status = clSetKernelArg(*kernel, 8, sizeof(cl_mem), (void *)&cl_move2); checkerror1(status, "Failed to set kernel argument 8");

		int i1=0;
		status = clSetKernelArg(*kernel, 9, sizeof(int), (void *)&i1); checkerror1(status, "Failed to set kernel argument 9");
		status = clSetKernelArg(*kernel, 10, sizeof(int), (void *)&i1); checkerror1(status, "Failed to set kernel argument 10");

		size=pixels*sizeof(uchar);
		cl_im1 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_im1");
		status = clSetKernelArg(*kernel, 11, sizeof(cl_mem), (void *)&cl_im1); checkerror1(status, "Failed to set kernel argument 11");
		cl_im2 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size, NULL, &status); checkerror1(status, "Failed to create buffer for cl_im2");
		status = clSetKernelArg(*kernel, 12, sizeof(cl_mem), (void *)&cl_im2); checkerror1(status, "Failed to set kernel argument 12");

#ifdef COMPRESSED2
		status = clSetKernelArg(*kernel, 13, max_local_size*sizeof(int), NULL); checkerror1(status, "Failed to set kernel argument 13 lmov1");
		status = clSetKernelArg(*kernel, 14, max_local_size*sizeof(int), NULL); checkerror1(status, "Failed to set kernel argument 14 lmov2");
#endif
	}
	catch (int error)
	{
		//std::cout << "ERROR PerformCalculationOnDevice:" << error.what() << "(" << error.err() << ")" << " ver:https://streamcomputing.eu/blog/2013-04-28/opencl-1-2-error-codes/" << std::endl;
		cout << "ERROR en c_clase::funcion_BDP_gpu(): " << endl;
		checkerror2_nonstop(status, "ERROR at c_clase::funcion_BDP_gpu() initialization try catch");
		checkerror2_nonstop(error, "ERROR at c_clase::funcion_BDP_gpu() initialization try catch");
		getchar(); getchar(); exit(0);
	}
	timer("\n c_clase::funcion_BDP_gpu() initialization timing :");

	//2. Usage: introduces image1 & 2 and then executes and extract data from kernel
	int *move1=new int[SIZEOUT];
	int *move2=new int[SIZEOUT];
	uchar *gray=new uchar[pixels];

	try
	{
		status = clEnqueueWriteBuffer(queue, cl_im0, CL_TRUE, 0, pixels * sizeof(uchar), (void *)gray1, 0, NULL, NULL); checkerror1(status, "Failed to enqueue write buffer cl_im0");
		status = clEnqueueWriteBuffer(queue, cl_im1, CL_TRUE, 0, pixels * sizeof(uchar), (void *)gray2, 0, NULL, NULL); checkerror1(status, "Failed to enqueue write buffer cl_im1");

		start=clock();
		status = clEnqueueWriteBuffer(queue, cl_im2, CL_TRUE, 0, pixels * sizeof(uchar), (void *)gray3, 0, NULL, NULL); checkerror1(status, "Failed to enqueue write buffer cl_im2");
		clFinish(queue);

		//RUN gpu
		status = clEnqueueNDRangeKernel(queue, *kernel, 1, NULL, &global_size, &local_size, 0, NULL, NULL); checkerror1(status, "Failed to enqueue kernel!");
		clFinish(queue);
		//Data extraction:
		status = clEnqueueReadBuffer(queue, cl_imageout, CL_TRUE, 0, pixels * sizeof(uchar), (void *)gray, 0, NULL, NULL); checkerror1(status, "Failed to read out data!");
		status = clEnqueueReadBuffer(queue, cl_move1, CL_TRUE, 0, SIZEOUT * sizeof(int), (void *)move1, 0, NULL, NULL); checkerror1(status, "Failed to read cl_move1 data!");
		status = clEnqueueReadBuffer(queue, cl_move2, CL_TRUE, 0, SIZEOUT * sizeof(int), (void *)move2, 0, NULL, NULL); checkerror1(status, "Failed to read cl_move2 data!");
		clFinish(queue);
	}
	catch (int error)
	{
		//std::cout << "ERROR PerformCalculationOnDevice:" << error.what() << "(" << error.err() << ")" << " ver:https://streamcomputing.eu/blog/2013-04-28/opencl-1-2-error-codes/" << std::endl;
		cout << "ERROR en c_clase::funcion_BDP_gpu() usage: " << endl;
		checkerror2_nonstop(status, "ERROR at c_clase::funcion_BDP_gpu() usage try catch");
		checkerror2_nonstop(error, "ERROR at c_clase::funcion_BDP_gpu() usage try catch");
		getchar(); getchar(); exit(0);
	}
	timer("\n c_clase::funcion_BDP_gpu() usage :");

	uchar *out=new uchar[3*pixels];
	gray_to_rgb(gray,out);delete gray;
	save_image_ppm("out_BDP.ppm",out,xmax,ymax);

	double summove1 = 0.0, summove2 = 0.0;
	{	//data results
		for (int i = 0; i < SIZEOUT; i++)  //NUMPOUT==ymax if uncompressed 
		{
			summove1 += move1[i];
			summove2 += move2[i];
		}	
		if (mask_xy_area1>0)
			summove1 = 100.0*summove1 / mask_xy_area1 * bcp_coefficient/coefxy_sf; //occupation rate in %. BCP_TRAFFIC_COEFFICIENT= effective area occuped by one m2 of vehicle 
		else summove1 = 0;
		if (mask_xy_area2>0)
			summove2 = 100.0*summove2 / mask_xy_area2 * bcp_coefficient/coefxy_sf; //occupation rate in %. BCP_TRAFFIC_COEFFICIENT= effective area occuped by one m2 of vehicle 
		else summove2 = 0;
		printf("  summove1=%lg summove2=%lg\n",summove1,summove2);
	}

	{	//check results!

			cout<<endl<<endl<<"======= CHECK RESULTS INI ======= "<<endl;
			if (fabs(summove1-11.208745708f)<0.01f)
				cout<<"Sumove1   test = OK  ";
			else
				cout<<"Sumove1   test = FAIL";
			cout<<"    DIFF="<<summove1-11.208745708f<<endl;

			if (fabs(summove2 - 6.55036615f)<0.01f)
				cout<<"Sumove2   test = OK  ";
			else
				cout<<"Sumove2   test = FAIL";
			cout<<"    DIFF="<<summove2 - 6.55036615f<<endl;

			cout<<"======= CHECK RESULTS END ======= "<<endl;
	}

	{	/*
		//Printf results to file!
		char filename[1024];sprintf(filename,"%s_output.csv",KERNELNAME);
		FILE *str=fopen(filename,"w");
		if(!str) { cout<<"ERROR at c_clase::save_float() opening "<<filename<<endl;getchar();return;}
		fprintf(str,"KERNEL = %s\n",KERNELNAME);
		fprintf(str,"sumove1=,%.8lg,sumove2=,%.8lg\nsumcount1=,%lg,sumcount2=,%lg\n\n",summove1,summove2,sumcount1,sumcount2);
		fprintf(str,"row,move1,move2,count1,count2\n");
		for (int i=0;i<NUMOUT;i++)
			fprintf(str,"%i ,%.7f ,%.7f ,%i ,%i \n",i,move1[i],move2[i],count1[i],count2[i]);
		fclose(str);*/
	}

	//End: delete part
	delete[] out;delete[]move1;delete[] move2;
}




void c_clase::init_c_clase() 
{ 
	gray1=gray2=gray3=grayBG=NULL;data_size=0;xmax=ymax=0;  sum_coefy1=sum_coefy2=mask_xy_area1=mask_xy_area2=0.0;coefy=NULL;coefxy1=NULL; 
	int xmax1,ymax1;
	uchar *data=NULL;

	read_image_ppm("2956_1.ppm",data,xmax1,ymax1);cout << "Loaded image file 2956_1.ppm at gray1"<<endl; 
	xmax=xmax1;ymax=ymax1;pixels=xmax1*ymax1;
	gray1=new uchar[pixels];rgb_to_gray(data,gray1);delete[] data;
	int xmax2,ymax2;

	read_image_ppm("2956_2.ppm",data,xmax2,ymax2);cout << "Loaded image file 2956_2.ppm at gray2"<<endl;
	gray2=new uchar[pixels];rgb_to_gray(data,gray2);delete[] data;
	if (xmax2!=xmax1 || ymax2!=ymax1 ) {cout<<"ERROR at c_clase::init_c_clase() xmax or ymax not equal. ABORT! "<<endl;getchar();}

	read_image_ppm("2956_3.ppm",data,xmax2,ymax2);cout << "Loaded image file 2956_3.ppm at gray3"<<endl;
	gray3=new uchar[pixels];rgb_to_gray(data,gray3);delete[] data;
	if (xmax2!=xmax1 || ymax2!=ymax1 ) {cout<<"ERROR at c_clase::init_c_clase() xmax or ymax not equal. ABORT! "<<endl;getchar();}

	read_image_ppm("2956_bg.ppm",data,xmax2,ymax2);cout << "Loaded image file 2956_bg.ppm at grayBG"<<endl;
	grayBG=new uchar[pixels];rgb_to_gray(data,grayBG);delete[] data;
	if (xmax2!=xmax1 || ymax2!=ymax1 ) {cout<<"ERROR at c_clase::init_c_clase() xmax or ymax not equal. ABORT! "<<endl;getchar();}

	load_videodata("2956_coefy.txt");//reads also 2956_coefxy.txt
	cout << "Loaded coefficients from 2956_coefy.txt to coefy. xmed="<<xmed<<" sum_coefy1="<<sum_coefy1<<" sum_coefy2="<<sum_coefy2<<endl;
	cout << "Also loaded coefxy and mask_xy_area1="<<mask_xy_area1<<" mask_xy_area2="<<mask_xy_area2<< endl;
}

void leelin(FILE *strin,char *linea)
{
	//removes 0x0D and 0x0A
	int i; 	linea[0]='\0';	char *ptr=linea;
	for (i=0;(i<1024 && !feof(strin)); i++)
	{
		*ptr++ = fgetc(strin);
		if (ptr[-1] == 10)	break;
	}
	if (i>=1)	ptr[-1]='\0';
	else 		linea[0]='\0';
	if (i>2 && ptr[-2]==0x0D) 	ptr[-2]='\0';
}

bool c_clase::read_image_ppm(char *filename, uchar  *&data, int &xmax1,int &ymax1)
{
	cout<<"Reading file "<<filename<<endl;
	xmax1=ymax1=0;
	FILE *str = fopen(filename, "rb");
	if (str == NULL) 	{ 		cout<<filename<< "Couldn't open for reading!\n";getchar(); 		return false; 	}
	char linea[1024];
	leelin(str,linea);if(linea[0]!='P'||linea[1]!='6')  { 		cout<<filename<< "PPM file not type P6, so couldn't read! \n";getchar();		return false; 	}
	leelin(str,linea);if(linea[0]=='#') leelin(str,linea);
	char *ptr=linea;xmax1=strtol(ptr,&ptr,10);ymax1=strtol(ptr+1,&ptr,10);leelin(str,linea);
	if (xmax1<1||xmax1>90000||ymax1<1||ymax1>90000) { 		printf("%s PPM file xmax or ymax is wrong= %i %i, so couldn't read! \n", filename,xmax1,ymax1);getchar();		return false; 	}
	data=new uchar[xmax1*ymax1*3];
	for (int j = 0; j < ymax1; j++) 
		fread(&data[3*j*xmax1], 1, 3*xmax1, str);
	fclose(str);
	return true;
}

void c_clase::load_videodata(char *filename)
{
	cout<<endl<<"=============================================="<<endl;
	//2.0 Load coefy[]
	FILE *str=fopen(filename,"r");
	if(!str) { cout<<"ERROR at c_processing::load_videodata() opening "<<filename<<endl;getchar();return;}
	coefy=new float[xmax*ymax];
	cout<<"Reading file "<<filename<<endl;
	fscanf(str,"%d %lg %lg ",&xmed,&sum_coefy1,&sum_coefy2);
	double check1=0.0;
	for (int i=0;i<pixels;i++)
	{
		if(feof(str))
		{cout<<"ERROR at c_processing::load_videodata() file end reached"<<filename<<endl;getchar();return;}
		fscanf(str,"%g ",&coefy[i]);check1+=coefy[i];
	}
	fgetc(str);
	if(!feof(str))
		cout<<"Warning at c_processing::load_videodata() file end not reached"<<endl;
	cout<< "xmed, sum_coefy1,sum_coefy2="<<xmed<<" "<<sum_coefy1<<" "<<sum_coefy2<<endl;
	cout<<"File "<<filename<<" checkout="<<check1<<endl;
	fclose(str);

	//2.0 Load coefxy1[]
	char filename2[1024];strcpy(filename2,filename);char *ptr=filename2+strlen(filename2)-5;strcpy(ptr,"xy1.txt");
	str=fopen(filename2,"r");
	if(!str) { cout<<"ERROR at c_processing::load_videodata() opening "<<filename2;getchar();return;}
	coefxy1=new ushort[xmax*ymax];
	int checkout=0;
	fscanf(str,"%lg %lg %lg ",&coefxy_sf,&mask_xy_area1,&mask_xy_area2);
	int i1;
	for (int i=0;i<pixels;i++)
	{
		if(feof(str))
		{cout<<"ERROR at c_processing::load_videodata() file end reached"<<filename<<endl;getchar();return;}
		fscanf(str,"%i ",&i1);coefxy1[i]=(ushort) i1;checkout+=coefxy1[i];
	}
	fgetc(str);
	if(!feof(str))
		cout<<"Warning at c_processing::load_videodata() file end not reached"<<endl;
	cout<< "coefxy_sf, mask_xy_area1,mask_xy_area2="<<coefxy_sf<<" "<<mask_xy_area1<<" "<<mask_xy_area2<<endl;
	cout<<"File "<<filename2<<" checkout="<<checkout<<endl;
	fclose(str);
	cout<<"=============================================="<<endl<<endl;
}


bool c_clase::save_image_ppm(char *filename, uchar  *data,int xmax1,int ymax1)
{
	FILE *output = fopen(filename, "wb");
	if (output == NULL)
	{
		printf("Couldn't open %s for writing!\n", filename);
		return false;
	}
	fprintf(output, "P6\n%d %d\n%d\n", xmax1, ymax1, 255);
	for (int j = 0; j < ymax1; j++) 
		fwrite(&data[3*j*xmax1], 1, 3*xmax1, output);
	fclose(output);	return true;
}

void c_clase::save_int(char *filename,int *data,int size)
{
	FILE *str=fopen(filename,"w");
	if(!str) { cout<<"ERROR at c_clase::save_int() opening "<<filename;getchar();return;}
	if (!data) { cout<<"ERROR at c_clase::save_int() data not exists";getchar();return;}
	for (int i=0;i<size;i++)
		fprintf(str,"%i\n",data[i]);
	fclose(str);
}
void c_clase::save_float(char *filename,float *data,int size)
{
	FILE *str=fopen(filename,"w");
	if(!str) { cout<<"ERROR at c_clase::save_float() opening "<<filename;getchar();return;}
	if (!data) { cout<<"ERROR at c_clase::save_float() data not exists";getchar();return;}
	for (int i=0;i<size;i++)
		fprintf(str,"%.7f\n",data[i]);
	fclose(str);
}




