/*0.0 Uncomment to use c checker
#define __global 
#define __local
#define __kernel
#define uchar unsigned char
#define restrict 
#include <math.h>
int get_global_id(int i1){ return 1; }
void barrier(int i1){}
int CLK_LOCAL_MEM_FENCE;
//*/

// data size=HEIGHT*WIDTH  where HEIGHT<WIDTH  
__kernel void hallamedia(
	__global float*  data,  //0..WIDTH*HEIGHT
	int WIDTH,
	int HEIGHT,
	__global double*  sumout //output 0..HEIGHT
)
{
        int k = get_global_id(0);//0..HEIGHT
		double sum=0.0;
		__global float *x=data+k*WIDTH;
		for (int j=0;j<WIDTH;j++)
			sum+=x[j];
		sumout[k]=sum;
}

__kernel void hallaRMS(
	__global float*  data,  //0..WIDTH*HEIGHT
	int WIDTH,
	int HEIGHT,
	double  media,
	__global double *rms //output 0..HEIGHT
)
{
        int k = get_global_id(0); //0..HEIGHT
		float x2;double sum=0.0;
		__global float *x=data+k*WIDTH;
		for (int j=0;j<WIDTH;j++)
		{
			x2=x[j]-media;sum+=(double) (x2*x2);
		}
		rms[k]=sum;
}