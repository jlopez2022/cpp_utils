#include <iostream>
#include <string.h>
#define PI2 1.5707963267948966192313216916398 //pi/2
#define PI180 0.01745329251994329576923690768489 



using namespace std;

//#aux2
void matriz_vector_mul(double zyx[3][3], double in[], double out[]);

//#aux3 Rotacion de un vector con respecto de un eje arbitrario un angulo dado:
void divmodule(double v[3], double z[3]);
//rotar vector x alrededor del vector u un angulo dado  x[0]=x,x[1]=y,x[2]=z
void rotate(double *x, double *u, double angle, double *x2);

//#aux4 Otra forma de rotar, primero halla la matriz de rotacion y luego la usa. La ventaja es que si se aplica a muchos puntos tardara menos:
void setUpRotationMatrix(double angle, double rotation_axis[3], double rotationMatrix[3][3]);
void rotate2(double vector_in[3], double rotationMatrix[3][3], double vector_out[3]);

//#aux5 Rota vector "in" alrededor de 3 angulos, primero rota alrededor del eje x,luego y, luego z
void rotatexyz(double a[], double in[], double out[]);   //a(z,y,x) ,in(z,y,x)  . Angulos en radianes
//#aux6 a[i]=0,1,2 0=no timon, 1=timon arriba o derecha, 2=timon abajo o izquierda
void rotateyx(double a[], double in[], double out[]);   //a(_,y,x) ,in(z,y,x)
//#aux7 Rota yaw, pitch (en ese orden):
void rotateyz(double a[], double in[], double out[]);   //a(z,y,0) ,in(z,y,x)   Rotar segun a(yaw,pitch,0)
//#aux8
void rotate_x(double a, double in[], double out[]);
//#aux9 Rota vector "in" alrededor del eje y un angulo "a":
void rotate_y(double a, double in[], double out[]);
//#aux10 Rota vector "in" alrededor del eje z un angulo "a":
void rotate_z(double a, double in[], double out[]);
//#aux11
double dotproduct(double a[], double b[]) { return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]); }
void set0(double a[]) { a[0] = a[1] = a[2] = 0.0; }
void copy(double dest[], double ori[]) { memcpy(dest, ori, 3 * sizeof(double)); }

double hallaerror(double a[], double b[]) { return (fabs(a[0] - b[0]) + fabs(a[1] - b[1]) + fabs(a[2] - b[2])) / (fabs(a[0] + b[0]) + fabs(a[1] + b[1]) + fabs(a[2] + b[2])); }
void avisaerror(double a[], double b[]) { if (hallaerror(a, b) > 1e-7) cout << " FAIL" << endl; else cout << " OK!" << endl; }

double check_error(double *u, double *v){ double err = (fabs(u[0] - v[0]) + fabs(u[1] - v[1]) + fabs(u[2] - v[2])); double val = (fabs(u[0] + v[0]) + fabs(u[1] + v[1]) + fabs(u[2] + v[2])); return (err / val); }
double check_error2(double *u, double *v){ double err = (fabs(u[0] - v[0]) + fabs(u[1] - v[1]) + fabs(u[2] - v[2])); double val = (fabs(u[0] + v[0]) + fabs(u[1] + v[1]) + fabs(u[2] + v[2])); if (err / val < 1e-5) cout << " OK!!" << endl; else cout << " FAIL!!" << endl; return (err / val); }

void test_rotation1();
void test_rotation2();

