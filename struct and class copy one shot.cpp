//Test of not modified class member address from outside
#include <iostream>

#pragma warning(disable:4996) 
typedef unsigned char uchar;
using namespace std;

class c_prue
{
public:
	uchar dir1;
	uchar *give_dir(){ return &dir1; }
	uchar *give_dir2(){ return &dir2; }
private:
	uchar dir2;
};

typedef unsigned short ushort;
struct s_str
{
	int a, b;
	ushort c;
	float f;
};

class c_cls
{
public:
	int a, b;
	ushort c;
	float f;
};

void imprime(s_str str)
{
	cout << "a=" << str.a << " b=" << str.b << " c=" << str.c << " f=" << str.f << endl;
}
void imprime(c_cls str)
{
	cout << "a=" << str.a << " b=" << str.b << " c=" << str.c << " f=" << str.f << endl;
}



int main()
{
	//test of copying structs in the right way!
	cout << endl << "Test of copying structs in one shot!" << endl;
	s_str str1{ 10, 12, 133, 123.4f };
	s_str str2{ 215, -280, 2450, -432.4f };
	s_str str3;

	memcpy(&str3, &str1, sizeof(s_str));//right
	imprime(str1);
	imprime(str3);

	cout << endl;
	char *ptr1 = (char *)&str1;
	char *ptr2 = (char *)&str2;
	char *ptr3 = (char *)&str3;
	memcpy(ptr3, ptr2, sizeof(s_str));
	imprime(str2);
	imprime(str3);

	cout << endl;
	char buffer[128]; 
	s_str *str4 = (s_str *) &buffer[0];   
	str4->a = 333; str4->b = 334; str4->c = 328;  str4->f = 339.993f;
	memcpy(&str3, str4, sizeof(s_str));
	imprime(*str4);
	imprime(str3);

	cout << endl;
	memcpy(buffer, &str1, sizeof(s_str));
	memcpy(&str3, buffer, sizeof(s_str));
	imprime(str1);
	imprime(str3);
	imprime(*str4);

	//test of copying classes in the right way!
	cout << endl;
	c_cls cls1{ 100, -110, 130,   101.133f };
	c_cls cls2{ 202, -212, 224, -2101.223f };
	c_cls cls3;
	memcpy(&cls3, &cls1, sizeof(c_cls));
	imprime(cls1);
	imprime(cls3);
	memcpy(&cls3, &cls2, sizeof(c_cls));
	imprime(cls2);
	imprime(cls3);

	cout << "=== END ===" << endl;  
	getchar();
	return 0;
}