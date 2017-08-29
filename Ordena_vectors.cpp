//Ordering using vectors. Also obtain a list.

#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <time.h> //timers
#pragma warning(disable:4996) //disable deprecateds
using namespace std;

bool compare_down(double a, double b) { return (a>b); }
bool compare_up(double a, double b) { return (a<b); }

//Checks if the vector is ascending:
template<typename T>
int check_up(vector<T> a)
{
	for (int i = 1; i < a.size(); i++)
	{
		if (a[i] < a[i - 1])
			return i;//failure. i=index of wrong ordered data
	}
	return 0;//ok
}

//Used to obtain the list:
vector<double> vcmp; //vector that contains the data
bool compare_list_up(int a, int b) { return (vcmp[a]<vcmp[b]); }
int check_list_up(vector<int> list)
{
	for (int i = 1; i < list.size(); i++)
	{
		if (vcmp[list[i]] < vcmp[list[i-1]])
			return i;//failure. i=index of wrong ordered data
	}
	return 0;//ok
}

int main()
{
	FILE *stream;
	stream = fopen("ordenacion.txt", "r");//contains random 20000 floating points generated using excel
	if (!stream)
	{
		cout << "Error opening ordenacion.txt" << endl; getchar(); return -1;
	}
	vector<double> vini;
	while (!feof(stream))
	{
		double x;
		fscanf(stream, "%lf", &x);
		if (!feof(stream)) //avoids last null one
			vini.push_back(x);
	}
	size_t longitud = vini.size();
	vector<double> v; v.resize(longitud);
	fclose(stream);
	time_t inicio, fin;
	int sort_result;
	double time;

	//1. === SORTING without function:
	cout << "Sort without using function in ascending order:" << endl;
	v = vini; //copies vini -> v
	inicio = clock();
	sort(v.begin(), v.end());
	fin = clock();
	sort_result = check_up(v);
	if (sort_result == 0)
		cout << "Sorting result is OK" << endl;
	else
		cout << "Sorting failed at element number " << sort_result << endl;
	time = (1.0*fin - inicio) / CLOCKS_PER_SEC;
	cout << "Time=" << time << " seconds" << endl; 

	//2. === SORTING using function:
	cout << "Sort using function in ascending order:" << endl;
	v = vini; //copies vini -> v
	inicio = clock();
	sort(v.begin(), v.end(), compare_up);
	fin = clock();
	sort_result = check_up(v);
	if (sort_result == 0)
		cout << "Sorting result is OK" << endl;
	else
		cout << "Sorting failed at element number " << sort_result << endl;
	time = (1.0*fin - inicio) / CLOCKS_PER_SEC;
	cout << "Time=" << time << " seconds" << endl;

	//3. === Obtains the order list:
	cout << "Sort list obtaining:" << endl;
	vcmp = vini;
	vector<int> list;
	for (int i = 0; i < longitud; i++)
		list.push_back(i);
	inicio = clock();
	sort(list.begin(), list.end(), compare_list_up);
	fin = clock();
	sort_result = check_list_up(list);
	if (sort_result == 0)
		cout << "Sorting result is OK" << endl;
	else
		cout << "Sorting failed at element number " << sort_result << endl;
	time = (1.0*fin - inicio) / CLOCKS_PER_SEC;
	cout << "Time=" << time << " seconds" << endl;

	cout << "=== END ===" << endl; getchar();
}

