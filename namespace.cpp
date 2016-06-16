#include <stdio.h>
#include <iostream.h>
#include <string>
using namespace std;

namespace Stack
{
	void push(char);
}

namespace Stack
{
	const int size=200;
	char v[size];
	int index=0;
	void push(char c)
	{
		if (index<(size-1))
		{
			v[index++]=c;
		}
	}
}

void main()
{
	char c1[]="abcdef";
	string st1,st2,st3;
	st1="hola ";st2="mm";
	st3=st1+st2;
	for (int i=0;i<5;i++)
		Stack::push(c1[i]);
	const char* c2=st3.c_str();
	cout <<c2;
	cin >> c1;
}