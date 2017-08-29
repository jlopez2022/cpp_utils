/*
Uses 2D arrays.
Main routines are:
init_2Dvector() that initializes any 2d vector (can be uchar, char, int, float or double)
multiply_2Dvector()
inverse()
*/

#include<iostream>
#include <vector>
using namespace std;

void print_2Dvector(vector<vector<double> >& vec)
{
	size_t xmax, ymax;
	ymax = vec.size();
	xmax = vec[0].size(); 

	int x, y;
	for (y = 0; y < ymax; y++)
	{
		for (x = 0; x < xmax; x++)
			cout << vec[y][x] << " \t";
		cout << endl;
	}
}

//Resizes to y_dim,x_dim any kind of 2d array:
template<typename T>
void init_2Dvector(vector<vector<T> >& vec, size_t y_dim, size_t x_dim)
{
	vec.resize(y_dim);
	for (size_t i = 0; i < vec.size(); i++)
		vec[i].resize(x_dim);
}
//Returns vec1*vec2. vec1 and 2 are not touch
vector< vector<double> > multiply_2Dvector(vector< vector<double> > vec1, vector< vector<double> > vec2)
{
	size_t xmax, ymax;
	ymax = vec1.size();   
	xmax = vec1[0].size();
	vector< vector<double> > vec3;
	if ((ymax != vec2[0].size()) || (xmax != vec2.size()))
	{
		cout << "ERROR on dim2_multiply() dimensions of vec2 not corresponding with vec1 ones" << endl; getchar(); return{};//returns a null
	}
	init_2Dvector(vec3, ymax, ymax);
	cout << "dimensions of vec3=" << vec3.size() << " x " << vec3[0].size() << endl;
	double xx;
	for (int y = 0; y < ymax; y++)
		for (int x = 0; x < ymax; x++)
		{
			xx = 0.0;
			for (int t = 0; t < xmax; t++)
				xx += vec1[y][t] * vec2[t][x];
			vec3[y][x] = xx;
		}
	return vec3;//ok
}

//returns inverse of x2, x2 is not modified
vector< vector<double> > inverse(vector< vector<double> > x2)
{
	if (x2.size() != x2[0].size())
	{
		cout << "ERROR on inverse() not square array" << endl; getchar(); return{};//returns a null
	}

	size_t dim = x2.size();
	int i, j, ord;
	vector< vector<double> > x,y;//output
	init_2Dvector(x, dim, dim); x = x2;
	init_2Dvector(y, dim, dim);
	//1. Unity array y: 
	for (i = 0; i<dim; i++) 
		for (j = 0; j<dim; j++)
		{
			if (i==j)
				y[i][j] = 1.0;
			else
				y[i][j] = 0.0;
		}

	double diagon, coef;
	double *ptrx, *ptry, *ptrx2, *ptry2;
	for (ord = 0; ord<dim; ord++)
	{
		//2 Hacemos diagonal de x =1
		diagon = x[ord][ord];
		if (fabs(diagon)<1e-15)
		{
			long i2;
			for (i2 = ord + 1; i2<dim; i2++)
			{
				if (fabs(x[ord][i2])>1e-15) break;
			}
			if (i2 >= dim)
				return{};//error, returns null
			for (i = 0; i<dim; i++)//sumo la linea que no es 0 el de la misma fila de ord
			{
				x[ord + i][ord] += x[ord + i][i2];
			}
		}
		ptry = &y[ord][0];
		for (i = 0; i<dim; i++)
			*ptry++ /= diagon;
		ptrx = &x[ord][ord];
		for (i = ord; i<dim; i++)//para i<ord *ptrx=0,
			*ptrx++ /= diagon;

		//Hacemos '0' la columna ord salvo elemento diagonal:
		for (i = 0; i<dim; i++)//Empezamos por primera fila
		{
			if (i == ord) continue;
			coef = x[i][ord];//elemento ha hacer 0 
			if (fabs(coef)<1e-15) continue; //si es cero se evita
			ptry = &y[i][0];
			ptry2 = &y[ord][0];
			for (j = 0; j<dim; j++)
				*ptry++ = *ptry - coef * (*ptry2++);
			ptrx = &x[i][ord];
			ptrx2 = &x[ord][ord];
			for (j = ord; j<dim; j++)
				*ptrx++ = *ptrx - coef * (*ptrx2++);
		}
	}//end ord
	return y;
}

void test_one_dimension_vector()
{
	vector<int> v = { 4, 100, 107, 2008 };
	v.reserve(40);//Do this if you planned to increase vector v to 40 values
	v.push_back(1024);
	int* pv = &v[0];
	int *pv2 = v.data(); //makes the same in c++11
	pv2[1] = 128;//modifies also v and pv

	int i;
	cout << "input vector = ";
	for (i = 0; i < 5; i++)
		cout << v[i] << " ";
	cout << endl;

	cout << "input array  = ";
	for (i = 0; i < 5; i++)
		cout << pv[i] << " ";
	cout << endl;

	//conversion from array to vector:
	cout << "input vector2= ";
	vector<int> v2(pv, pv + 5);
	for (i = 0; i < 5; i++)
		cout << v2[i] << " ";
	cout << endl;

	vector<int> v3(45);
	cout << "vector v3 size must be 45: " << v3.size() << endl;
}

void test_2_dimension_vector()
{
	vector< vector<double> > vec1 = {
		{ 104.5, 100.2, 107.7, 1008.3 },
		{ 204.5, 200.2, 207.7, 2008.3 },
		{ 304.5, 300.2, 307.7, 3008.3 }
	};
	vector< vector<double> > vec2 = {
		{ 100.5, 200.6, 300.7 },
		{ 110.5, 210.6, 310.7 },
		{ 120.5, 220.6, 320.7 },
		{ 130.5, 230.6, 340.7 },
	};
	vector< vector<double> > vec3;

	vec3 = multiply_2Dvector(vec1, vec2);
	//cout << "dimensions of vec3=" << vec3.size() << " x " << vec3[0].size() << endl;

	int x, y;
	cout << "multiply 2d array:" << endl;
	for (y = 0; y < 3; y++)
	{ 
		for (x = 0; x < 3; x++)
		{
			cout << vec3[y][x] << " \t";
		}
		cout << endl;
	}
	//double xx = vec3[1][0];
	cout << endl;
}

void test_3_inverse()
{
	vector< vector<double> > vec1 = {
		{ 1, 1, 1, 0 },
		{ 1, 0, 1, 1 },
		{ 1, 1, 0, 1 },
		{ 0, 1, 1, 3 },
	};
	vector< vector<double> > vec2;
	vec2 = inverse(vec1);
	vector< vector<double> > vec3;
	vec3 = multiply_2Dvector(vec1, vec2);

	cout << "initial array (must be unmodified):" << endl;
	print_2Dvector(vec1);

	cout << "inverse array:" << endl;
	print_2Dvector(vec2);

	cout << "Must be diagon array:" << endl;
	print_2Dvector(vec3);

	cout << endl;
}


int main()
{
	vector< vector<double> > vec1;
	init_2Dvector(vec1, 10, 5);	//size_t ymax = vec1.size(),xmax = vec1[0].size();
	//test_2_dimension_vector();
	//test_one_dimension_vector();
	test_3_inverse();
	cout << endl << "=== END ===" << endl; getchar(); 
	return 1;
}


