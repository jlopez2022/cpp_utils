#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

void func(int*& r, int& size) { r = new int[size];  }
void func2(vector<int>& v) { v.resize(100); }

void main()
{
	int* mat,size;

	for (size = 10; size <= 1000; size++)
	{
		func(mat, size);
		mat[size - 1] = 100;
		cout << mat[size - 1] << endl;
		delete mat;
	}

	vector<int> v; // empty vector of ints
	func2(v);
	for (int i = 0; i < v.size(); i++) { v[i] = 100 + i; }
	v.clear();

	std::vector<int> first;                                // empty vector of ints
	std::vector<int> second(4, 100);                       // four ints with value 100
	std::vector<int> third(second.begin(), second.end());  // iterating through second
	std::vector<int> fourth(third);                       // a copy of third


	cout << "===FIN===" << endl;getchar(); getchar();
}