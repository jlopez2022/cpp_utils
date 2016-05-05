#include <stdio.h>
#include <string.h>
//Meter en C/C++ > Preprocessor > Preprocessor Definitions poner _CRT_SECURE_NO_WARNINGS
//También vale:
#pragma warning(disable:4996) //o cualquier otro 



int main ()
{
	char linea[1024];
	strcpy(linea,"prueba de copia");
	printf("\n%s \nFIN",linea);
	getchar();getchar();
	return 0;
}