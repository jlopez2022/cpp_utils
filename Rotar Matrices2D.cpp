#include <iostream>
#include <time.h>
#define PI2 1.5707963267948966192313216916398 //pi/2
#define PI180 0.01745329251994329576923690768489   //pi/180


using namespace std;

//#1. Calculates coefficient array using angle in radians:
template<class T>
void rotar_2d_hallacoef(T coef[4],T angle) { 	
	T Cz = cos(angle), Sz = sin(angle); 
	coef[0]=coef[3]= Cz;coef[1]=-Sz;coef[2]=Sz;
}

//#2. rotates x,y using z axis an angle. Uses coefficients calculated at rotar_2d_hallacoef(). TESTED!!
template<class T>
void rotar_2d(T coef[4],T in[2],T out[2])
{
	out[0]=in[0]*coef[0] + in[1]*coef[1];
	out[1]=in[0]*coef[2] + in[1]*coef[3];
}

//#3. As #2. but using shorts. Uses also #1 to calculate coef[]
void rotar_2d(double coef[4],short in[2],short out[2])
{
	out[0]=(short) (0.5+in[0]*coef[0] + in[1]*coef[1]);
	out[1]=(short) (0.5+in[0]*coef[2] + in[1]*coef[3]); 
}

//#3. As #2. but using shorts. Uses also #1 to calculate coef[]. NOT TESTED
void rotar_2d_index(double coef[4],int index_in,short xmax,int &index_out)
{
	short in[2]={index_in % xmax,index_in/ xmax},out[2];
	out[0]=(short) (0.5+in[0]*coef[0] + in[1]*coef[1]);
	out[1]=(short) (0.5+in[0]*coef[2] + in[1]*coef[3]); 
	index_out=out[0]+out[1]*xmax;
}

//#4. Fills an array with delta x,y using the rotation coefficients around center and x_delta,y_delta=delta. NOT TESTED
//It is used indexes, so xmax is needed!
void fills_2d_rotation(double coef[4],short delta,short xmax,short *out_ix)
{
	delete[] out_ix;
	int size=(2*delta+1)*(2*delta+1);out_ix=new short[size];
	short out[2];
	int dx,dy,index=0;
	for (dx=-delta;dx<=delta;dx++)
		for (dy=delta;dy<=delta;dy++)
		{
			short in[2]={dx,dy};rotar_2d(coef,in,out);out_ix[index++]=out[0]+out[1]*xmax;
		}
}


time_t start,stop;char null_char='\0';
//Use empty timer() to reset start time:
void timer(char *title=&null_char,int data_size=1){    	stop=clock();	if (*title) printf("%s time = %7lg = %7lg MOPs\n",title,(double) (stop-start)/(double) CLOCKS_PER_SEC, 1e-6*data_size/( (double)(stop-start)/(double)CLOCKS_PER_SEC ) ); 	start=clock(); }

void test_results();
void test_speed();


int main()
{
	void test_results();
	void test_speed();
	printf("\n\n===FIN===");getchar();
	return 1;
}









void test_results()
{
	{	//Results test
		double coef[4];
		rotar_2d_hallacoef(coef,(double) 0.5);
		double in[2],out[2];
		printf("xin    yin    xout       zout\n");
		in[0]= 2.0;in[1]= 0.0;rotar_2d(coef,in,out);printf("%-6g %-6g %-10g %-10g\n",in[0],in[1],out[0],out[1]);
		in[0]= 1.0;in[1]= 1.0;rotar_2d(coef,in,out);printf("%-6g %-6g %-10g %-10g\n",in[0],in[1],out[0],out[1]);
		in[0]= 0.0;in[1]= 2.0;rotar_2d(coef,in,out);printf("%-6g %-6g %-10g %-10g\n",in[0],in[1],out[0],out[1]);
		in[0]=-2.0;in[1]= 0.0;rotar_2d(coef,in,out);printf("%-6g %-6g %-10g %-10g\n",in[0],in[1],out[0],out[1]);
		in[0]= 0.0;in[1]=-2.0;rotar_2d(coef,in,out);printf("%-6g %-6g %-10g %-10g\n",in[0],in[1],out[0],out[1]);
	}
}

