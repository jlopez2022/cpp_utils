#include <iostream>

using namespace std;


class c_clase
{
public:
	c_clase(long in1) { a1 = in1; }
	double multiplica(double a, double b) { return a*b; }
private:
	long a1;
};

double inyecta_clase(c_clase *clase1, double b)
{
	b = clase1->multiplica(b, b);
	return b;
}

double inyecta_clase(c_clase clase1, double b)
{
	b = clase1.multiplica(b, b);
	return b;
}

int main()
{
	c_clase *clase1=new c_clase(15);
	c_clase clase2(10);
	double c,d=7;
	c = inyecta_clase(clase1, d);	cout << "c = " << c << endl;
	d = 100;
	c = inyecta_clase(clase2, d);	cout << "c = " << c << endl;
	cout << "\n=== FIN ====" << endl; getchar(); getchar();
	return 0;
}