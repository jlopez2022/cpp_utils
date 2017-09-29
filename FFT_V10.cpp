/*
V10: Mete power_spectrum2() que dá más precisión en frecuencia  
     Además mete ventana Hamming para más precisión en amplitud
*/
#include <iostream>
#include <complex>
#include <time.h>	//clock(), time_t
#include <stdlib.h> //rand
#include <string.h> //memcpy
#pragma warning(disable:4996) //disable deprecateds
using namespace std;
typedef unsigned char uchar;

//#define HAMMING //uses the Hamming window!!!!!!!!!

typedef std::complex<double> Complex;


#define PI	    3.1415926535897932384626433832795
#define TWOPI	6.283185307179586476925286766559
#define PI2     6.283185307179586476925286766559

//generation of example signal:
//	output: data[0-number_of_samples]  
void crea_signal( double data[], long number_of_samples, long sample_rate);
void crea_signal1(double data[], long number_of_samples, long sample_rate);



//input: data_in[0..number_of_samples]
//NFFT=numero real de datos 
//output:power[0..NFFT/2]  y frecuencia[0..NFFT/2]
//sample_rate=muestras por segundo del sistema de adquisición
void power_spectrum2(double data_in[], long number_of_samples,long sample_rate,double power[],double frecuencia[],long &NFFT);
//Other worse:
void power_spectrum(double data_in[], long number_of_samples,long sample_rate,double power[],double frecuencia[],long &NFFT);

//Uses Hamming window:
void hamming(double data_in[], long number_of_samples);



int main()
{
	long i;
	long NFFT;

	const long number_of_samples=1000;
	long sample_rate=25000;
	/* generate a ramp with 10 numbers */
	double *data1=new double[  number_of_samples];
	double *power=new double[2*number_of_samples]; // 2x due real size can be doubled by power_spectrum()to fix to a 2^N number

	double *frecuencia=new double[2*number_of_samples];  // 2x due real size can be doubled by power_spectrum()to fix to a 2^N number
	crea_signal1(data1,number_of_samples,sample_rate);
	//power_spectrum(data1,number_of_samples,sample_rate,power,frecuencia,NFFT);
	power_spectrum2(data1,number_of_samples,sample_rate,power,frecuencia,NFFT);

	FILE *strout=fopen("out.txt","w");
	if (!strout)
	{
		printf("\nERROR en fichero out.txt");getchar();return -1;
	}
	fprintf(strout,"number\t frequency\t power");
	for(i=1; i<NFFT/2; i++)
	{
		fprintf(strout,"\n%d\t %lg\t %lg", i, frecuencia[i],power[i]);
	}

	delete[] data1;
	delete[] power;
	delete[] frecuencia;
	fclose(strout);
	return 1;
}