void test_speed()
{
	{//speed test float:
		float coef[4];
		float in[2]={1.1f,1.2f},out[2];
		float sum=0.0f;
		int N=10000000;
		timer();//set to zero
		for(int i=0;i<N;i++)
		{
			float ang=((float) (i%5000))/5000.0f;
			rotar_2d_hallacoef(coef,ang);sum+=coef[0];rotar_2d_hallacoef(coef,ang);sum+=coef[0];
			rotar_2d_hallacoef(coef,ang);sum+=coef[0];rotar_2d_hallacoef(coef,ang);sum+=coef[0];
			rotar_2d_hallacoef(coef,ang);sum+=coef[0];rotar_2d_hallacoef(coef,ang);sum+=coef[0];
			rotar_2d_hallacoef(coef,ang);sum+=coef[0];rotar_2d_hallacoef(coef,ang);sum+=coef[0];
			rotar_2d_hallacoef(coef,ang);sum+=coef[0];rotar_2d_hallacoef(coef,ang);sum+=coef[0];
		}
		timer("Coef      calculus using floats  ",10*N);
		for(int i=0;i<N;i++)
		{
			in[0]=((float) (i%5000))/5000.0f;
			rotar_2d(coef,in,out);sum+=out[0];rotar_2d(coef,out,in);sum+=in[0];
			rotar_2d(coef,in,out);sum+=out[0];rotar_2d(coef,out,in);sum+=in[0];
			rotar_2d(coef,in,out);sum+=out[0];rotar_2d(coef,out,in);sum+=in[0];
			rotar_2d(coef,in,out);sum+=out[0];rotar_2d(coef,out,in);sum+=in[0];
			rotar_2d(coef,in,out);sum+=out[0];rotar_2d(coef,out,in);sum+=in[0];
		}
		timer("Rotations calculus using floats  ",10*N);
		cout<<"\t\t\t\t\t\t\t\t\t  ignore:"<<sum<<endl;
	}

	{//speed test double:
		double coef[4];
		double in[2]={1.1,1.2},out[2];
		double sum=0.0;
		int N=10000000;
		timer();//set to zero
		for(int i=0;i<N;i++)
		{
			double ang=((double) (i%5000))/5000.0;
			rotar_2d_hallacoef(coef,ang);sum+=coef[0];rotar_2d_hallacoef(coef,ang);sum+=coef[0];
			rotar_2d_hallacoef(coef,ang);sum+=coef[0];rotar_2d_hallacoef(coef,ang);sum+=coef[0];
			rotar_2d_hallacoef(coef,ang);sum+=coef[0];rotar_2d_hallacoef(coef,ang);sum+=coef[0];
			rotar_2d_hallacoef(coef,ang);sum+=coef[0];rotar_2d_hallacoef(coef,ang);sum+=coef[0];
			rotar_2d_hallacoef(coef,ang);sum+=coef[0];rotar_2d_hallacoef(coef,ang);sum+=coef[0];
		}
		timer("Coef      calculus using doubles ",10*N);
		for(int i=0;i<N;i++)
		{
			in[0]=((double) (i%5000))/5000.0;
			rotar_2d(coef,in,out);sum+=out[0];rotar_2d(coef,out,in);sum+=in[0];
			rotar_2d(coef,in,out);sum+=out[0];rotar_2d(coef,out,in);sum+=in[0];
			rotar_2d(coef,in,out);sum+=out[0];rotar_2d(coef,out,in);sum+=in[0];
			rotar_2d(coef,in,out);sum+=out[0];rotar_2d(coef,out,in);sum+=in[0];
			rotar_2d(coef,in,out);sum+=out[0];rotar_2d(coef,out,in);sum+=in[0];
		}
		timer("Rotations calculus using doubles ",10*N);

		cout<<"\t\t\t\t\t\t\t\t\t  ignore:"<<sum<<endl;
	}

	{//speed test short:
		double coef[4];
		short in[2]={1,2},out[2];
		double sum=0.0;
		int N=10000000;
		timer();//set to zero
		for(int i=0;i<N;i++)
		{
			double ang=((double) (i%5000))/5000.0;
			rotar_2d_hallacoef(coef,ang);sum+=coef[0];rotar_2d_hallacoef(coef,ang);sum+=coef[0];
			rotar_2d_hallacoef(coef,ang);sum+=coef[0];rotar_2d_hallacoef(coef,ang);sum+=coef[0];
			rotar_2d_hallacoef(coef,ang);sum+=coef[0];rotar_2d_hallacoef(coef,ang);sum+=coef[0];
			rotar_2d_hallacoef(coef,ang);sum+=coef[0];rotar_2d_hallacoef(coef,ang);sum+=coef[0];
			rotar_2d_hallacoef(coef,ang);sum+=coef[0];rotar_2d_hallacoef(coef,ang);sum+=coef[0];
		}
		timer("Coef      calculus using shorts  ",10*N);
		short sum2=(short) sum;
		for(int i=0;i<N;i++)
		{
			in[0]=(short) i%5000;
			rotar_2d(coef,in,out);sum2+=out[0];rotar_2d(coef,out,in);sum2+=in[0];
			rotar_2d(coef,in,out);sum2+=out[0];rotar_2d(coef,out,in);sum2+=in[0];
			rotar_2d(coef,in,out);sum2+=out[0];rotar_2d(coef,out,in);sum2+=in[0];
			rotar_2d(coef,in,out);sum2+=out[0];rotar_2d(coef,out,in);sum2+=in[0];
			rotar_2d(coef,in,out);sum2+=out[0];rotar_2d(coef,out,in);sum2+=in[0]; 
		}
		timer("Rotations calculus using shorts  ",10*N);
		cout<<"\t\t\t\t\t\t\t\t\t  ignore:"<<sum<<endl;
	}
}