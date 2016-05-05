#pragma warning(disable:4786) //quito todos los warnings 4786 de compilación
#include <string>
#include <iostream>
#include <map>
using namespace std;

class bound
{
public:
	string st1,st2;
	bound(string st){st1=st2=st;}
};

void main()
{
	/*
	map<bound,double> m1;
	typedef map<bound,double>::const_iterator m1i;
	bound b1("b1"),b2("b2");
	m1[b1]=1;m1[b2]=2;
	for (m1i q=m1.begin();q!=m1.end();++q,i++)
	{
		double x;
		x=q->second;
	}
	*/

	int i=0;
	map<string,int> m;

	string w[]={"uno","tres","siete","diez"};
	int wn[]={1,3,7,10};

	for (i=0;i<4;i++)
		m[w[i]]=wn[i];

	typedef map<string,int>::const_iterator mi;
	int total=0;
	for (mi p=m.begin();p!=m.end();++p)
	{
		total+=p->second;//p->second es el entero (1,3,7,10)
		cout<<p->first<<'\t'<<p->second<<'\n';//p->first es el nombre
	}

	cin>>i; 

}
