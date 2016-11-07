#include <iostream>
#define ABS(a) ((a) < 0 ? (-(a)) : (a))
typedef unsigned char uchar;

using namespace std;

struct c_str1
{
	int c1;
	float f1;
};

class c_clas1
{
public:
	int c1;
	float f1;
};

int fun1(int i1, c_str1 str1)
{
	str1.c1 += i1;
	str1.f1 += (float)i1;
	return str1.c1;
}

int fun1b(int i1, c_str1 *str1)
{
	str1->c1 += i1;
	str1->f1 += (float)i1;
	return str1->c1;
}

int fun2(int i1, c_clas1 str1)
{
	str1.c1 += i1;
	str1.f1 += (float)i1;
	return str1.c1;
}

int fun3(int i1, c_clas1* str2)
{
	str2->c1 += i1;
	str2->f1 += (float)i1;
	return str2->c1;
}

void main()
{
	c_str1 str;
	str.c1 = 100;
	str.f1 = 1000.0f;

	c_clas1 clase1;
	clase1.c1 = 500;
	clase1.f1 = 5000.0f;

	cout << "=== testing parsing struct as a data: we can read but not write in the struct ====\n";
	cout << fun1(17, str) << endl;
	cout << fun1(10, str) << " 17 added but not saved at the struct"<<endl;
	cout << fun1(10, str) << " 10 added but not saved at the struct" << endl;

	cout << "=== testing parsing struct as a pointer: we can read but not write in the pointer ====\n";
	cout << fun1b(17, &str) << endl;
	cout << fun1b(10, &str) << " 17 added and saved at the struct" << endl;
	cout << fun1b(10, &str) << " 10 added and saved at the struct" << endl;

	cout << "=== testing parsing class as a data: we can read but not write in the class ====\n";
	cout << fun2(17, clase1) << endl;
	cout << fun2(10, clase1) << " 17 added but not saved at the class" << endl;
	cout << fun2(10, clase1) << " 10 added but not saved at the class"<<endl;

	cout << "=== testing parsing class as pointers: we can read and write in the class ====\n";
	cout << fun3(17, &clase1) << endl;
	cout << fun3(10, &clase1) << " 17 added and saved at the class" << endl;
	cout << fun3(10, &clase1) << " 10 added and saved at the class" << endl;


	cout << "\n\n======end========\n"; getchar(); getchar();
}

