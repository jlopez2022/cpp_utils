#include "stdafx.h"
#include <iostream>
using namespace std;


int main()
{
    char s[1024]="Hello World!",s1[5]="Pepa";
	cout<< "Inicio"<<endl;
	strcat_s(s,sizeof(s)," end");
	strcat_s(s1,sizeof(s1)," end");
	cout << "Resultado1:"<<s<<endl;
	cout << "Resultado2:"<<s1<<endl;
	getchar();getchar();
}