#include <iostream>
#include <stdlib.h>


using namespace std;

double ran1()
{
	return(1.0*(((rand() & 0xFFF) << 12) + (rand() & 0xFFF)) / 0x1000000);
}

void main()
{
	long count[1001];
	for (long i = 0; i < 1000; i++)
		count[i] = 0;

	for (long i = 0; i < 100000; i++)
	{
		double x = ran1();
		long i1 = (long)(x * 1000);
		count[i1]++;
	}
	long countmin = 100000, countmax = -1;
	for (long i = 0; i < 1000; i++)
	{
		if (countmin > count[i])
			countmin=count[i];
		if (countmax < count[i])
			countmax=count[i];
	}
	cout << "countmin=" << countmin << endl;
	cout << "countmax=" << countmax << endl;
	if (count[1000]>0)
		cout << "ERROR count[1000]=" << count[1000] << " must be zero!!" << endl;
	getchar(); getchar(); 
}

