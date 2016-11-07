//strcpy and strcat microsof proof
#include <iostream>

void strcpy1(char *ptr1, char *ptr2, long max = 1023)
{
	for (long i = 0; i < max; i++)
		if (*ptr2)
			*ptr1++ = *ptr2++;
		else break;
		*ptr1 = '\0';
}

void strcat1(char *ptr1, char *ptr2, long max = 1023)
{
	long i;
	for (i = 0; i < max; i++)
		if (!(*ptr1++))
			break;
	if (i >= max) return;
	ptr1--;
	for (; i <= max; i++)
		if (!(*ptr1++ = *ptr2++))
			break;
	*ptr1 = '\0';
}


using namespace std;


void main()
{
	char cadena1[] = "prueba/copia/strings.txt", cadena2[1024], cadena3[1024] = "\0";
	strcpy1(cadena2, cadena1);
	strcat1(cadena3, cadena1);
	strcat1(cadena3, cadena2);
	cout << "cadena1=" << cadena1 << endl;
	cout << "cadena2=" << cadena2 << endl;
	cout << "cadena1+2=" << cadena3 << endl;

	cout << "=================== END ======================" << endl << endl;
	getchar(); getchar();
}
