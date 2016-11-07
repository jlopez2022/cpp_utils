#include <iostream>
#include <string.h>
#define PI2 1.5707963267948966192313216916398 //pi/2



using namespace std;

//#aux2
void matriz_vector_mul(double zyx[3][3], double in[], double out[]);

//rotar vector x alrededor del vector u un angulo dado  x[0]=x,x[1]=y,x[2]=z   !!!!!!
void rotate(double *x, double *u, double angle, double *x2);

//#aux3 Rota vector "in" alrededor de 3 angulos, primero rota alrededor del eje x,luego y, luego z
void rotatexyz(double a[], double in[], double out[]);   //a(z,y,x) ,in(z,y,x)  . Angulos en radianes
//#aux4 a[i]=0,1,2 0=no timon, 1=timon arriba o derecha, 2=timon abajo o izquierda
void rotateyx(double a[], double in[], double out[]);   //a(_,y,x) ,in(z,y,x)
//Rota yaw, pitch (en ese orden):
void rotateyz(double a[], double in[], double out[]);   //a(z,y,0) ,in(z,y,x)   Rotar segun a(yaw,pitch,0)
//#aux5
void rotate_x(double a, double in[], double out[]);
//#aux6 Rota vector "in" alrededor del eje y un angulo "a":
void rotate_y(double a, double in[], double out[]);
//#aux7 Rota vector "in" alrededor del eje z un angulo "a":
void rotate_z(double a, double in[], double out[]);
//#aux9
double dotproduct(double a[], double b[]) { return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]); }
void set0(double a[]) { a[0] = a[1] = a[2] = 0.0; }
void copy(double dest[], double ori[]) { memcpy(dest, ori, 3 * sizeof(double)); }

double hallaerror(double a[], double b[]) { return (fabs(a[0] - b[0]) + fabs(a[1] - b[1]) + fabs(a[2] - b[2])) / (fabs(a[0] + b[0]) + fabs(a[1] + b[1]) + fabs(a[2] + b[2])); }
void avisaerror(double a[], double b[]) { if (hallaerror(a, b) > 1e-7) cout << " FAIL" << endl; else cout << " OK!" << endl; }

void test_rotations();

void main()
{
	test_rotations();
	cout << "=================== END ======================" << endl << endl;
	getchar(); getchar();
}



//#aux2
void matriz_vector_mul(double zyx[3][3], double in[], double out[])
{
	out[0] = in[0] * zyx[0][0] + in[1] * zyx[0][1] + in[2] * zyx[0][2];
	out[1] = in[0] * zyx[1][0] + in[1] * zyx[1][1] + in[2] * zyx[1][2];
	out[2] = in[0] * zyx[2][0] + in[1] * zyx[2][1] + in[2] * zyx[2][2];
}
//#aux3
void rotatexyz(double a[], double in[], double out[])   //a(z,y,x) ,in(z,y,x)  . Angulos en radianes
{
	double Cx = cos(a[0]), Cy = cos(a[1]), Cz = cos(a[2]);
	double Sx = sin(a[0]), Sy = sin(a[1]), Sz = sin(a[2]);

	double zyx[3][3] = {
		{	Cy*Cz      , -Sz*Cx-Cz*Sy*Sx  ,	 Sz*Sx  -Cz*Sy*Cx   },
		{	Sz*Cy      ,  Cz*Cx - Sz*Sy*Sx,	-Cz*Sx - Sz*Sy*Cx	},
		{	Sy  ,		  Cy*Sx           ,  Cy*Cx} };
		/*
		//{  Cy*Cz,  Sx*Sy*Cz + Sz*Cx,  Cx*Sy*Cz - Sx*Sz },
		//{ -Cy*Sz, -Sx*Sy*Sz + Cx*Cz, -Cx*Sy*Sz - Sx*Cz },
		//{ -Sy,     Sx*Cy, Cx*Cy } };

		{	Cy*Cz, Sz*Cx ,- Cz*Sy  },
		{	Sz*Cy*Cx - Sy*Sx, Cz*Cx, -Sz*Sy*Cx - Cy*Sx },
		{	Sz*Cy*Sx+Sx*Cx,Cz*Sx,-Sz*Sy*Sx+Cy*Cx} };
				  */

	matriz_vector_mul(zyx, in, out);
}
//#aux4
void rotateyx(double a[], double in[], double out[])   //a(x,y,z) ,in(x,y,z)   a(roll,pitch,-)
{
	double Cx = cos(a[0]), Cy = cos(a[1]);
	double Sx = sin(a[0]), Sy = sin(a[1]);

	double yx[3][3] = {
		{ Cy , -Sx*Sy, -Cx*Sy },
		{ 0.0,  Cx,    -Sx },
		{ Sy ,  Sx*Cy,  Cx*Cy } };

	matriz_vector_mul(yx, in, out);
}

