/*The function colorwheel generates  a three color combinations with respect a x value.
It is assigned:
x=0  then bgr  = greeen
x=0.5 then bgr = white
x=1.0 then bgr = red
*/
#include <iostream>
#include <chrono>
#include <thread>  //usleep
#pragma warning(disable:4996) //o cualquier otro 
typedef unsigned char uchar;
#define INLIMIT3(x,xmin,xmax) ( (x)<(xmin) ? (xmin) : ((x)<=(xmax) ? (x) : (xmax)    ))     //OJO: ASIGNO max no max-1!!!

using namespace std;

//if x=0 bgr=red, if x=0.5 bgr=white, if x=1.0 bgr=green
//See "Color en funcion de la densidad de trafico.xlsm funcion Colorize5!!
//xmax2=double of xmax
//Javier Lopez
void colorwheel(float x, uchar bgr_out[], float xmax2)
{
	x = 0.5f + x / xmax2;
	if (x < 0.0f) x = 0.0f;
	else if (x>1.0f) x = 1.0f;
	bgr_out[0] = (uchar)(510.0f * (0.5 - abs(x - 0.5f)));
	bgr_out[1] = (x < 0.500f) ? 255 : (uchar)(510.0f*(1.0f - x));
	bgr_out[2] = (x > 0.499f) ? 255 : (uchar)(510.0f*x);
}

void colorwheel2(float x, uchar bgr_out[])
{
	bgr_out[0] = (uchar)(510.0f * (0.5 - abs(x - 0.5f)));
	bgr_out[1] = (x < 0.500f) ? 255 : (uchar)(510.0f*(1.0f - x));
	bgr_out[2] = (x > 0.499f) ? 255 : (uchar)(510.0f*x);
}

int main(int argc, char *argv[])
{
	float x;
	uchar bgr[3];
	/*
	x = 0.0000f; colorwheel2(x, bgr); printf("%.4f %03i %03i %03i \n", x,bgr[0], bgr[1], bgr[2]);
	x = 0.1666f; colorwheel2(x, bgr); printf("%.4f %03i %03i %03i \n", x,bgr[0], bgr[1], bgr[2]);
	x = 0.3333f; colorwheel2(x, bgr); printf("%.4f %03i %03i %03i \n", x,bgr[0], bgr[1], bgr[2]);
	x = 0.4959f; colorwheel2(x, bgr); printf("%.4f %03i %03i %03i \n", x,bgr[0], bgr[1], bgr[2]);
	x = 0.5000f; colorwheel2(x, bgr); printf("%.4f %03i %03i %03i \n", x,bgr[0], bgr[1], bgr[2]);
	x = 0.5040f; colorwheel2(x, bgr); printf("%.4f %03i %03i %03i \n", x,bgr[0], bgr[1], bgr[2]);
	x = 0.6666f; colorwheel2(x, bgr); printf("%.4f %03i %03i %03i \n", x,bgr[0], bgr[1], bgr[2]);
	x = 0.8333f; colorwheel2(x, bgr); printf("%.4f %03i %03i %03i \n", x,bgr[0], bgr[1], bgr[2]);
	x = 1.0000f; colorwheel2(x, bgr); printf("%.4f %03i %03i %03i \n", x,bgr[0], bgr[1], bgr[2]);
	x = 0.4981f; colorwheel2(x, bgr); printf("%.4f %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = 0.4961f; colorwheel2(x, bgr); printf("%.4f %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = 0.5019f; colorwheel2(x, bgr); printf("%.4f %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = 0.5039f; colorwheel2(x, bgr); printf("%.4f %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = 0.0020f; colorwheel2(x, bgr); printf("%.4f %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = 0.0040f; colorwheel2(x, bgr); printf("%.4f %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = 0.9980f; colorwheel2(x, bgr); printf("%.4f %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = 0.9960f; colorwheel2(x, bgr); printf("%.4f %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	*/
	float xmax2 = 200.0f;
	x = -150.0f;colorwheel(x, bgr, xmax2); printf("%6.3f  \t %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = -100.0f;colorwheel(x, bgr, xmax2); printf("%6.3f  \t %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = -95.00f;colorwheel(x, bgr, xmax2); printf("%6.3f  \t %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = -75.00f;colorwheel(x, bgr, xmax2); printf("%6.3f  \t %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = -50.00f;colorwheel(x, bgr, xmax2); printf("%6.3f  \t %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = -25.00f;colorwheel(x, bgr, xmax2); printf("%6.3f  \t %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = -5.000f;colorwheel(x, bgr, xmax2); printf("%6.3f  \t %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);

	x = 0.000f;colorwheel(x, bgr, xmax2); printf("%6.3f  \t %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);

	x = 5.000f;colorwheel(x, bgr, xmax2); printf("%6.3f  \t %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = 25.00f;colorwheel(x, bgr, xmax2); printf("%6.3f  \t %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = 50.00f;colorwheel(x, bgr, xmax2); printf("%6.3f  \t %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = 75.00f;colorwheel(x, bgr, xmax2); printf("%6.3f  \t %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = 95.00f;colorwheel(x, bgr, xmax2); printf("%6.3f  \t %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = 100.0f;colorwheel(x, bgr, xmax2); printf("%6.3f  \t %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);
	x = 150.0f;colorwheel(x, bgr, xmax2); printf("%6.3f  \t %03i %03i %03i \n", x, bgr[0], bgr[1], bgr[2]);

	getchar();
}