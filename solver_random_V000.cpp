/*
Resuelve ecuaciones con muchas incognitas. 
Escoje el conjunto de coeficientes que reduce este error al minimo
*/

//#include <stdio.h> no se usa, si no no se puede usar cout
#include <iostream>
#include <stdlib.h> //rand
#include <algorithm> //sort

//uses: x=INLIMIT3(x,10,100);
//No hace falta pues el algoritmo impide salirse de limites:
#define INLIMIT3(x,xmin,xmax) ( (x)<(xmin) ? (xmin) : ((x)<(xmax) ? (x) : (xmax)    ))     //OJO: ASIGNO max no max-1!!! 

using namespace std;
typedef unsigned char uchar;


#define CENT_DIM  6 //numero de coeficientes (o dimensiones) 
//funcion a la cual quiero reducir la salida a un minimo
double generafuncion(double *x);//en funcion de x[CENT_DIM] obtengo el resultado

//Estas dos definiciones las usa para funcion sort y no las he podido meter dentro de la clase:
double *dato_d;
bool ordenalista(long i, long j) { return dato_d[i] < dato_d[j]; }

class c_solver
{
public:
	c_solver();
	~c_solver() 
	{
		delete rans_matriz_double; 
	}
	typedef double(*FUNCT)(double *);
	double rans(void){ index = (index + 1) % RANS_SIZE; return rans_matriz_double[index]; } //devuelve 0 a 1
	void solve(FUNCT hallaerror, double *Kmin,double *Kmax);
private:
	const long CENT_NUM = 21000; // debe ser divisible por CENT_FACTOR
	const long CENT_FACTOR = 7000;  //divide los centroides iniciales por un factor, quitando los de mas error, luego halla para cada centroide un factor de estos
	double CENT_COEF; //coeficiente de reduccion en cada dimension, debiera de ser (1/CENT_FACTOR)^(1/CENT_DIM)  pero DEBE ESTAR entre 0 y 1

	void halla_centroides_rans(double min[CENT_DIM], double max[CENT_DIM], double min2[][CENT_DIM], double max2[][CENT_DIM], long num);
	inline void hallacentro(double cenmin[], double cenmax[], double centro[]);
	void halladev(double cenmin[], double cenmax[], double error[]);

	//ORDENACION:
	// decreciente: > creciente: < 
	//bool wayToSort(long i, long j) { return i < j; }
	
	//zona rans:
	const long RANS_SIZE = 131072; //<131072
	long index;
	double *rans_matriz_double;
	//k desordena 17 veces:
	void desordena_double() { double v0; for (long k = 0; k<17; k++) for (long i = 0; i<RANS_SIZE; i++) 	{ v0 = rans_matriz_double[i]; long j = rand(); j = ((j << 15) + rand()) % RANS_SIZE; 	rans_matriz_double[i] = rans_matriz_double[j]; rans_matriz_double[j] = v0; } }
};

c_solver::c_solver()
{
	CENT_COEF = pow(1.0 / CENT_FACTOR, 1.0 / CENT_DIM);
	cout << "CENT_COEF=" << CENT_COEF << endl;
	cout << "Iteraciones recomendadas=" << (long)(1.0 + log(1e-8) / log(CENT_COEF)) << endl;
	//zona rans:
	rans_matriz_double = new double[RANS_SIZE];
	index = 0; long i; for (i = 0; i<RANS_SIZE; i++) { rans_matriz_double[i] = 1.0f*i / RANS_SIZE; }; //valor mas cerca de 1= 131071/131072
	desordena_double();
}

