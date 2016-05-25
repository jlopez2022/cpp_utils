#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

void func2(vector<int>& v) { v.resize(100); }

void main()
{
	vector<int> v; // empty vector of ints
	func2(v);
	for (int i = 0; i < v.size(); i++) { v[i] = 100 + i; }
	v.clear();

	std::vector<int> first;                                // empty vector of ints
	std::vector<int> second(4, 100);                       // four ints with value 100
	std::vector<int> third(second.begin(), second.end());  // iterating through second
	std::vector<int> fourth(third);                       // a copy of third


	//push_back:

	std::vector<int> myvector;
	myvector.push_back(100);
	myvector.push_back(200);
	myvector.push_back(300);

	std::cout << "myvector contains:";
	for (unsigned i = 0; i<myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	myvector.clear();
	myvector.push_back(1101);
	myvector.push_back(2202);

	std::cout << "myvector contains:";
	for (unsigned i = 0; i<myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';



	cout << "===FIN===" << endl;getchar(); getchar();
}


