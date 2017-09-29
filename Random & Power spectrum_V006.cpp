//It can be seen that standard c++ rand() really generates a flat power spectrum
//See also FFT_V10.cpp 
#include <iostream>
#include <complex>
#include <time.h>	//clock(), time_t
#include <stdlib.h> //rand
#include <string.h> //memcpy
#pragma warning(disable:4996) //disable deprecateds
using namespace std;
typedef unsigned char uchar;

//#define HAMMING //uses the Hamming window!!!!!!!!!
#define _GET_RAND_MAX 65536   //  = 64*1024 = RAND_MAX+1

typedef std::complex<double> Complex;


#define PI	    3.1415926535897932384626433832795
#define TWOPI	6.283185307179586476925286766559
#define PI2     6.283185307179586476925286766559

double _rand[64*1024];

//generation of example signal:
//	output: data[0-number_of_samples]  
void creates_random_signal( double data[], int number_of_samples);
void creates_random_signal( int data[], int number_of_samples);
time_t start,stop;
// Empty timer() resets start time:
void timer(char *title=0,int data_size=1);




//input: data_in[0..number_of_samples]
//NFFT=numero real de datos 
//output:power[0..NFFT/2]  y frecuencia[0..NFFT/2]
//sample_rate=muestras por segundo del sistema de adquisición
void power_spectrum2(double data_in[], int number_of_samples,int sample_rate,double power[],double frecuencia[],int &NFFT);
void power_spectrum2_inverse(double data_in[], int number_of_samples,int sample_rate,double power[],double frecuencia[],int &NFFT);

//Uses Hamming window:
void hamming(double data_in[], int number_of_samples);



int main()
{
	int i;
	int NFFT;

	const int number_of_samples=_GET_RAND_MAX;
	int sample_rate=64*1024;
	/* generate a ramp with 10 numbers */
	double *data1=new double[  number_of_samples];
	double *power=new double[2*number_of_samples]; // 2x due real size can be doubled by power_spectrum()to fix to a 2^N number

	double *frecuencia=new double[2*number_of_samples];  // 2x due real size can be doubled by power_spectrum()to fix to a 2^N number
	creates_random_signal(_rand,number_of_samples);
	memcpy(data1,_rand,number_of_samples*sizeof(double));
	//power_spectrum(data1,number_of_samples,sample_rate,power,frecuencia,NFFT);
	timer("\0");//initializes timer
	power_spectrum2(data1,number_of_samples,sample_rate,power,frecuencia,NFFT);
	timer(" power_spectrum2 time: ",number_of_samples);


	FILE *strout=fopen("out.csv","w");
	if (!strout)
	{
		printf("\nERROR en fichero out.csv");getchar();return -1;
	}
	fprintf(strout,"number, frequency, power, inverse");
	for(i=1; i<NFFT/2; i++)
	{
		fprintf(strout,"\n%d, %lg, %lg", i, frecuencia[i],power[i]);
	}

	fclose(strout);
	delete[] data1;
	delete[] power;
	delete[] frecuencia;
	cout<<"=== FIN ==="<<endl;getchar();
	return 1;
}


/*
   input: data_in[0..number_of_samples]
   output:power[0..NFFT/2]  and frecuencia[0..NFFT/2]. CAUTION!!: fix power[] and frecuencia[] dimension to 2 x number_of_samples to avoid stack overflow!!!!
   NFFT=real size of power[] and frecuencia[] that is greater than number_of_samples in the form 2^N
   sample_rate=samples per second of the acquisition system
   Modification of Paul Bourkes FFT code by Peter Cusack and    Javier Luis Lopez 
   No license issues due Javier Luis Lopez, I only hope it is useful

   This computes an in-place complex-to-complex FFT 
   x and y are the real and imaginary arrays of 2^m points.
   dir =  1 gives forward transform
   dir = -1 gives reverse transform 
*/
void power_spectrum2(double data_in[], int number_of_samples,int sample_rate,double power[],double frecuencia[],int &NFFT)
//void FFT(int dir, int m, Complex x[])
{
#ifdef HAMMING
	hamming (data_in,number_of_samples);
#endif
   int i, i1, i2,j, k, l, l1, l2, n,dir=1; //dir=1:FFT directa
   Complex tx, t1, u, c;

   /*Calculate the number of points */
   //n = 1; for(i = 0; i < m; i++)  n <<= 1;   
   n=NFFT = (int) pow(2.0, ceil(log((double)number_of_samples)/log(2.0)));
   Complex *x=new Complex[NFFT];
   int m=0,m1=NFFT;
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
void hamming(double data_in[], int number_of_samples)
{
	int i;double w=PI2/(number_of_samples-1.0);
	for (i=0;i<number_of_samples;i++)
		data_in[i]*=0.45-.46*cos(w*i);

}

//generation of example signal:
//	output: data[0-number_of_samples]  
void creates_random_signal(double data[], int number_of_samples)
{
	for (int i=0;i<number_of_samples;i++)
	{
		data[i]=(double) rand()/(double) _GET_RAND_MAX;  //RAND_MAX = 64k-1 so better use _GET_RAND_MAX
	}
}

void creates_random_signal( int data[], int number_of_samples)
{
	for (int i=0;i<number_of_samples;i++)
	{
		data[i]=rand();  
	}
}


void timer(char *title,int data_size)
{
	stop=clock();
	if (*title) cout<<title<< " time ="<<(double) (stop-start)/(double) CLOCKS_PER_SEC<< " = " << 1e-6*data_size/( (double)(stop-start)/(double)CLOCKS_PER_SEC ) <<  " Mops/seg"   <<endl;
	start=clock();//it must be done better in the beginning of the function to be measured
}

void power_spectrum2_inverse(double data_in[], int number_of_samples,int sample_rate,double power[],double frecuencia[],int &NFFT)
//void FFT(int dir, int m, Complex x[])
{
#ifdef HAMMING
	hamming (data_in,number_of_samples);
#endif
   int i, i1, i2,j, k, l, l1, l2, n,dir=-11; //dir=1:FFT directa
   Complex tx, t1, u, c;

   /*Calculate the number of points */
   //n = 1; for(i = 0; i < m; i++)  n <<= 1;   
   n=NFFT = (int) pow(2.0, ceil(log((double)number_of_samples)/log(2.0)));
   Complex *x=new Complex[NFFT];
   int m=0,m1=NFFT;
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