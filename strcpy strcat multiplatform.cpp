// strcpy and strcat microsoft compatible
#include <iostream>
//#pragma warning(disable:4996) not needed!!

using namespace std;

//secure string copy:
void s_strncpy(char *dest, char *source, int sizemax)
{
	for (int i = 0; i < sizemax; i++)
	{
		dest[i] = source[i];
		if (source[i] == '\0') return;
	}
	cout << "Warning sizemax reached at s_strncpy()" << endl;
	dest[sizemax - 1] = '\0';//To place the null at the end
}

void strcpy1(char *ptr1, char *ptr2, int max=1023)
{
	int i;
	for (i = 0; i < max; i++)
	{
		*ptr1++ = *ptr2++;
		if (!*ptr2) break;
	}
	*ptr1 = '\0';
}

void strcat1(char *ptr1, char *str2, int max = 1023)
{
	int i;
	//finds str1 end:
	for (i = 0; i < max; i++)
	{
		if (!*ptr1)
			break;
		ptr1++;
	}
	strcpy1(ptr1, str2, max);
}



int main() 
{
	char str1[1024];
	char str2[] = "This is the first string.";
	char str3[] = "And this is the second one.";
	strcpy1(str1, str2, 1024);
	cout << "First  string= #" << str1 << "#" << endl;
	strcat1(str1, str3,1024);
	cout << "Second string= #" << str1 << "#" << endl;
	cout << "=== END ===" << endl;

	char prue1[] = "Prueba de copia de caracteres hasta llegar a 0 por lo que no sirve para copiar datos", prue2[1024];
	s_strncpy(prue2, prue1, 1024);
	cout << "input =" << prue1 << endl;
	cout << "output=" << prue2 << endl;

	getchar(); 
	return 1;
}
