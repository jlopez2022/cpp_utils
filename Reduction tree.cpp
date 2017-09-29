/*Tree reduction to be used in OpenCL accordingly:
http://web.engr.oregonstate.edu/~mjb/cs575/Handouts/opencl.reduction.2pp.pdf
http://developer.amd.com/resources/articles-whitepapers/opencl-optimization-case-study-simple-reductions/
*/
#include <iostream>
using namespace std;
typedef unsigned char uchar;
#include <math.h>


void main()
{
	const int max_size=100;
	double data[max_size+1];
	int size;
	for (size=3;size<max_size;size++)
	{
		for (int i=0;i<max_size+1;i++)
			data[i]=1e99;
		for (int i=0;i<size;i++)
			data[i]=100.0;

		//Tree reduction to be used in OpenCL 
		int max=size;
		while(max>1)
		{
			data[max]=0.0;max=(max+1)/2;
			for (int i=0;i<max;i++)
				data[i]+=data[i+max];
		}

		double expected=size*100.0;
		cout << "size="<<size<<" Output="<<data[0]<<" Expected="<<expected;
		if (fabs(data[0]-expected)>1e-6)
			cout<<" ERROR";
		cout<<endl;
	}


	cout<<"===END==="<<endl;getchar();
}