//Platform independent

// linux compilation:         g++ -std=c++11 -lstdc++ prue prueba.cpp   
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;


int main()
{
	this_thread::sleep_for(std::chrono::microseconds(123));
	cout << "=== END ===" << endl; getchar();
	return 1;
}