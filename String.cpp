#include <iostream>
#include <string>

using namespace std;

void imprime(const char *c)
{
	cout << "line:" << c << endl;
}

void imprime2(char *c)
{
	cout << "line:" << c << endl;
}

void main()
{
	string a="Rincon",b=" provincia de Malaga",c;
	size_t ii;

	ii=a.size();
	c=a+b;
	ii=c.length();

	c=a;

	c=a+" de la Victoria"+b;
	imprime(c.c_str());
	c=b;
	imprime(c.c_str());
	imprime2((char *)c.c_str());
	cout << "=== END ===" << endl; getchar();
}