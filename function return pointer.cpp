#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#pragma warning(disable:4996)

typedef unsigned char uchar;
using namespace std;

uchar vector[256]={10,11,12,13,14,15,16,17,255};

void retornaptr(uchar **ptr) { *ptr=&vector[0]; }
uchar *retornaptr2(void) { return &vector[0]; }


void main()
{
	uchar *v1;
	v1=retornaptr2();

	ofstream strout;
	strout.open("out.txt", ios::out | ios::trunc );

	int i;
	for (i=0;i<20;i++)
		strout << (int) v1[i] << " ";
	strout << endl;
	strout.close();

	printf("\n\n===FIN===\n");
	char c; scanf("%c%c",&c,&c);
}