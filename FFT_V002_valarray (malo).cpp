
//OJO!!!: quitar stafax :  select project-properties-c/c++-precompiled headers 
//Then select Not Using Precompiled Headers
#include "stdafx.h"
#include <complex>
#include <iostream>
#include <valarray>
 
const double PI = 3.141592653589793238460;
const double PI2= 6.283185307179586476925286766559;

 
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

void crea_signal(double data[], long number_of_samples, long sample_rate);

 
// Cooley–Tukey FFT (in-place)
void fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;
 
    // divide
    CArray even = x[std::slice(0, N/2, 2)];
    CArray  odd = x[std::slice(1, N/2, 2)];
 
    // conquer
    fft(even);
    fft(odd);
 
    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}
 
// inverse fft (in-place)
void ifft(CArray& x)
{
    // conjugate the complex numbers
    x = x.apply(std::conj);
 
    // forward fft
    fft( x );
 
    // conjugate the complex numbers again
    x = x.apply(std::conj);
 
    // scale the numbers
    x /= x.size();
}
 
int main()
{

	const long number_of_samples=1000;
	long sample_rate=25000;
	/* generate a ramp with 10 numbers */
	double data1[number_of_samples],power[number_of_samples],frecuencia[number_of_samples];
	crea_signal(data1,number_of_samples,sample_rate);

	Complex data2[number_of_samples];
	long i;
	for (i=0;i<number_of_samples;i++) 
		data2[i]=data1[i];
    CArray data(data2, number_of_samples);
 
    // forward fft
    fft(data);
	double k=4.0/number_of_samples;
	for (i=0;i<number_of_samples/2;i++)
	{
		power[i]=k*sqrt(data[i].real()*data[i].real()+data[i].imag()*data[i].imag());
		frecuencia[i]=1.0*i*sample_rate/number_of_samples;
	}
 
	FILE *strout=fopen("out.txt","w");
	if (!strout)
	{
		printf("\nERROR en fichero out.txt");getchar();return -1;
	}
	fprintf(strout,"number\t frequency\t power");
	for(i=0; i<number_of_samples/2; i++)
	{
		fprintf(strout,"\n%d\t %lg\t %lg", i, frecuencia[i],power[i]);
	}


	fclose(strout);

	//getchar();
    return 0;
}

//creando señal de ejemplo
void crea_signal(double data[], long number_of_samples, long sample_rate)
{
	double amp1=0.35,frec1=1000,phase1=1.0;   //amplitude and phase-1
	double amp2=0.2, frec2=2000,phase2=1.2;   //amplitude and phase-2
	double amp3=1.0, frec3=4000,phase3=0.5;   //amplitude and phase-3
	double amp4=1.0, frec4=10000,phase4=0.2;  //amplitude and phase-4
	long i;
	double k1,k2,k3,k4;
	k1=PI2/sample_rate*frec1;
	k2=PI2/sample_rate*frec2;
	k3=PI2/sample_rate*frec3;
	k4=PI2/sample_rate*frec4;
	for (i=0;i<number_of_samples;i++)
	{
		data[i]=amp1*sin(k1*i+phase1) + amp2*sin(k2*i+phase2) + amp3*sin(k3*i+phase3) + amp4*sin(k4*i+phase4);
	}
}
