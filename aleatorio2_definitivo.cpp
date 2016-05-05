#include <stdio.h>
#include <stdlib.h>//rand() used
#include <limits.h>//used by random0()
#include <math.h> //to make fft test
#include <time.h>//to make timer test and seeds the randoms

//Definitions, constants and functions used by random4 test:
#define SWAP(t,a,b) ( (t) = (a), (a) = (b), (b) = (t) )    //use: SWAP(dtemp, d1, d2);
#define RANS_MAX 131072
double rans_m[RANS_MAX];
double rans();//generates random number 0 <= rans() < 1
void  srans(long seed); //Must be run one time before using rans()

//Definitions for random5 and drand48
#define C_DRAND 16807
#define A_DRAND 2147483647.0
double yz_DRAND=0.1;
void srand48(long seed) { 	yz_DRAND= (double) seed; } 
double drand48();


//Four random functions: (worst=random3 and 5)
long random0(long max);//good
long random2(long max) { 	return rand() % max; }//better than random0 22% and quicker
long random3(long max) {	long r; do{r=rand();}while (r==RAND_MAX);return (long) ((r*max)/RAND_MAX); }//Bad! It is avoided to use rand() when it reach RAND_MAX
long random4(long max) {	return (long) (max*rans());}//It is the best of all but needs 177ms to execute srans() before to fill rams_m[] array
long random5(long max) {	return (long) (max*drand48());}//As bad as random3

//Definitions used for testing
#define NUM 10000000L
const long MAX=128;//rand values maximum=MAX-1
typedef long (*FUNCT)(long max);
long sum[MAX+1];
//tests the random functions by generation of numbers between 0-19 NUM times
void test(FUNCT f_rand);

//Constants and functions used to calculate power spectrum
#define PI	    3.1415926535897932384626433832795
#define TWOPI	6.283185307179586476925286766559
#define PI2     6.283185307179586476925286766559//input: data_in[0..number_of_samples]
//output:power[0..NFFT/2]  and frecuencia[0..NFFT/2]. CAUTION!!: fix power[] and frecuencia[] dimension to 2 x number_of_samples to avoid stack overflow!!!!
//NFFT=real size of power[] and frecuencia[] that is greater than number_of_samples in the form 2^N
//sample_rate=samples per second of the acquisition system
void power_spectrum(double data_in[], long number_of_samples,long sample_rate,double power[],double frecuencia[],long &NFFT);



long main()
{
	printf("\nTimings will be reduced by compile in RELEASE instead DEBUG mode");
	clock_t ini,fin;ini=clock();
	srans(time (NULL));//initializes rands_m[] with seed=1000;
	fin=clock();double milliseconds=1000.0*(fin-ini)/CLOCKS_PER_SEC;
	srand(time (NULL));//initializes rand()
	srand48(time (NULL));//initializes drand48()
	printf("\n\nTime needed for srans()=%lg milliseconds",milliseconds);
	printf("\n\nTesting random0()");test(random0);
	printf("\n\nTesting random2()");test(random2);
	printf("\n\nTesting random3()");test(random3);
	printf("\n\nTesting random4()");test(random4);
	printf("\n\nTesting random5()");test(random5);

	printf("\n\n===FIN===");getchar();getchar();
	return 1;
}

void test(FUNCT f_rand)
{
	long i,max=MAX;
	for (i=0;i<MAX+1;i++) sum[i]=0;

	clock_t ini,fin;ini=clock();
	for (i=0;i<NUM;i++)
	{
		sum[(*f_rand)(max)]++; 
	}
	fin=clock();double seconds=1.0*(fin-ini)/CLOCKS_PER_SEC;
	long min=LONG_MAX,max1=-1;
	for (i=0;i<MAX;i++) 
	{
		if (min>sum[i]) min=sum[i];
		if (max1<sum[i]) max1=sum[i];
	}
	printf("\nMegasamples/second=%lg",1.0e-6*NUM/seconds);
	printf("\nMinimum repeatings=%li",min);
	printf("\nMaximum repeatings=%li",max1);
	printf("\nMaximum-minimums  =%li (less is better)",max1-min);
	if (sum[MAX]!=0) printf("\nFAILS maximum value reached one time every %lg", (double) (1.0*NUM/sum[MAX]));

	double power[MAX],data_in[MAX],frecuencia[MAX];
	long NFFT;
	for (i=0;i<MAX;i++) data_in[i]=(*f_rand)(max);
	power_spectrum(data_in, MAX, MAX,power,frecuencia,NFFT);
	double mid=0.0,rms=0.0,x;
	for (i=0;i<MAX/2;i++) mid+=power[i];
	mid=2.0*mid/MAX;
	for (i=0;i<MAX/2;i++) { x=mid-power[i];rms+=x*x;}
	rms=sqrt(2.0*rms/MAX);
	printf("\nRMS of FFT power  =%lg (less is better)",rms);
}


long random0(long max)
{
	static long sum=0;
	long x;
	x=(rand()+sum) % max;
	sum+=RAND_MAX;
	if (sum>(LONG_MAX-RAND_MAX)) 
		sum=0;
	return x;
}

void  srans(long seed=0)
{
	seed=seed%(1024L*1024L);//limited to 1Meg
	long i,k,l=0;double temp;
	for (i=0;i<RANS_MAX;i++) rans_m[i]=1.0*i/RANS_MAX;
	for (i=0;i<(8L*1024L*1024L);i++)
	{
		k=i % RANS_MAX;l=(k+rand()) % RANS_MAX;
		SWAP(temp,rans_m[k],rans_m[l]);
		//temp=rans_m[k];rans_m[k]=rans_m[l];rans_m[l]=temp;
	}
	for (i=0;i<(seed % RANS_MAX);i++) //seed is applied, but not longer than 128k times
		rans();
}

double rans()
{
	static int index=-1;
	index=(index+1)% RANS_MAX; //index must be < RANS_MAX
	return rans_m[index];
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



double drand48() 
{
	long ki;
	double uu;
	ki=(long) ((C_DRAND* yz_DRAND)/A_DRAND);
	yz_DRAND = C_DRAND * yz_DRAND - ki * A_DRAND;
	uu=yz_DRAND/(A_DRAND-1);
	return uu;
}