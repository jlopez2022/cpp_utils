#include<iostream>
using namespace std;
#define LINE "define line"

void non_const_call(char *c)
{
	c[1] = '#';
}

void const_call(const char *c)
{
	cout << c << endl;
}



int main()
{
	char *non_const_line = (char *) "non constant line constant data";
	const char *const_line = (char *) "constant line constant data";
	char char_type[1024] = "char type line";

	non_const_call(non_const_line);
	const_call(const_line);
	non_const_call(char_type); //ok

	non_const_call(LINE); //warning when compiled in linux: deprecated conversion from string constant to ‘char*’ [-Wwrite-strings]
	const_call(LINE);//ok

	cout << endl << "=== END ===" << endl; getchar(); 
	return 1;
}


void llena(double w[10][20])
{
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 20; x++)
			w[y][x] = 100.0 * x;

}
