//test rotate arrays:
#include <iostream>
#include <stdlib.h>

using namespace std;

int array1[4] = { 100, 101, 102, 103 };
int array2[4] = { 200, 201, 202, 203 };
int array3[4] = { 300, 301, 302, 303 };
int *ptr0 = array1, *ptr1 = array2, *ptr2 = array3, *ptrx;


void main()
{
	int i;

	for (i = 0; i < 20; i++)
	{
		cout << ptr0[0] << " " << ptr1[0] << " " << ptr2[0] << endl;
		//ptrx = ptr0; ptr0 = ptr1; ptr1 = ptr2; ptr2 = ptrx; //rotates 3 arrays in only 4 operations. 0 <- 1 <- 2 <- 0
		ptrx = ptr2; ptr2 = ptr1; ptr1 = ptr0; ptr0 = ptrx; //rotates 3 arrays in only 4 operations. 0 -> 1 -> 2 -> 0
	}
	getchar();
}

