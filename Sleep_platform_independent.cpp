//Platform independent

#include <time.h>
#include <iostream>
#ifdef __linux 
int Sleep(int sleepMs) { return usleep(sleepMs * 1000); }
#else 
#include <Windows.h>
#endif


#pragma warning(disable:4996) 
typedef unsigned char uchar;
using namespace std;



int main()
{
	time_t start, stop;
	start = clock();
	Sleep(500);
	stop = clock();
	cout << "Delay is " << 1.0*(stop - start) / CLOCKS_PER_SEC << " seconds" << endl;
	cout << "=== END ===" << endl;
	getchar();
	return 0;
}