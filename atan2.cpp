//The advantage using atan2() over atan() is that atan2 takes in account the cuadrant of the angle
#include <iostream>
#include <string.h>
#define PI2 1.5707963267948966192313216916398 //pi/2
#define PI180 0.01745329251994329576923690768489  //pi/180

//VER: http://msl.cs.uiuc.edu/planning/node102.html  "planning algorithms" donde  alfa=z    beta=y    gamma=x

using namespace std;


void main()
{
	double angledeg,angle1,angle2, x, y,h=10;

	angledeg = 10; angle1 = angledeg*PI180; y = h*sin(angle1); x = h*cos(angle1); angle2 = atan2(y, x); cout << "Angulo 1 y 2 = " << angle1 << " " << angle2 << endl;  //primer cuadrante
	angledeg = 115; angle1 = angledeg*PI180; y = h*sin(angle1); x = h*cos(angle1); angle2 = atan2(y, x); cout << "Angulo 1 y 2 = " << angle1 << " " << angle2 << endl;  //segundo cuadrante
	angledeg = -10; angle1 = angledeg*PI180; y = h*sin(angle1); x = h*cos(angle1); angle2 = atan2(y, x); cout << "Angulo 1 y 2 = " << angle1 << " " << angle2 << endl;  //cuarto cuadrante
	angledeg = -115; angle1 = angledeg*PI180; y = h*sin(angle1); x = h*cos(angle1);  angle2 = atan2(y, x); cout << "Angulo 1 y 2 = " << angle1 << " " << angle2 << endl;  //tercer cuadrante


	cout << "=================== END ======================" << endl << endl;
	getchar(); getchar();
}

