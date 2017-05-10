//Fills and copies structs in an easy way
//Use debug mode to check str1 and 2 contents
#include <iostream>
//#pragma warning(disable:4996)

using namespace std;

typedef short t_arr[6][7];

t_arr coef2 = {
	{ 72, 5, 93, 34, 1280, 720, 1280 },
	{ 72, 5, 110, 14, 1280, 720, 704 },
	{ 72, 5, 93, 10, 1280, 720, 0 },
	{ 75, 5, 110, 14, 1280, 720, 704 },
	{ 65, 5, 115, 15, 1280, 720, 1280 },  //too much error
	{ 75, 5, 110, 14, 1280, 720, 0 }   //to be calculated with 3308
};

short coefs_bcp[][7] = {
	{ 72, 5, 93, 34, 1280, 720, 1280 },
	{ 72, 5, 110, 14, 1280, 720, 704 },
	{ 72, 5, 93, 10, 1280, 720, 0 },
	{ 75, 5, 110, 14, 1280, 720, 704 },
	{ 65, 5, 115, 15, 1280, 720, 1280 },  //too much error
	{ 75, 5, 110, 14, 1280, 720, 0 }   //to be calculated with 3308
};


void imprimematriz(short** dir2)
{
	cout << "This is the imprimematriz" << endl;
	int i, j;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 7; j++)
			cout << dir2[i][j] << " \t";
		cout << endl;
	}
}

void imprimematriz2(t_arr dir2)
{
	cout << "This is the imprimematriz" << endl;
	int i, j;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 7; j++)
			cout << dir2[i][j] << " \t";
		cout << endl;
	}
}

void imprimematriz3(short dir2[][7])
{
	cout << "This is the imprimematriz" << endl;
	int i, j;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 7; j++)
			cout << dir2[i][j] << " \t";
		cout << endl;
	}
}


int main() 
{
	short **dir=new short*[6];
	int i, j;
	for (i = 0; i < 6; i++)
		dir[i] = coefs_bcp[i];
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 7; j++)
			cout << dir[i][j] << " \t";
		cout << endl;
	}
	imprimematriz(dir);
	delete dir;

	cout << endl << "And this is another way:" << endl;
	short *dir2[6];
	for (i = 0; i < 6; i++)
		dir2[i] = coefs_bcp[i];
	imprimematriz(dir2);

	
	cout << endl << "In one command but with known both bounds:" << endl;
	t_arr* ptr1 = &coef2;
	imprimematriz2(*ptr1);

	cout << endl << "In one command with unknown second bound but not one time assigment is done:" << endl;
	imprimematriz3(coefs_bcp);


	cout << "=== END ===" << endl;
	getchar();
	return 1;
}
