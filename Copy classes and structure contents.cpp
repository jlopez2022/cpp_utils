#include <iostream>


struct s_struct
{
	int a, b;
	double w;
}s1,s2,s3;

class c_class
{
public:
	int a, b;
	double w;
}c1,c2,c3;


using namespace std;


void main()
{
	s1.a = 10; s1.b = 12; s1.w = 100.111;
	memcpy(&s2, &s1, sizeof(s_struct));
	s3 = s1; //C90+ only
	if ((&s1 == &s3) || (&s1==&s2))
		cout << "STUPID copy of structures" << endl;
	else
		cout << "right copy of structures" << endl;
	c1.a = 22; c1.b = 24; c1.w = 200.222;
	memcpy(&c2, &c1, sizeof(c_class));
	c3 = c1;//C90+ only
	if ((&c1 == &c3) || (&c1 == &c2))
		cout << "STUPID copy of classes" << endl;
	else
		cout << "right copy of classes" << endl;


	cout << "=================== END ======================" << endl << endl;
	getchar(); getchar();
}