void c_solver::solve(FUNCT funcion_error_min, double *Kmin, double *Kmax)
{
	auto cenmin1 = new double[CENT_NUM][CENT_DIM];
	auto cenmax1 = new double[CENT_NUM][CENT_DIM];
	auto cenmin2 = new double[CENT_NUM][CENT_DIM];
	auto cenmax2 = new double[CENT_NUM][CENT_DIM];
	auto error = new double[CENT_NUM];
	auto lista = new long[CENT_NUM];

	//Inicializo centroides:
	halla_centroides_rans(Kmin, Kmax, cenmin1, cenmax1, CENT_NUM);
	long num_iter = (long)(1.0 + log(1e-8) / log(CENT_COEF)); //numero de iteraciones

	//iter=iteraciones
	for (long iter = 0; iter < num_iter; iter += 2)
	{
		double centro[CENT_DIM];
		double err1;

		//PRIMER PASEO
		//Hallo error para cada centro:
		for (long i = 0; i < CENT_NUM; i++)
		{
			hallacentro(cenmin1[i], cenmax1[i], centro);
			error[i] = funcion_error_min(centro);//valor ha hacer 0
		}
		//ordeno segun lista:
		for (long i = 0; i < CENT_NUM; i++) lista[i] = i;
		dato_d = error;
		sort(lista, lista + CENT_NUM, ordenalista);
		long centros_elegidos = CENT_NUM / CENT_FACTOR;
		for (long ix = 0; ix < CENT_NUM;)
		{
			long i = lista[ix];
			halla_centroides_rans(cenmin1[i], cenmax1[i], &cenmin2[ix], &cenmax2[ix], CENT_FACTOR);
			ix += CENT_FACTOR;
		}
		hallacentro(cenmin1[0], cenmax1[0], centro);
		err1 = funcion_error_min(centro);
		cout << "iter:" << iter + 1 << " resultado=" << err1 << endl;

		//REPITO TODO CAMBIANDO ORIGEN Y DESTINO cenmin1 por cenmin2 y cenmax1 por cenmax2:
		//Hallo error para cada centro:
		for (long i = 0; i < CENT_NUM; i++)
		{
			hallacentro(cenmin2[i], cenmax2[i], centro);
			error[i] = funcion_error_min(centro);//valor ha hacer 0
		}
		//ordeno segun lista:
		for (long i = 0; i < CENT_NUM; i++) lista[i] = i;
		dato_d = error;
		sort(lista, lista + CENT_NUM, ordenalista);
		centros_elegidos = CENT_NUM / CENT_FACTOR;
		for (long ix = 0; ix < CENT_NUM;)
		{
			long i = lista[ix];
			halla_centroides_rans(cenmin2[i], cenmax2[i], &cenmin1[ix], &cenmax1[ix], CENT_FACTOR);
			ix += CENT_FACTOR;
		}
		hallacentro(cenmin2[0], cenmax2[0], centro);
		err1 = funcion_error_min(centro);
		cout << "iter:" << iter + 2 << " resultado=" << err1 << endl;
	}
	//El resultado se halla aqui:
	double error1[CENT_DIM], centro1[CENT_DIM];
	hallacentro(cenmin1[0], cenmax1[0], centro1);
	halladev(cenmin1[0], cenmax1[0], error1);

	cout << "\N===== COEFICIENTES CALCULADOS ====" << endl;
	for (long i = 0; i < CENT_DIM; i++)
	{
		cout << "coef " << i << ":" << centro1[i] << " error:" << error1[i] << endl;
	}
	cout << "===== COEFICIENTES CALCULADOS ====" << endl;

	double error2 = funcion_error_min(centro1);
	cout << "==============    error final=" << error2 << endl<<endl;
	delete[] cenmin1;
	delete[] cenmin2;
	delete[] cenmax1;
	delete[] cenmax2;
	delete[] error;
	delete[] lista;
}

void c_solver::halla_centroides_rans(double min[CENT_DIM], double max[CENT_DIM], double min2[][CENT_DIM], double max2[][CENT_DIM], long num)
{
	double k;
	for (long i = 0; i < num; i++)
		for (long d = 0; d < CENT_DIM; d++)
		{
			k = min[d] + rans()*(max[d] - min[d]);
			max2[i][d] = k + CENT_COEF*(max[d] - k);
			min2[i][d] = k - CENT_COEF*(k-min[d]);
		}
}

inline void c_solver::hallacentro(double cenmin[], double cenmax[], double centro[])
{
	for (long i = 0; i < CENT_DIM; i++)
		centro[i] = 0.5*(cenmin[i] + cenmax[i]);
}
void c_solver::halladev(double cenmin[], double cenmax[], double error[])
{
	for (long i = 0; i < CENT_DIM; i++)
		error[i] = 0.5*(cenmax[i] - cenmin[i]);
}


void main()
{


	//1.0 Meto datos a centroide inicial:
	double Kmin[CENT_DIM] = { 0.2, 0.5, 0.4, 0.6, -32.8, 1.2 };//valores minimos de los coeficientes
	double Kmax[CENT_DIM] = { 20.0, 32.0, 45.0, 33.0, 29.2, 202.0 };//id maximos
	//Empleo el solver:
	c_solver solucionador;
	solucionador.solve(generafuncion, Kmin, Kmax);

	cout << "======end========\n"; getchar(); getchar();
}




//funcion de prueba para 6 dimensiones:
double generafuncion(double x[])//en funcion de x obtengo el resultado
{
	double x0=0.0; //minimo=0, 
	const double amplitud[6] = { 10.0, 3.3, 11.5, 42.5, 1.2, 3.8 };
	const double exp[6] = { 1.5, 2.2, 1.8, 3.3, 1.9, 1.7 };
	const double periodo[6] = { 5.5, 6.4, 8.2, 12.3, 22, 4.0 };
	const double fase[6] = { 9.1, 2, 3, 5.5, 0.8, 3.3 };

	for (int i = 0; i < 6; i++)
		x0 += amplitud[i] * pow(fabs(sin(fase[i] + x[i] / periodo[i])), exp[i]);
	return x0;
}