//input: data_in[0..number_of_samples]
//output:power[0..NFFT/2]  and frecuencia[0..NFFT/2]. CAUTION!!: fix power[] and frecuencia[] dimension to 2 x number_of_samples to avoid stack overflow!!!!
//NFFT=real size of power[] and frecuencia[] that is greater than number_of_samples in the form 2^N
//sample_rate=samples per second of the acquisition system
void power_spectrum(double data_in[], long number_of_samples,long sample_rate,double power[],double frecuencia[],long &NFFT)
{
	long i;
	double *data;
	double *X;
	NFFT = (long) pow(2.0, ceil(log((double)number_of_samples)/log(2.0)));
	/* allocate memory for NFFT complex numbers (note the +1) */
	X = (double *) malloc((2*NFFT+1) * sizeof(double));

	/* Storing x(n) in a complex array to make it work with four1. 
	This is needed even though x(n) is purely real in this case. */
	for(i=0; i<number_of_samples; i++)
	{
		X[2*i+1] = data_in[i];
		X[2*i+2] = 0.0;
	}
	/* pad the remainder of the array with zeros (0 + 0 j) */
	for(i=number_of_samples; i<NFFT; i++)
	{
		X[2*i+1] = 0.0;
		X[2*i+2] = 0.0;
	}
	data=X;

    long n, mmax, m, j, istep;
    double wtemp, wr, wpr, wpi, wi, theta;
    double tempr, tempi;
    
    n = NFFT << 1;
    j = 1;
    for (i = 1; i < n; i += 2) 
	{
		if (j > i) 
		{
			tempr = data[j];     data[j] = data[i];     data[i] = tempr;
			tempr = data[j+1]; data[j+1] = data[i+1]; data[i+1] = tempr;
		}
		m = n >> 1;
		while (m >= 2 && j > m) 
		{
			j -= m;
			m >>= 1;
		}
		j += m;
    }
    mmax = 2;
    while (n > mmax) 
	{
		istep = 2*mmax;
		theta = TWOPI/(1.0*mmax);
		wtemp = sin(0.5*theta);
		wpr = -2.0*wtemp*wtemp;
		wpi = sin(theta);
		wr = 1.0;
		wi = 0.0;
		for (m = 1; m < mmax; m += 2) 
		{
			for (i = m; i <= n; i += istep) 
			{
				j =i + mmax;
				tempr = wr*data[j]   - wi*data[j+1];
				tempi = wr*data[j+1] + wi*data[j];
				data[j]   = data[i]   - tempr;
				data[j+1] = data[i+1] - tempi;
				data[i] += tempr;
				data[i+1] += tempi;
			}
			wr = (wtemp = wr)*wpr - wi*wpi + wr;
			wi = wi*wpr + wtemp*wpi + wi;
		}
		mmax = istep;
    }

	//I have now in data[] the real and imaginary parts of the FFT
	//I calculate now Power and frequency:

	double kk=0.5*number_of_samples;//It must be 0.5*NFFT, but we introducted samples only in the 0-number_of_samples segments, others were filled with zeroesd
	for(i=1; i<=NFFT/2; i++)
	{
		frecuencia[i-1] =1.0*(i-1)*sample_rate/NFFT;
		power[i-1]      =data[2*i+1]*data[2*i+1]+ data[2*i+2]*data[2*i+2];
		power[i-1]      =sqrt(power[i-1])/kk;
	}
	free(X);
}