void rotateyz(double a[], double in[], double out[])   //a(0,y,z) ,in(x,y,z)   Rotar segun a(0,yaw,pitch)
{
	double Cy = cos(a[1]), Cz = cos(a[2]);
	double Sy = sin(a[1]), Sz = sin(a[2]);

	double zy[3][3] = {
		{Cy*Cz,-Sz, -Cz*Sy  },
		{Sz*Cy, Cz, -Sz*Sy  },
		{ Sy,   0,     Cy } };
	matriz_vector_mul(zy, in, out);
}
//#aux5 = roll
void rotate_x(double a, double in[], double out[])
{
	double Cx = cos(a), Sx = sin(a);
	double x[3][3] = {
		{ 1.0, 0,   0 },
		{ 0,   Cx, -Sx },
		{ 0,   Sx,  Cx } };
	matriz_vector_mul(x, in, out);
}
//#aux6 pitch
void rotate_y(double a, double in[], double out[])
{
	double Cy = cos(a), Sy = sin(a);
	double x[3][3] = {
		{ Cy, 0, -Sy },
		{ 0, 1.0, 0 },
		{ Sy, 0, Cy } };
	matriz_vector_mul(x, in, out);
}
//#aux7  yaw
void rotate_z(double a, double in[], double out[])
{
	double Cz = cos(a), Sz = sin(a);
	double x[3][3] = {
		{ Cz, -Sz, 0 },
		{ Sz, Cz, 0 },
		{ 0, 0, 1.0 } };
	matriz_vector_mul(x, in, out);
}














