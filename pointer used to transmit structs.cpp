//Transmit a struct using an array of chars. It can be used as example in data transmission using sockets
//Be careful, easily a 0 can be sent in the middle of the struct, so if the command uses the '\0' as end of the string, only part of the data is transmitted
#include <iostream>
#include <stdlib.h>
#pragma warning(disable:4996)

using namespace std;

struct t_struct
{
	char texto[100];
	float m[120];
	int size1;
};

void print_struct(t_struct str)
{
	for (long i = 0; i < str.size1; i++)
	{
		cout << str.m[i] << " \t";
	}
	cout << "\nstr.texto=" << str.texto << endl;
}


void message_sent(char *msg)
{
	t_struct str2;
	memcpy(&str2, msg, sizeof(t_struct));//size of the struct, not msg length in order to avoid the \0 problem!
	cout << "\nstr2.m=" << endl;
	print_struct(str2);
}

void main()
{
	t_struct str1;
	str1.size1 = 100;
	long struct_size = sizeof(t_struct) + 1;
	int i;
	for (i = 0; i < 100; i++)
	{
		str1.m[i] = 1000.0f + i*1.0f;
	}
	strcpy(str1.texto, "Texto a trasmitir");

	cout << "\nstr1.m=" << endl;
	print_struct(str1);

	//Sending the struct:
	message_sent((char*)&str1);
	cout << "==== END ====" << endl;
	getchar();
}