void main()
{
	test_rotation1();
	test_rotation2();
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

void divmodule(double v[3], double z[3]) { double k = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]); if (k < 1e-30) { v[0] = k = 1.0; } z[0] = v[0] / k; z[1] = v[1] / k; z[2] = v[2] / k; }
//rotar vector x alrededor del vector u un angulo dado  x[0]=x,x[1]=y,x[2]=z
void rotate(double *x, double *rotating_axis, double angle, double *x2)
{
	double u[3];
	divmodule(rotating_axis, u);
	double ux = u[0] * x[0];
	double uy = u[0] * x[1];
	double uz = u[0] * x[2];
	double vx = u[1] * x[0];
	double vy = u[1] * x[1];
	double vz = u[1] * x[2];
	double wx = u[2] * x[0];
	double wy = u[2] * x[1];
	double wz = u[2] * x[2];
	double sa = sin(angle);
	double ca = cos(angle);
	x2[0] = u[0] * (ux + vy + wz) + (x[0] * (u[1] * u[1] + u[2] * u[2]) - u[0] * (vy + wz))*ca + (-wy + vz)*sa;
	x2[1] = u[1] * (ux + vy + wz) + (x[1] * (u[0] * u[0] + u[2] * u[2]) - u[1] * (ux + wz))*ca + (wx - uz)*sa;
	x2[2] = u[2] * (ux + vy + wz) + (x[2] * (u[0] * u[0] + u[1] * u[1]) - u[2] * (ux + vy))*ca + (-vx + uy)*sa;
}

//#aux4 
void setUpRotationMatrix(double angle, double rotation_axis[3], double rotationMatrix[3][3])
{
	double u = rotation_axis[0], v = rotation_axis[1], w = rotation_axis[2];
	double L = (u*u + v * v + w * w);
	//angle = angle * M_PI / 180.0; //converting to radian value
	double u2 = u * u;
	double v2 = v * v;
	double w2 = w * w;

	rotationMatrix[0][0] = (u2 + (v2 + w2) * cos(angle)) / L;
	rotationMatrix[0][1] = (u * v * (1 - cos(angle)) - w * sqrt(L) * sin(angle)) / L;
	rotationMatrix[0][2] = (u * w * (1 - cos(angle)) + v * sqrt(L) * sin(angle)) / L;

	rotationMatrix[1][0] = (u * v * (1 - cos(angle)) + w * sqrt(L) * sin(angle)) / L;
	rotationMatrix[1][1] = (v2 + (u2 + w2) * cos(angle)) / L;
	rotationMatrix[1][2] = (v * w * (1 - cos(angle)) - u * sqrt(L) * sin(angle)) / L;

	rotationMatrix[2][0] = (u * w * (1 - cos(angle)) - v * sqrt(L) * sin(angle)) / L;
	rotationMatrix[2][1] = (v * w * (1 - cos(angle)) + u * sqrt(L) * sin(angle)) / L;
	rotationMatrix[2][2] = (w2 + (u2 + v2) * cos(angle)) / L;
}
void rotate2(double vector_in[3], double rotationMatrix[3][3], double vector_out[3])
{
	for (int i = 0; i < 3; i++)
	{
		vector_out[i] = 0;
		for (int k = 0; k < 3; k++)
		{
			vector_out[i] += rotationMatrix[i][k] * vector_in[k];
		}
	}
}

//#aux5
void rotatexyz(double a[], double in[], double out[])   //a(z,y,x) ,in(z,y,x)  . Angulos en radianes
{
	double Cx = cos(a[0]), Cy = cos(a[1]), Cz = cos(a[2]);
	double Sx = sin(a[0]), Sy = sin(a[1]), Sz = sin(a[2]);

	double zyx[3][3] = {
		{	Cy*Cz      , -Sz*Cx-Cz*Sy*Sx  ,	 Sz*Sx  -Cz*Sy*Cx   },
		{	Sz*Cy      ,  Cz*Cx - Sz*Sy*Sx,	-Cz*Sx - Sz*Sy*Cx	},
		{	Sy  ,		  Cy*Sx           ,  Cy*Cx} };

	matriz_vector_mul(zyx, in, out);
}
//#aux6
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
//#aux7
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
//#aux8 = roll
void rotate_x(double a, double in[], double out[])
{
	double Cx = cos(a), Sx = sin(a);
	double x[3][3] = {
		{ 1.0, 0,   0 },
		{ 0,   Cx, -Sx },
		{ 0,   Sx,  Cx } };
	matriz_vector_mul(x, in, out);
}
//#aux9 pitch
void rotate_y(double a, double in[], double out[])
{
	double Cy = cos(a), Sy = sin(a);
	double x[3][3] = {
		{ Cy, 0, -Sy },
		{ 0, 1.0, 0 },
		{ Sy, 0, Cy } };
	matriz_vector_mul(x, in, out);
}
//#aux10  yaw
void rotate_z(double a, double in[], double out[])
{
	double Cz = cos(a), Sz = sin(a);
	double x[3][3] = {
		{ Cz, -Sz, 0 },
		{ Sz, Cz, 0 },
		{ 0, 0, 1.0 } };
	matriz_vector_mul(x, in, out);
}











