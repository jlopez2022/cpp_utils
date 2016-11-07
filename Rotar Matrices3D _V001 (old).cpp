//ATENCION, si se rota un vector alrededor de 3 ejes: x,luego y y luego z, no es lo mismo que hacerlo en orden distinto, 
//Por eso si se rota segun angulos x,y,z=10,20,30 y luego x,y,z=-10,-20,-30 el vector no queda igual, 
//para que quedara igual habría que rotar en orden contrario: z,luego y luego x 

#include <iostream>
#define DEG_TO_RAD 0.01745329251994329576923690768489   // =pi/180
typedef unsigned char uchar;
using namespace std;

void torad(double angulo[]);  //pasa a radianes
void matriz_vector_mul(double zyx[3][3], double in[], double out[]);
void display3(double in[], double out[], double R[]); //entran angulo en radianes y salen en grados

//Rota vector "in" alrededor de 3 angulos, primero rota alrededor del eje x,luego y, luego z
void rotatezyx(double a[], double in[], double out[]);   //a(z,y,x) ,in(z,y,x)  . Angulos en radianes
//Rota vector "in" alrededor de 2 angulos, primero rota alrededor del eje x,luego y
void rotateyx(double a[], double in[], double out[]);   //a(_,y,x) ,in(z,y,x)
//Rota vector "in" alrededor del eje x un angulo "a":
void rotate_x(double a, double in[], double out[]);
//Rota vector "in" alrededor del eje y un angulo "a":
void rotate_y(double a, double in[], double out[]);
//Rota vector "in" alrededor del eje z un angulo "a":
void rotate_z(double a, double in[], double out[]);
//Mira si los vectores son iguales, en cuyo caso sale 0, si no sale -1:
int mira_error(double out[], double out2[2]);


void main()
{
	double in[3] = { 10, 15, 30 }, out[3],out2[3],o1[3],o2[3];
	double R[3];

	R[0] = -39; R[1] = 33; R[2] = -150; torad(R);
	rotateyx(R, in, out); display3(in, out,R);
	rotatezyx(R, in, out); display3(in, out, R);

	rotate_x(R[0], in, o1); rotate_y(R[1], o1, o2); rotate_z(R[2], o2, out2); mira_error(out, out2);

	R[0] = 129; R[1] = 133; R[2] = 15; torad(R);
	rotateyx(R, in, out); display3(in, out, R);
	rotatezyx(R, in, out); display3(in, out, R);

	rotate_x(R[0], in, o1); rotate_y(R[1], o1, o2); rotate_z(R[2], o2, out2); mira_error(out, out2);

	R[0] = 12; R[1] = -153; R[2] = 95; torad(R);
	rotateyx(R, in, out); display3(in, out, R);
	rotatezyx(R, in, out); display3(in, out, R);

	rotate_x(R[0], in, o1); rotate_y(R[1], o1, o2); rotate_z(R[2], o2, out2); mira_error(out, out2);

	cout << "\n\n======end========\n"; getchar(); getchar();
}


void torad(double angulo[])  //pasa a radianes
{
	angulo[0] *= DEG_TO_RAD;
	angulo[1] *= DEG_TO_RAD;
	angulo[2] *= DEG_TO_RAD;
}

void matriz_vector_mul(double zyx[3][3], double in[], double out[])
{
	out[0] = in[0] * zyx[0][0] + in[1] * zyx[0][1] + in[2] * zyx[0][2];
	out[1] = in[0] * zyx[1][0] + in[1] * zyx[1][1] + in[2] * zyx[1][2];
	out[2] = in[0] * zyx[2][0] + in[1] * zyx[2][1] + in[2] * zyx[2][2];
}

void rotatezyx(double a[], double in[], double out[])   //a(z,y,x) ,in(z,y,x)  . Angulos en radianes
{
	double Cx = cos(a[0]), Cy = cos(a[1]), Cz = cos(a[2]);
	double Sx = sin(a[0]), Sy = sin(a[1]), Sz = sin(a[2]);

	double zyx[3][3] = {
		{ Cy*Cz, -Sx*Sy*Cz + Sz*Cx, Cx*Sy*Cz + Sx*Sz },
		{ -Cy*Sz, Sx*Sy*Sz + Cx*Cz, -Cx*Sy*Sz + Sx*Cz },
		{ -Sy, -Sx*Cy, Cx*Cy } };

	matriz_vector_mul(zyx, in, out);
}


void rotateyx(double a[], double in[], double out[])   //a(_,y,x) ,in(z,y,x)
{
	double Cx = cos(a[0]), Cy = cos(a[1]);
	double Sx = sin(a[0]), Sy = sin(a[1]);

	double yx[3][3] = {
		{ Cy, -Sx*Sy, Cx*Sy },
		{ 0.0, Cx, Sx },
		{ -Sy, -Sx*Cy, Cx*Cy } };

	matriz_vector_mul(yx, in, out);
}


void rotate_x(double a, double in[], double out[])
{
	double Cx = cos(a);
	double Sx = sin(a);

	double x[3][3] = {
		{ 1.0, 0, 0 },
		{ 0, Cx, Sx },
		{ 0, -Sx, Cx } };
	matriz_vector_mul(x, in, out);
}

void rotate_y(double a, double in[], double out[])
{
	double Cy = cos(a);
	double Sy = sin(a);

	double x[3][3] = {
		{ Cy, 0, Sy },
		{ 0, 1.0, 0 },
		{ -Sy, 0, Cy } };
	matriz_vector_mul(x, in, out);
}

void rotate_z(double a, double in[], double out[])
{
	double Cz = cos(a);
	double Sz = sin(a);

	double x[3][3] = {
		{ Cz, Sz, 0 },
		{ -Sz, Cz, 0 },
		{ 0, 0, 1.0 } };
	matriz_vector_mul(x, in, out);
}


void display3(double in[], double out[], double R[]) //entran angulo en radianes y salen en grados
{
	cout << "angulos=" << R[0] / DEG_TO_RAD << " " << R[1] / DEG_TO_RAD << " " << R[2] / DEG_TO_RAD << " \t";
	cout << "IN= " << in[0] << " " << in[1] << " " << in[2] << " \tOUT= " << out[0] << " " << out[1] << " " << out[2] << endl;
}

//Mira si los vectores son iguales, en cuyo caso sale 0, si no sale -1:
int mira_error(double out[], double out2[2])
{
	double error = 0.0, valor = 0.0;
	error += fabs(out[0] - out2[0]); valor += fabs(out[0] + out2[0]);
	error += fabs(out[1] - out2[1]); valor += fabs(out[1] + out2[1]);
	error += fabs(out[2] - out2[2]); valor += fabs(out[2] + out2[2]);
	error = error / valor;
	if (error < 1e-7)
	{
		cout << " OK!!!!!!" << endl;
		return 0;
	}
	else
	{
		cout << " FAIL!!!!!! error=" << error << " ./1" << endl;
		return -1;
	}
}

