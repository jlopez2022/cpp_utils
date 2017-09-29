
#include <iostream>
#include <time.h> //clock()
#pragma warning(disable:4996) //disable deprecateds
using namespace std;
typedef unsigned char uchar;

time_t start,stop;
//Timing function. Add this command to the beginning of the function to be measured: start=clock();
void timer(char *title,int size=0)
{
	stop=clock();
	cout<<title<< " time ="<<(double) (stop-start)/(double) CLOCKS_PER_SEC<< " secs";
	if (size)
		cout << " = " << 1e-6*size/( (double)(stop-start)/(double)CLOCKS_PER_SEC ) <<  " Mops/seg"   <<endl; 
	else
		cout<<endl;
	start=clock();//it must be done better in the beginning of the function to be measured
}

#define SIZE 100000000 //100Meg

void main()
{
	cout<<"WARNING: run this program in RELEASE mode. Timing is non correct in DEBUG mode"<<endl;
	float *data=new float[SIZE];
	start=clock();
	memset(data,0,SIZE*sizeof(float));
	timer("\n memset(data,0,SIZE*sizeof(float)) ",SIZE);
	//This may be 5x faster in release mode!:
	std::fill(data, data+SIZE, 3.14f);
	timer("\n fill(data, data+SIZE, 3.14f)      ",SIZE);

	delete data;
	cout<<"===END==="<<endl;getchar();
}

