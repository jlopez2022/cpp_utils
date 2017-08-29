//Please do not modify this filename or will not work!!!
//Here are two numbers to get from file: 18123.12 12.33

#include <iostream>
#include <string>

using namespace std;

class c_A
{
public:
	static int xmax, ymax;
	static int x2(int x);
}p1,p2;

class c_B : public c_A
{
public: 
	int x2;
};

int c_A::xmax=0, c_A::ymax=0;
int c_A::x2(int x) {return x*x;}

void main()
{
	c_B B1;
	p1.xmax=7;
	cout <<"xmax="<<p2.xmax<<endl;
	//You can use c_A static vars like this:
	c_A::xmax=77;  c_A::ymax=177;
	cout <<"c_A::xmax="<<c_A::xmax;

	cout <<"  =p2.xmax="<<p2.xmax<<endl;
	cout <<"B1.xmax="<<B1.xmax<<" ymax="<<B1.ymax <<endl;
	c_A::xmax=88;  c_A::ymax=388;  
	cout <<"c_A::xmax="<<c_A::xmax;

	cout <<"  =p2.xmax="<<p2.xmax<<endl;

	cout <<"B1.xmax="<<B1.xmax<<" ymax="<<B1.ymax <<endl;
	cout<<endl;
	//You can use also static functions of a class without instantiate the class:
	int xx2=c_A::x2(11);
	cout <<"Using c_A::x2(11)="<<c_A::x2(11)<<endl;


	cout << "=== END ===" << endl; getchar();
}
