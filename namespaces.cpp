#include <iostream>
#include <chrono>
#include <thread>  //usleep
#pragma warning(disable:4996) //o cualquier otro 
using namespace std;

namespace n_1
{
	int x = 100, y = 200;
	double funcion1(int a, int b) { return (double)(a*b); }
}

namespace n_2
{
	double x = 10.3, y = 20.66;
	double funcion1(double a, double b) { return (double)(a*b); }
}


int main()
{
	{
		using namespace n_1;
		cout << "x=" << x << " y=" << y << endl;
	}
	{
		using namespace n_2;
		cout << "x=" << x << " y=" << y << endl;
	}
	cout << "x=" << n_1::x << " y=" << n_1::y << endl;
	cout << "x=" << n_2::x << " y=" << n_2::y << endl;

	double result = n_2::funcion1(33.33, 100.1010);
	cout << "result=" << result << endl;
	getchar();
	return 0;
}


