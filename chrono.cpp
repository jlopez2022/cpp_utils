//<chrono> SOLO VALIDO EN C++11!!

#include <iostream>
#include <chrono>
#include <thread>
using namespace std;


int main() {
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono; // nanoseconds, system_clock, seconds

	sleep_for(nanoseconds(10));
	sleep_until(system_clock::now() + seconds(1));

	long i;
	for (i = 0; i < 10; i++)
	{
		_sleep(500);// C++ estandard
		cout << i << " ";
	}

	for (i = 0; i < 100; i++)
	{
		sleep_for(milliseconds(500));
		cout << i << " ";
	}
}