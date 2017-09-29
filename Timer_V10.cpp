#include <iostream>
#include <string.h> //strcpy strcat
#include <stdio.h> //fopen
#include <math.h> //sqrt, sin
#include <time.h>	//clock(), time_t
#pragma warning(disable:4996) //disable deprecateds
using namespace std;

#define _PRINT_RESULT


time_t start,stop;char null_char='\0';
//Use empty timer() to reset start time:
#ifndef _PRINT_RESULT
void timer(char *title=&null_char,int data_size=1){    	stop=clock();	if (*title) printf("%s time = %7lg = %7lg MOPs\n",title,(double) (stop-start)/(double) CLOCKS_PER_SEC, 1e-6*data_size/( (double)(stop-start)/(double)CLOCKS_PER_SEC ) ); 	start=clock(); }
#else
char string_timer[128*1024],str1[1024];
void timer(char *title=&null_char,int data_size=1)
{
	stop=clock();	
	if (*title) 
	{
		sprintf(str1,"%s time = %7lg = %7lg MOPs\n",title,(double) (stop-start)/(double) CLOCKS_PER_SEC, 1e-6*data_size/( (double)(stop-start)/(double)CLOCKS_PER_SEC ) ); 	
		cout<<str1;   strcat(string_timer,str1);
	}
	start=clock(); 
}
#endif

int main()
{
	cout << "Perform test in Release mode. Timing results will be wrong in Debug mode" <<endl;
	int isum=0,size=100*1024*1024;
	timer();//void timer resets timer!
	double dsum=1.0,d2=1.111;
//	for (int i=0;i<size/20;i++)
//		dsum=2.0/(dsum+3.0/(dsum+4.0/(dsum+5.0/(dsum+6.0/(dsum+7.0/(dsum+8.0/(dsum+9.0/(dsum+10.0/(dsum+11.0/(dsum  +12.0/(dsum+13.0/(dsum+14.0/(dsum+15.0/(dsum+16.0/(dsum+17.0/(dsum+18.0/(dsum+19.0/(dsum+21.0/(dsum+27.0/(dsum+2.0 ;
//	timer("Time for 100 Mega double divisions x20  ",size);
	for (int i=0;i<size;i++)
		dsum/=d2;
	timer("Time for 100 Mega double divisions      ",size);
	for (int i=0;i<size/20;i++)
	{
		dsum=1.1/(dsum+2.2/(dsum+2.3/(dsum+2.4/(dsum+2.5/(dsum+2.6/(dsum+2.7/(dsum+2.8/(dsum+2.9/(dsum+2.1/(dsum+2.2/(dsum+2.3/(dsum+2.4/(dsum+2.5/(dsum+2.6/(dsum+2.7/(dsum+2.8/(dsum+2.9/(dsum+3.1/(dsum+1.111)))))))))))))))))));
	}
	timer("Time for 100 Mega double divisions (20x)",size);
	float fsum=1.0f;
	for (int i=0;i<size;i++)
		fsum=fsum/1.1111f;
	timer("Time for 100 Mega float  divisions      ",size);
	for (int i=0;i<size;i++)
		dsum=dsum*d2;
	timer("Time for 100 Mega double multiplications",size);
	for (int i=0;i<size;i++)
		dsum=dsum+d2;
	timer("Time for 100 Mega double sums           ",size);
	for (int i=0;i<size;i++)
		dsum=sqrt(dsum);
	timer("Time for 100 Mega double sqrt           ",size);dsum+=1.01;
	for (int i=0;i<size;i++)
		dsum=sin(dsum);
	timer("Time for 100 Mega double sin            ",size);dsum+=1.01;
	for (int i=0;i<size;i++)
		dsum=log(dsum+2.0);
	timer("Time for 100 Mega double log            ",size);dsum+=1.01;
	for (int i=0;i<size;i++)
		isum+=i;
	timer("Time for 100 Mega int sums              ",size);
	for (int i=0;i<size;i++)
		isum<<=i;
	timer("Time for 100 Mega int <<                ",size);
	isum+=1;
	for (int i=1;i<size+1;i++)
		isum/=i;
	timer("Time for 100 Mega int divisions         ",size);
	for (int i=1;i<size+1;i++)
		isum*=i;
	timer("Time for 100 Mega int multiplications   ",size);
	for (int i=1;i<size+1;i++)
		isum=isum*2+i;
	timer("Time for 100 Mega int sum+mult          ",size);

#ifdef _PRINT_RESULT
	FILE *str=fopen("timer result.txt","a");
	fprintf(str,"\n======================================================================\n");
	fprintf(str,"%s",string_timer);
	fprintf(str,  "======================================================================\n");
	fclose(str);
#endif

	cout<<endl<<" Reject following data (done to force for loops be performed after compiler optimizations):  ";
	cout<<isum<<dsum<<fsum<<endl;//to force for() be done on isum
	cout<<"=== FIN ==="<<endl;getchar();
	return 1;
}
