//Makes sums and media calculation by using a tree to avoid rounding errors. 

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

//tree sum reduction:
float reduction(float *data,int max)
{
	while(max>1)
	{
		data[max]=0.0;max=(max+1)/2;
		for (int i=0;i<max;i++)
			data[i]+=data[i+max];      //operation to be performed
	}
	return data[0];
}

//calculates media:
float reduction_media(float *data,int max)
{
	while(max>1)
	{
		data[max]=data[max/2];max=(max+1)/2;
		for (int i=0;i<max;i++)
			data[i]=(data[i]+data[i+max])/2.0f;      //operation to be performed
	}
	return data[0];
}

void main()
{
	cout<<"WARNING: run this program in RELEASE mode. Timing is non correct in DEBUG mode"<<endl;
	float *data=new float[SIZE+1];
	start=clock();
	memset(data,0,SIZE*sizeof(float));
	timer("\n memset(data,0,SIZE*sizeof(float)) ",SIZE);
	//This may be 5x faster in release mode!:
	std::fill(data, data+SIZE, 3.14f);
	timer("\n fill(data, data+SIZE, 3.14f)      ",SIZE);

	//Calculates media in standard way but FAILS due rounding errors:
	start=clock();
	float sum=0.0f;
	for (int i=0;i<SIZE;i++)
		sum+=data[i];
	sum=sum/(float) SIZE;
	timer("\n Standard for() reduction          ",SIZE);
	cout << "This should be 3.14="<<sum<<endl;

	//calculates media by using the tree reduction function, is OK and runs 20% faster in release mode:
	start=clock();
	sum=reduction(data,SIZE)/(float) SIZE;
	timer("\n Using reduction() function        ",SIZE);
	cout << "This should be 3.14="<<sum<<endl;

	//calculates media by using reduction_media:
	std::fill(data, data+SIZE, 3.14f);
	start=clock();
	sum=reduction_media(data,SIZE);
	timer("\n Using reduction() function        ",SIZE);
	cout << "This should be 3.14="<<sum<<endl;

	delete data;
	cout<<"===END==="<<endl;getchar();
}

