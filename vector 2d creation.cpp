//Ordering using vectors. Also obtain a list.

#include <iostream>     // std::cout
#include <vector>       // std::vector
#pragma warning(disable:4996) //disable deprecateds
using namespace std;

template<typename T>
void print_2Dvector(vector<vector<T> >& vec)
{
	size_t xmax= vec[0].size(), ymax= vec.size(), x, y;

	for (y = 0; y < ymax; y++)
	{
		for (x = 0; x < xmax; x++)
			cout << vec[y][x] << " \t";
		cout << endl;
	}
}


int main()
{
	vector<int> row(4);
	vector < vector<int> > matriz;

	row = { 10, 100, 1000, 10000 };
	matriz.push_back(row);
	row = { 20, 200, 2000, 20000 };
	matriz.push_back(row);
	matriz.push_back({ 30, 300, 3000, 30000 });
	matriz.push_back({ 40, 400, 4000, 40000,-7 }); // -7 is ignored
	cout << "matrix:" << endl;
	print_2Dvector(matriz);

	vector < vector<double> > matriz2(8, vector<double>(5,-1.0)); //creates a 2d array ymax=8,xmax=5 all initialized to -1
	cout << "matrix2:" << endl;
	print_2Dvector(matriz2);

	cout << "=== END ===" << endl; getchar();
}