void test_rotations()
{
	long i = 0;
	double angle[3];
	double out[3];

	{
		cout << "\nTest de rotacion de varias matrices:" << endl;
		double out1[3], out2[3], out3[3], aux[3];
		double nxyz[3] = { 0.15, -0.25, 0.31 };
		double angle[3] = { 0, -0.33, 0.11 };//a(x,y,z) = roll=0,yaw=-0.3, pitch=0.15
		long test = 0;

		rotateyz(angle, nxyz, out1);
		rotatexyz(angle, nxyz, out2);
		rotate_y(angle[1], nxyz, aux);
		rotate_z(angle[2], aux, out3);
		//rotate_z(angle[2], nxyz, aux);
		//rotate_y(angle[1], aux, out3);
		cout << "Test:" << test++; avisaerror(out1, out2);
		cout << "Test:" << test++; avisaerror(out1, out3);

		nxyz[0] = -nxyz[0];
		rotateyz(angle, nxyz, out1);
		rotatexyz(angle, nxyz, out2);
		rotate_y(angle[1], nxyz, aux);
		rotate_z(angle[2], aux, out3);
		cout << "Test:" << test++; avisaerror(out1, out2);
		cout << "Test:" << test++; avisaerror(out1, out3);
		angle[2] = -angle[2];
		rotateyz(angle, nxyz, out1);
		rotatexyz(angle, nxyz, out2);
		rotate_y(angle[1], nxyz, aux);
		rotate_z(angle[2], aux, out3);
		cout << "Test:" << test++; avisaerror(out1, out2);
		cout << "Test:" << test++; avisaerror(out1, out3);

		nxyz[1] = -nxyz[1];
		rotateyz(angle, nxyz, out1);
		rotatexyz(angle, nxyz, out2);
		rotate_y(angle[1], nxyz, aux);
		rotate_z(angle[2], aux, out3);
		cout << "Test:" << test++; avisaerror(out1, out2);
		cout << "Test:" << test++; avisaerror(out1, out3);
		angle[1] = -angle[1];
		rotateyz(angle, nxyz, out1);
		rotatexyz(angle, nxyz, out2);
		rotate_y(angle[1], nxyz, aux);
		rotate_z(angle[2], aux, out3);
		cout << "Test:" << test++; avisaerror(out1, out2);
		cout << "Test:" << test++; avisaerror(out1, out3);
		cout << endl;

		double aux2[3];
		angle[0] = 0.22;
		rotatexyz(angle, nxyz, out2);
		rotate_x(angle[0], nxyz, aux);
		rotate_y(angle[1], aux, aux2);
		rotate_z(angle[2], aux2, out3);
		cout << "Test:" << test++; avisaerror(out2, out3);

		angle[0] = -angle[0];
		rotatexyz(angle, nxyz, out2);
		rotate_x(angle[0], nxyz, aux);
		rotate_y(angle[1], aux, aux2);
		rotate_z(angle[2], aux2, out3);
		cout << "Test:" << test++; avisaerror(out2, out3);
		nxyz[0] = -nxyz[0];
		rotatexyz(angle, nxyz, out2);
		rotate_x(angle[0], nxyz, aux);
		rotate_y(angle[1], aux, aux2);
		rotate_z(angle[2], aux2, out3);
		cout << "Test:" << test++; avisaerror(out2, out3);

		angle[1] = -angle[1];
		rotatexyz(angle, nxyz, out2);
		rotate_x(angle[0], nxyz, aux);
		rotate_y(angle[1], aux, aux2);
		rotate_z(angle[2], aux2, out3);
		cout << "Test:" << test++; avisaerror(out2, out3);
		nxyz[1] = -nxyz[1];
		rotatexyz(angle, nxyz, out2);
		rotate_x(angle[0], nxyz, aux);
		rotate_y(angle[1], aux, aux2);
		rotate_z(angle[2], aux2, out3);
		cout << "Test:" << test++; avisaerror(out2, out3);

		angle[2] = -angle[2];
		rotatexyz(angle, nxyz, out2);
		rotate_x(angle[0], nxyz, aux);
		rotate_y(angle[1], aux, aux2);
		rotate_z(angle[2], aux2, out3);
		cout << "Test:" << test++; avisaerror(out2, out3);
		nxyz[2] = -nxyz[2];
		rotatexyz(angle, nxyz, out2);
		rotate_x(angle[0], nxyz, aux);
		rotate_y(angle[1], aux, aux2);
		rotate_z(angle[2], aux2, out3);
		cout << "Test:" << test++; avisaerror(out2, out3);


		cout << endl;


		i = i;
	}

	{
		double nxyz[3] = { 1.0 / sqrt(2.0), 1.0 / sqrt(2.0), 0 };
		double pxyz[3] = { 1.0 / sqrt(3.0), 1.0 / sqrt(3.0), 1.0 / sqrt(3.0) };
		set0(angle); angle[0] = angle[1] = PI2; rotatexyz(angle, nxyz, out);
		set0(angle); angle[1] = angle[2] = PI2; rotatexyz(angle, nxyz, out);
		i = i;
	}
	{
		double nxyz[3] = { 1.0, 0, 0 };
		double a = PI2;
		cout << "nxyz:" << nxyz[0] << " " << nxyz[1] << " " << nxyz[2] << endl;
		rotate_x(a, nxyz, out); cout << "roll  x:" << out[0] << " " << out[1] << " " << out[2] << endl;
		//Ojo:yaw gira al reves:
		rotate_y(-a, nxyz, out); cout << "yaw   y:" << out[0] << " " << out[1] << " " << out[2] << endl;
		rotate_z(a, nxyz, out); cout << "pitch z:" << out[0] << " " << out[1] << " " << out[2] << endl;
		i = i;
	}
	{
		double nxyz[3] = { 1.0, 1.0, 0 };
		double a = PI2;
		double angle[3] = { 0, 0, 0 };
		cout << endl << "nxyz:" << nxyz[0] << " " << nxyz[1] << " " << nxyz[2] << endl;

		rotate_x(a, nxyz, out); cout << "roll  x:" << out[0] << " " << out[1] << " " << out[2] << endl;
		angle[0] = a; rotatexyz(angle, nxyz, out); angle[0] = 0;
		cout << "roll  x:" << out[0] << " " << out[1] << " " << out[2] << endl;

		//Ojo:yaw gira al reves:
		rotate_y(a, nxyz, out); cout << "yaw   y:" << out[0] << " " << out[1] << " " << out[2] << endl;
		angle[1] = a; rotatexyz(angle, nxyz, out); angle[1] = 0;
		cout << "yaw   y:" << out[0] << " " << out[1] << " " << out[2] << endl;

		rotate_z(a, nxyz, out); cout << "pitch z:" << out[0] << " " << out[1] << " " << out[2] << endl;
		angle[2] = a; rotatexyz(angle, nxyz, out); angle[2] = 0;
		cout << "pitch z:" << out[0] << " " << out[1] << " " << out[2] << endl;

		i = i;
	}



	cout << endl << endl;

}