void test_rotation1()
{
	double rotationMatrix[3][3];
	double inputMatrix[4] = { 0.0, 0.0, 0.0, 0.0 };
	double outputMatrix[4] = { 0.0, 0.0, 0.0, 0.0 };

	double x2[4], x3[4];  //4 en vez de 3 para pruebas
	double a;
	{
		double x[4] = { 10, 10, 0, 1.0 };   //1.0 al final se emplea para pruebas
		double u[3] = { 1, 0, 0 };
		printf("Rotation axis=%4lg %4lg %4lg \n", u[0], u[1], u[2]);
		a = 45 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		setUpRotationMatrix(a, u, rotationMatrix);
		rotate2(x, rotationMatrix, x3);   check_error2(x2, x3);

		a = 90 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		setUpRotationMatrix(a, u, rotationMatrix);
		rotate2(x, rotationMatrix, x3);    check_error2(x2, x3);

		x[0] = 0; x[2] = 10;
		a = 45 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		setUpRotationMatrix(a, u, rotationMatrix);
		rotate2(x, rotationMatrix, x3);    check_error2(x2, x3);

		a = 90 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		setUpRotationMatrix(a, u, rotationMatrix);
		rotate2(x, rotationMatrix, x3);    check_error2(x2, x3);

		x[0] = 0; x[1] = 10; x[2] = 0;
		a = 45 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		setUpRotationMatrix(a, u, rotationMatrix);
		rotate2(x, rotationMatrix, x3);    check_error2(x2, x3);
		a = 90 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		setUpRotationMatrix(a, u, rotationMatrix);
		rotate2(x, rotationMatrix, x3);    check_error2(x2, x3);
	}
	{
		double x[3] = { 13.5, 23.2, 15.0 };
		double rotation_axis1[3] = { 15.2, 13, -14 };//rotation axis
		inputMatrix[0] = x[0]; inputMatrix[1] = x[1]; inputMatrix[2] = x[2]; inputMatrix[3] = 1.0;
		a = 133.5*PI180;
		rotate(x, rotation_axis1, a, x2);
		setUpRotationMatrix(a, rotation_axis1, rotationMatrix);
		rotate2(inputMatrix, rotationMatrix, outputMatrix);
		cout << "TEST 1: error=" << check_error(x2, outputMatrix) << endl;
	}


	{
		double x[3] = { 10, 10, 0 };
		double u[3] = { 0, 1, 0 };
		printf("Rota axes=%14lg %14lg %14lg \n", u[0], u[1], u[2]);
		a = 45 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		setUpRotationMatrix(a, u, rotationMatrix); 	rotate2(x, rotationMatrix, x3);   check_error2(x2, x3);
		a = 90 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		setUpRotationMatrix(a, u, rotationMatrix); 	rotate2(x, rotationMatrix, x3);   check_error2(x2, x3);
		x[0] = 0; x[2] = 10;
		a = 45 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		setUpRotationMatrix(a, u, rotationMatrix); 	rotate2(x, rotationMatrix, x3);   check_error2(x2, x3);
		a = 90 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		setUpRotationMatrix(a, u, rotationMatrix); 	rotate2(x, rotationMatrix, x3);   check_error2(x2, x3);
	}
	{
		double x[3] = { 10, 10, 0 };
		double u[3] = { 0, 0, 1 };
		printf("Rota axes=%14lg %14lg %14lg \n", u[0], u[1], u[2]);
		a = 45 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		setUpRotationMatrix(a, u, rotationMatrix); 	rotate2(x, rotationMatrix, x3);   check_error2(x2, x3);
		a = 90 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		setUpRotationMatrix(a, u, rotationMatrix); 	rotate2(x, rotationMatrix, x3);   check_error2(x2, x3);
		x[0] = 0; x[2] = 10;
		a = 45 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		setUpRotationMatrix(a, u, rotationMatrix); 	rotate2(x, rotationMatrix, x3);   check_error2(x2, x3);
		a = 90 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		setUpRotationMatrix(a, u, rotationMatrix); 	rotate2(x, rotationMatrix, x3);   check_error2(x2, x3);
	}
	{
		double x[3] = { 10, 10, 0 };
		double u[3] = { 1, 1, 0 };
		printf("Rota axes=%14lg %14lg %14lg \n", u[0], u[1], u[2]);
		u[0] = 1; u[1] = 1; u[2] = 0; a = 45 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		u[0] = 1; u[1] = 1; u[2] = 0; setUpRotationMatrix(a, u, rotationMatrix); 	rotate2(x, rotationMatrix, x3);   check_error2(x2, x3);
		u[0] = 1; u[1] = 1; u[2] = 0; a = 90 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		u[0] = 1; u[1] = 1; u[2] = 0; setUpRotationMatrix(a, u, rotationMatrix); 	rotate2(x, rotationMatrix, x3);   check_error2(x2, x3);
		x[0] = 0; x[2] = 10;
		u[0] = 1; u[1] = 1; u[2] = 0; a = 45 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		u[0] = 1; u[1] = 1; u[2] = 0; setUpRotationMatrix(a, u, rotationMatrix); 	rotate2(x, rotationMatrix, x3);   check_error2(x2, x3);
		u[0] = 1; u[1] = 1; u[2] = 0; a = 90 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		u[0] = 1; u[1] = 1; u[2] = 0; setUpRotationMatrix(a, u, rotationMatrix); 	rotate2(x, rotationMatrix, x3);   check_error2(x2, x3);
	}
	{
		double x[3] = { 10, 10, 0 };
		double u[3] = { 0, 1, 1 };
		printf("Rota axes=%14lg %14lg %14lg \n", u[0], u[1], u[2]);
		u[0] = 0; u[1] = 1; u[2] = 1; a = 45 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		u[0] = 0; u[1] = 1; u[2] = 1; setUpRotationMatrix(a, u, rotationMatrix); 	rotate2(x, rotationMatrix, x3);   check_error2(x2, x3);
		u[0] = 0; u[1] = 1; u[2] = 1; a = 90 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		u[0] = 0; u[1] = 1; u[2] = 1; setUpRotationMatrix(a, u, rotationMatrix); 	rotate2(x, rotationMatrix, x3);   check_error2(x2, x3);
		x[0] = 0; x[2] = 10;
		u[0] = 0; u[1] = 1; u[2] = 1; a = 45 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		u[0] = 0; u[1] = 1; u[2] = 1; setUpRotationMatrix(a, u, rotationMatrix); 	rotate2(x, rotationMatrix, x3);   check_error2(x2, x3);
		u[0] = 0; u[1] = 1; u[2] = 1; a = 90 * PI180; 	rotate(x, u, a, x2); printf("xyz=%14lg %14lg %14lg angle=%14lg xyz2=%14lg %14lg %14lg", x[0], x[1], x[2], a / PI180, x2[0], x2[1], x2[2]);
		u[0] = 0; u[1] = 1; u[2] = 1; setUpRotationMatrix(a, u, rotationMatrix); 	rotate2(x, rotationMatrix, x3);   check_error2(x2, x3);
	}

	cout << "=============FIN===================" << endl; getchar(); getchar();
}





void test_rotation2()
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