/*
   Modification of Paul Bourkes FFT code by Peter Cusack and 
   Javier Luis Lopez 
   No license issues due Javier Luis Lopez, I only hope it is useful

   This computes an in-place complex-to-complex FFT 
   x and y are the real and imaginary arrays of 2^m points.
   dir =  1 gives forward transform
   dir = -1 gives reverse transform 
*/
void power_spectrum2(double data_in[], long number_of_samples,long sample_rate,double power[],double frecuencia[],long &NFFT)
//void FFT(int dir, long m, Complex x[])
{
#ifdef HAMMING
	hamming (data_in,number_of_samples);
#endif
   long i, i1, i2,j, k, l, l1, l2, n,dir=1; //dir=1:FFT directa
   Complex tx, t1, u, c;

   /*Calculate the number of points */
   //n = 1; for(i = 0; i < m; i++)  n <<= 1;   
   n=NFFT = (long) pow(2.0, ceil(log((double)number_of_samples)/log(2.0)));
   Complex *x=new Complex[NFFT];
   long m=0,m1=NFFT;
   while (m1)    {		   m1>>=1;m++;    }
   m--;
   for (i=0;i<NFFT;i++)
   {
	   x[i].imag(0.0);
		if (i<number_of_samples)
			x[i].real(data_in[i]);
		else 
			x[i].real(0.0);
   }

   /* Do the bit reversal */
   i2 = n >> 1;
   j = 0;

   for (i = 0; i < n-1 ; i++)
   {
      if (i < j)
         swap(x[i], x[j]);

      k = i2;

      while (k <= j) 
	  {
         j -= k;
         k >>= 1;
      }

      j += k;
   }

   /* Compute the FFT */
   c.real(-1.0);
   c.imag(0.0);
   l2 = 1;
   for (l = 0; l < m; l++) 
   {
      l1 = l2;
      l2 <<= 1;
      u.real(1.0);
      u.imag(0.0);

      for (j = 0; j < l1; j++) 
	  {
         for (i = j; i < n; i += l2) 
		 {
            i1 = i + l1;
            t1 = u * x[i1];
            x[i1] = x[i] - t1; 
            x[i] += t1;
         }

         u = u * c;
      }

      c.imag(sqrt((1.0 - c.real()) / 2.0));
      if (dir == 1)
         c.imag(-c.imag());
      c.real(sqrt((1.0 + c.real()) / 2.0));
   }

   /* Scaling for forward transform */
   if (dir == 1) 
   {
      for (i = 0; i < n; i++)
         x[i] /= n;      
   }   
    //Calculation of power and frequency:
#ifdef HAMMING
	double kk=0.5*.46*number_of_samples/NFFT;//0.5*number_of_samples;//It must be 0.5*NFFT, but we introducted samples only in the 0-number_of_samples segments, others were filled with zeroesd
#else
	double kk=0.5;// *number_of_samples/NFFT;
#endif
	for(i=0; i<NFFT/2; i++)
	{
		frecuencia[i] =1.0*i*sample_rate/NFFT;
		if ( (i<2)||(i>=(NFFT/2-2)) )
			power[i]=sqrt(x[i].real()*x[i].real()+x[i].imag()*x[i].imag())/kk;
		else
		{    //see CONVOLUCION: http://www.dsprelated.com/showarticle/155.php
			double x1_real,x1_imag;
			x1_real=x[i].real() - 0.94247*(x[i-1].real()+x[i+1].real()) + 0.44247*(x[i-2].real()+x[i+2].real());
			x1_imag=x[i].imag() - 0.94247*(x[i-1].imag()+x[i+1].imag()) + 0.44247*(x[i-2].imag()+x[i+2].imag());
			power[i]=sqrt( x1_real*x1_real+x1_imag*x1_imag )/kk;
		}
	}
	free(x);
}

//Uses Hamming window:
void hamming(double data_in[], long number_of_samples)
{
	long i;double w=PI2/(number_of_samples-1.0);
	for (i=0;i<number_of_samples;i++)
		data_in[i]*=0.45-.46*cos(w*i);

}

//generation of example signal:
//	output: data[0-number_of_samples]  
void crea_signal(double data[], long number_of_samples, long sample_rate)
{
	double amp1=0.35,frec1=1000,phase1=1.0;   //amplitude and phase-1
	double amp2=0.2, frec2=2000,phase2=1.2;   //amplitude and phase-2
	double amp3=1.0, frec3=8000,phase3=0.5;   //amplitude and phase-3
	double amp4=1.0, frec4=10000,phase4=0.2;  //amplitude and phase-4
	long i;
	double k1,k2,k3,k4;
	k1=PI2/sample_rate*frec1;
	k2=PI2/sample_rate*frec2;
	k3=PI2/sample_rate*frec3;
	k4=PI2/sample_rate*frec4;
	for (i=0;i<number_of_samples;i++)
	{
		data[i]=amp1*sin(k1*i+phase1) + amp2*sin(k2*i+phase2) + amp3*sin(k3*i+phase3) + amp4*sin(k4*i+phase4);//waveform=sum of 4 sines
	}
}

void crea_signal1(double data[], long number_of_samples, long sample_rate)
{
	long i,j;
	for (i=0;i<number_of_samples;i++)
	{
		double x=0.0,k=PI2*20/number_of_samples;  //frec=10*frec_min    frec_min=sample_rate/number_of_samples
		for (j=1;j<21;j++)
			x+=sin(k*j*i);
		data[i]=x;
	}
}

