//Please do not modify this filename or will not work!!!
//Here are two numbers to get from file: 18123.12 12.33

#include <iostream>
#include <string>
using namespace std;

void swap(void **a,void **b)
{
	void *x=*a;*a=*b;*b=x;
}

//swaps anything!: 
template<class A>
void swap2(A *&a,A *&b)
{
	A *x=a;a=b;b=x;
}

struct s_st
{
	int i1,i2;
};


void main()
{
	cout<<endl<<"swapping following array:"<<endl;
	int a[3]={100,101,102};
	int b[3]={200,201,202};
	cout << "a:"<<a[0]<<" "<<a[1]<<" "<<a[2]<<endl;
	cout << "b:"<<b[0]<<" "<<b[1]<<" "<<b[2]<<endl;

	cout<<"swap2(a1,b1):"<<endl;
	int *a1=a,*b1=b;
	swap2(a1,b1);
	cout << "a:"<<a1[0]<<" "<<a1[1]<<" "<<a1[2]<<endl;
	cout << "b:"<<b1[0]<<" "<<b1[1]<<" "<<b1[2]<<endl;

	cout<<"swap((void **)&a1,(void **)&b1):"<<endl;
	a1=a;b1=b;
	swap((void **)&a1,(void **)&b1);
	cout << "a:"<<a1[0]<<" "<<a1[1]<<" "<<a1[2]<<endl;
	cout << "b:"<<b1[0]<<" "<<b1[1]<<" "<<b1[2]<<endl;


	s_st s1{100,101},s2{200,201};
	cout<<endl<<"swapping structs"<<endl;
	cout<<"struct-1="<<s1.i1<<" "<< s1.i2<<endl;
	cout<<"struct-2="<<s2.i1<<" "<< s2.i2<<endl;
	cout<<"swap2(t1,t2):"<<endl;
	s_st *t1=&s1,*t2=&s2;
	swap2(t1,t2);
	cout<<"struct-1="<<t1->i1<<" "<< t1->i2<<endl;
	cout<<"struct-2="<<t2->i1<<" "<< t2->i2<<endl;

	cout << "=== END ===" << endl; getchar();
}
