//Fills and copies structs in an easy way
//Use debug mode to check str1 and 2 contents
#include <iostream>
//#pragma warning(disable:4996)

using namespace std;

struct s_str
{
	char linea[1024];
	int num;
	float f;
};



int main() 
{
	s_str str1{ "linea0", 10, 20.0f },str2;
	memcpy(&str2, &str1, sizeof(s_str));
	cout << "=== END ===" << endl;
	getchar(); 
	return 1;
}
