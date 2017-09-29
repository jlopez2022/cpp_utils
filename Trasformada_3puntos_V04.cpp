/*  transformada3P convierte 
 una coordenada bidimensional: xy1 referida a las coordenadas "coor1" 
 a otra coordenada           : xy2 referida a las coordenadas "coor2" 
 La función trasformada3p_hallacoef() halla el vector de trasformada a[6], devuelve 0 si hay error de división por 0  
 La función transformada3P trasforma el vactor bidimensional xy1[2]={x1,y1} en otro xy2[2]={x2,y2} empleando el vector de trasformada a[6] 

 Las coordenadas coorn[6]={(x0,y0),(x1,y1),(x2,y2)} donde x0,y0=origen de coordenadas

 V04: It is introducted an struct s_xy_bgr that stores x,y and bgr of a coordinate
      Chapter 3: Introducted with new transform that calculates colour in a 2 axis coordinates when p0=origen and p1-p0 & p2-p0 the axes
	  It is calculated new colour in any x,y coordinate. It is extremely fast.
	  Chapter 4: New transform that calculates using expected delta colour with respect ani other point but changing values in the same manner
	  than does v1 and v2 with respect v0.
	  Chapter 4: trasformada3p_vect_dif() is a very ckick function. Also coef[6] is calculated at a high speed rate.

 */


#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

//=================================================================================================
//1. Halla el vector de trasformada coef[6] que trasforma un sistema de coordenadas coor1 en otro coor2
int trasformada3p_hallacoef(__int16 coor1[6],__int16 coor2[6],double coef[6]); 
/*  transformada3P usa el vector de trasformada a[6] para trasformar. ES EL MAS RAPIDO, hace casi una trasformada por ciclo de reloj (2.5 giga trasformadas/seg empleando 1 nucleo de 3.2Ghz) 
    la coordenada bidimensional: xy1 referida a las coordenadas "coor1" 
   a otra coordenada           : xy2 referida a las coordenadas "coor2" */
void transformada3P(double coef[6],__int16 xy1[2],__int16 xy2[2]);
//=================================================================================================
//2. version float:
int trasformada3p_hallacoef(__int16 coor1[6],__int16 coor2[6],float coef[6]); 
void transformada3P(float coef[6],__int16 xy1[2],__int16 xy2[2]);
//=================================================================================================
//3. trasformada3p_vect
typedef unsigned char uchar;
struct s_xy_bgr  //contains coordinates x,y and colour
{
	__int16 x,y;
	uchar bgr[3];
};
int trasformada3p_vect_hallacoef(s_xy_bgr v0,s_xy_bgr v1,s_xy_bgr v2,double coef[9]);
void trasformada3p_vect(double coef[9],s_xy_bgr &vn);
double invierte3x3(__int16 *ax,double *bx);//Hace 25 megainversiones/segundo
//OJO: y sale traspuesta!!
void multiplica3x3(__int16 *ax,double *bx,double *cx);//calcula cx=ax*bx. Multiplica 53millones de pares de matrices por segundo
void multiplica3x3(double *ax,__int16 *bx,double *cx);//multiplica cx=ax*bx
//===================================================================================================
//4. trasformada que calcula la diferencia de bgr en funcion de la diferencia de coordenadas respecto de otro origen de coordenadas
int trasformada3p_vect_dif_hallacoef(s_xy_bgr v0,s_xy_bgr v1,s_xy_bgr v2,double coef[6]);
//calculates v1.bgr as a function of: v0,  v1.x and v1.y. Where v0 is the new coordinates system. Uses coef[6] array calculated in the previous function
void trasformada3p_vect_dif(double coef[6],s_xy_bgr &v0,s_xy_bgr &v1);
//===================================================================================================


//OTHERS:
/*  transformada3P de coordenadas x,y. No probadas 
 una coordenada bidimensional: xy1 referida a las coordenadas "coor1" 
 a otra coordenada           : xy2 referida a las coordenadas "coor2" 
 La función devuelve 0 si hay error de división por 0  */
int transformada3P(__int16 coor1[6],__int16 coor2[6],__int16 xy1[2],__int16 xy2[2]);
/* La velocidad (modo release) es 103 millones de trasformadas/segundo con micro de 3.2Ghz empleando 1 nucleo*/
int transformada3P(double coor1[6],double coor2[6],double xy1[2],double xy2[2]);



time_t start,stop;char null_char='\0';
//Use empty timer() to reset start time:
void timer(char *title=&null_char,int data_size=1){    	stop=clock();	if (*title) printf("%s time = %7lg = %7lg MOPs\n",title,(double) (stop-start)/(double) CLOCKS_PER_SEC, 1e-6*data_size/( (double)(stop-start)/(double)CLOCKS_PER_SEC ) ); 	start=clock(); }

int main()
{
	cout << "Perform test in Release mode. Timing results will be wrong in Debug mode" <<endl;

	//0. Inicializacion  
	__int16 coor1[6]={-50,100,50,100,0,-50};
	__int16 coor2[6]={-25,50 ,30,50 ,5,-25};
	__int16 xy1[2],xy2[2];
	//inicializo:
	__int16 xy11[100][2],*p1;
	long i;
	for (i=0;i<100;i++)
	{
		xy11[i][0]=(rand() % 200);
		xy11[i][1]=(rand() % 200);
	}

	//===================================================================================
	cout<<"==================================================================================="<<endl;
	cout<<"=== Test de transformada3P  double ================================================"<<endl;
	{   // 1. Test de transformada3P  double 
		double tras1[6];//vector de la trasformada
		trasformada3p_hallacoef(coor1,coor2,tras1);

		double tras2[6];//vector de la trasformada inversa
		trasformada3p_hallacoef(coor2,coor1,tras2);

		for (i=0;i<3;i++)
		{	//compruebo que las tres coordenadas coor1 van a las otras tres coordenadas coor2
			//transformada3P(coor1,coor2,coor1+i*2,xy2);printf("\nx1=%lg y1=%lg x2=%lg y2=%lg",coor1[i*2],coor1[i*2+1],xy2[0],xy2[1]);
			xy1[0]=coor1[i*2];xy1[1]=coor1[i*2+1];
			transformada3P(tras1,xy1,xy2);printf("\nx1=%3i y1=%3i x2=%3i y2=%3i",coor1[i*2],coor1[i*2+1],xy2[0],xy2[1]);
		}

		for (i=0;i<3;i++)
		{	//compruebo que las tres coordenadas coor1 van a las otras tres coordenadas coor2
			transformada3P(coor1,coor2,coor1+i*2,xy2);printf("\nx1=%3i y1=%3i x2=%3i y2=%3i",coor1[i*2],coor1[i*2+1],xy2[0],xy2[1]);
		}


		cout<<"\n\n=== Calculus using double ==="<<endl;
		double sumerror1=0.0;
		long NUM=50000000;
		//Calculo el tiempo de calcular rands:
		timer();//resets timer
		for (i=0;i<NUM;i++)
		{
			p1=&xy11[i%100][0];
			__int16 xy3[2];
			transformada3P(tras1,p1,xy2);//directa a coor2
			transformada3P(tras2,xy2,xy3);//inversa a coor1 de nuevo

			double x,error;
			x=xy3[0]-p1[0];error= x*x;//comentar para test de velocidad
			x=xy3[1]-p1[1];error+=x*x;//comentar para test de velocidad
			sumerror1+=error;		   //Para test de velocidad sustituir por sumaerror1+=xy3[0] si no evitará el loop entero
		}
		sumerror1=sqrt(sumerror1/NUM);
		printf("Error medio=%lg\n",sumerror1);
		timer("1. Test de transformada3P double ", 2*NUM);
		cout<<"==================================================================================="<<endl;
	}

	//===================================================================================
	cout<<endl<<"==================================================================================="<<endl;
	cout<<"=== Test de transformada3P  float  ================================================"<<endl;
	{   // 2. Test de transformada3P  float 
		float tras1[6];//vector de la trasformada
		trasformada3p_hallacoef(coor1,coor2,tras1);

		float tras2[6];//vector de la trasformada inversa
		trasformada3p_hallacoef(coor2,coor1,tras2);

		cout<<"\n\n=== Calculus using float  ==="<<endl;
		double sumerror1=0.0;
		long NUM=50000000;
		//Calculo el tiempo de calcular rands:
		timer();//resets timer
		for (i=0;i<NUM;i++)
		{
			p1=&xy11[i%100][0];
			__int16 xy3[2];
			transformada3P(tras1,p1,xy2);//directa a coor2
			transformada3P(tras2,xy2,xy3);//inversa a coor1 de nuevo

			double x,error;
			x=xy3[0]-p1[0];error= x*x;//comentar para test de velocidad
			x=xy3[1]-p1[1];error+=x*x;//comentar para test de velocidad 
			sumerror1+= error;		   //Para test de velocidad sustituir por sumaerror1+=xy3[0] si no evitará el loop entero 
		}
		sumerror1=sqrt(sumerror1/NUM);
		printf("Error medio=%lg\n",sumerror1);
		timer("2. Test de transformada3P float  ", 2*NUM);
		cout<<"==================================================================================="<<endl;
	}

	//===================================================================================
	cout<<endl<<"==================================================================================="<<endl;
	cout      <<"=== 3. Test de transformada3p_vect() =============================================="<<endl;
	{   // 3. Test de transformada3p_vect()
		s_xy_bgr p0{100,100,{ 25, 30, 35}};
		s_xy_bgr p1{120,150,{120,130,135}};
		s_xy_bgr p2{ 70,175,{ 70,230,235}};
		s_xy_bgr pn;
		double coef[9];
		int error;uchar *bgr;
		trasformada3p_vect_hallacoef(p0,p1,p2,coef);

		pn=p0;pn.bgr[0]=pn.bgr[1]=pn.bgr[2]=0;
		trasformada3p_vect(coef,pn);
		bgr=p0.bgr;error=labs(bgr[0]-pn.bgr[0])+labs(bgr[1]-pn.bgr[1])+labs(bgr[2]-pn.bgr[2]);
		cout<<"3. Test de transformada3p_vect() error 0="<<error<<endl;

		pn=p1;pn.bgr[0]=pn.bgr[1]=pn.bgr[2]=0;
		trasformada3p_vect(coef,pn);
		bgr=p1.bgr;error=labs(bgr[0]-pn.bgr[0])+labs(bgr[1]-pn.bgr[1])+labs(bgr[2]-pn.bgr[2]);
		cout<<"3. Test de transformada3p_vect() error 1="<<error<<endl;

		pn=p2;pn.bgr[0]=pn.bgr[1]=pn.bgr[2]=0;
		trasformada3p_vect(coef,pn);
		bgr=p2.bgr;error=labs(bgr[0]-pn.bgr[0])+labs(bgr[1]-pn.bgr[1])+labs(bgr[2]-pn.bgr[2]);
		cout<<"3. Test de transformada3p_vect() error 2="<<error<<endl;

		pn.x=(__int16) (0.5+(p0.x+p1.x+p2.x)/3.0);
		pn.y=(__int16) (0.5+(p0.y+p1.y+p2.y)/3.0);
		pn.bgr[0]=pn.bgr[1]=pn.bgr[2]=0;
		uchar bgr2[3];for (int i=0;i<3;i++) bgr2[i]=(uchar) (0.5+(p0.bgr[i]+p1.bgr[i]+p2.bgr[i])/3.0);
		trasformada3p_vect(coef,pn);
		bgr=bgr2;error=labs(bgr[0]-pn.bgr[0])+labs(bgr[1]-pn.bgr[1])+labs(bgr[2]-pn.bgr[2]);
		cout<<"3. Test de transformada3p_vect() error 3="<<error<<" (debe ser <6)"<<endl;

		//test velocidad:
		double sumerror1=0.0;
		long NUM=50000000;
		//Calculo el tiempo de calcular rands:
		timer();//resets timer
		int sumatonta=0;
		for (int i=0;i<NUM;i++)
		{
			pn.x++;
			trasformada3p_vect(coef,pn);
			sumatonta+=pn.bgr[0];
		}
		timer("3. Test de velocidad de transformada3P_vect()              ", NUM);
		double sumatonta2=sumatonta;//para obligar hacer el test al optimizador
		for (int i=0;i<NUM;i++)
		{
			p2.x++;
			trasformada3p_vect_hallacoef(p0,p1,p2,coef);
			sumatonta2+=coef[0];
		}
		timer("3. Test de velocidad de trasformada3p_vect_hallacoef()     ", NUM);
		cout<<"                                                                 kaka a ignorar="<<sumatonta2<<endl; //para obligar hacer el test al optimizador
		cout<<"==================================================================================="<<endl;
	}


	//===================================================================================
	cout<<endl<<"==================================================================================="<<endl;
	cout      <<"=== 4. Test de transformada3p_vect_dif============================================="<<endl;
	{   // 4. Test de transformada3p_vect()
		s_xy_bgr p0{100,100,{ 25, 30, 35}};
		s_xy_bgr p1{120,150,{120,130,120}};
		s_xy_bgr p2{ 70,175,{ 70,230,225}};
		s_xy_bgr pn;
		double coef[6];
		int error;uchar *bgr;
		trasformada3p_vect_dif_hallacoef(p0,p1,p2,coef);

		pn=p0;pn.bgr[0]=pn.bgr[1]=pn.bgr[2]=0;
		trasformada3p_vect_dif(coef,p0,pn);
		bgr=p0.bgr;error=labs(bgr[0]-pn.bgr[0])+labs(bgr[1]-pn.bgr[1])+labs(bgr[2]-pn.bgr[2]);
		cout<<"4. Test de trasformada3p_vect_dif() error 0="<<error<<endl;

		pn=p1;pn.bgr[0]=pn.bgr[1]=pn.bgr[2]=0;
		trasformada3p_vect_dif(coef,p0,pn);
		bgr=p1.bgr;error=labs(bgr[0]-pn.bgr[0])+labs(bgr[1]-pn.bgr[1])+labs(bgr[2]-pn.bgr[2]);
		cout<<"4. Test de trasformada3p_vect_dif() error 1="<<error<<endl;

		pn=p2;pn.bgr[0]=pn.bgr[1]=pn.bgr[2]=0;
		trasformada3p_vect_dif(coef,p0,pn);
		bgr=p2.bgr;error=labs(bgr[0]-pn.bgr[0])+labs(bgr[1]-pn.bgr[1])+labs(bgr[2]-pn.bgr[2]);
		cout<<"4. Test de trasformada3p_vect_dif() error 2="<<error<<endl;

		pn.x=(__int16) (0.5+(p0.x+p1.x+p2.x)/3.0);
		pn.y=(__int16) (0.5+(p0.y+p1.y+p2.y)/3.0);
		pn.bgr[0]=pn.bgr[1]=pn.bgr[2]=0;
		uchar bgr2[3];for (int i=0;i<3;i++) bgr2[i]=(uchar) (0.5+(p0.bgr[i]+p1.bgr[i]+p2.bgr[i])/3.0);
		trasformada3p_vect_dif(coef,p0,pn);
		bgr=bgr2;error=labs(bgr[0]-pn.bgr[0])+labs(bgr[1]-pn.bgr[1])+labs(bgr[2]-pn.bgr[2]);
		cout<<"4. Test de trasformada3p_vect_dif() error 3="<<error<<" (debe ser <6)"<<endl;

		//test velocidad:
		double sumerror1=0.0;
		long NUM=50000000;
		//Calculo el tiempo de calcular rands:
		timer();//resets timer
		int sumatonta=0;
		for (int i=0;i<NUM;i++)
		{
			pn.x++;
			trasformada3p_vect_dif(coef,p0,pn);
			sumatonta+=pn.bgr[0];
		}
		timer("4. Test de velocidad de trasformada3p_vect_dif()           ", NUM);
		double sumatonta2=sumatonta;//para obligar hacer el test al optimizador
		for (int i=0;i<NUM;i++)
		{
			p2.x++;
			trasformada3p_vect_dif_hallacoef(p0,p1,p2,coef);
			sumatonta2+=coef[0];
		}
		timer("4. Test de velocidad de trasformada3p_vect_dif_hallacoef() ", NUM);
		cout<<"                                                                 kaka a ignorar="<<sumatonta2<<endl; //para obligar hacer el test al optimizador
		cout<<"==================================================================================="<<endl;
	}

	printf("\n\n===FIN===");getchar();getchar();
	return 1;
}

//coor[6]=ojo izq (x,y), ojo derecho (x,y) y boca (x,y). Retorna 0 si fail
/*  transformada3P convierte 
 una coordenada bidimensional: xy1 referida a grupo de 3 puntos  "coor1" 
 a otra coordenada           : xy2 referida a otros    3 puntos  "coor2" 
 La función devuelve 0 si hay error de división por 0  */
int transformada3P(__int16 coor1[6],__int16 coor2[6],__int16 xy1[2],__int16 xy2[2])
{
	long x10=coor1[2]-coor1[0];
	long x20=coor1[4]-coor1[0];
	long x30=xy1[0]  -coor1[0]; 
	long y10=coor1[3]-coor1[1];
	long y20=coor1[5]-coor1[1];
	long y30=xy1[1]  -coor1[1]; 
	double det;det=x10*y20-y10*x20;
	if (det==0) return 0;//fail
	double k1;k1=1.0*(x30*y20-x20*y30)/det;
	double k2;k2=1.0*(x10*y30-y10*x30)/det;
	       //x0         x1       x0            x2       x0   
	xy2[0]=(__int16) (0.5+coor2[0]+k1*(coor2[2]-coor2[0])+k2*(coor2[4]-coor2[0]));
	xy2[1]=(__int16) (0.5+coor2[1]+k1*(coor2[3]-coor2[1])+k2*(coor2[5]-coor2[1]));
	return 1;//ok
}

//coor[6]=ojo izq (x,y), ojo derecho (x,y) y boca (x,y). Retorna 0 si fail
/*  transformada3P convierte 
 una coordenada bidimensional: xy1 referida a las coordenadas "coor1" 
 a otra coordenada           : xy2 referida a las coordenadas "coor2" 
 La función devuelve 0 si hay error de división por 0  */
int transformada3P(double coor1[6],double coor2[6],double xy1[2],double xy2[2])
{
	double x10=coor1[2]-coor1[0];
	double x20=coor1[4]-coor1[0];
	double x30=xy1[0]  -coor1[0]; 
	double y10=coor1[3]-coor1[1];
	double y20=coor1[5]-coor1[1];
	double y30=xy1[1]  -coor1[1]; 
	double det;det=x10*y20-y10*x20;
	if (det==0) return 0;//fail
	double k1;k1=1.0*(x30*y20-x20*y30)/det;
	double k2;k2=1.0*(x10*y30-y10*x30)/det;
	       //x0         x1       x0            x2       x0   
	xy2[0]=coor2[0]+k1*(coor2[2]-coor2[0])+k2*(coor2[4]-coor2[0]);
	xy2[1]=coor2[1]+k1*(coor2[3]-coor2[1])+k2*(coor2[5]-coor2[1]);
	return 1;//ok
}

//Halla el vector de trasformada a[6]
//En a[6] viajan juntos a[] y b[], siendo: a[6]= {a[0],a[1],a[2], b[0],b[1],b[2]}
int trasformada3p_hallacoef(__int16 coor1[6],__int16 coor2[6],double a[6]) 
{
	double *b=a+3;
	double x10=coor1[2]-coor1[0];
	double x20=coor1[4]-coor1[0];
	double y10=coor1[3]-coor1[1];
	double y20=coor1[5]-coor1[1];
	double x11=coor2[2]-coor2[0];
	double x21=coor2[4]-coor2[0];
	double y11=coor2[3]-coor2[1];
	double y21=coor2[5]-coor2[1];
	double det;det=x10*y20-y10*x20;
	if (det==0) return 0;//fail
	a[0]=coor2[0]+  (  -coor1[0]*x11*y20 + coor1[1]*x11*x20 -coor1[1]*x21*x10 +x21*y10*coor1[0] )/det;					//a[0] se multiplica por 1 para hallar x'
	a[1]=( y20*x11 - y10*x21) /det; //a[1] se multiplica por x para hallar x'
	a[2]=(-x20*x11 + x10*x21) /det; //a[2] se multiplica por y para hallar x'
	b[0]=coor2[1]+  (  -coor1[0]*y11*y20 + coor1[1]*y11*x20 -coor1[1]*y21*x10 +y21*y10*coor1[0] )/det;					//b[0] se multiplica por 1 para hallar y'
	b[1]=( y20*y11 - y10*y21) /det; //b[1] se multiplica por x para hallar y'
	b[2]=(-x20*y11 + x10*y21) /det; //b[2] se multiplica por y para hallar y'
	return 1;
}

//Usa el vector de trasformada a[6] calculado en la funcion anterior
void transformada3P(double a[6],__int16 xy1[2],__int16 xy2[2])
{
	xy2[0]=(__int16) (0.5+a[0]+a[1]*xy1[0]+a[2]*xy1[1]);
	double *b=a+3;                                         //a[6]= {a[0],a[1],a[2], b[0],b[1],b[2]}
	xy2[1]=(__int16) (0.5+b[0]+b[1]*xy1[0]+b[2]*xy1[1]);
}



//float
int trasformada3p_hallacoef(__int16 coor1[6],__int16 coor2[6],float a[6]) 
{
	float *b=a+3;
	float x10=(float) (coor1[2]-coor1[0]);
	float x20=(float) (coor1[4]-coor1[0]);
	float y10=(float) (coor1[3]-coor1[1]);
	float y20=(float) (coor1[5]-coor1[1]);
	float x11=(float) (coor2[2]-coor2[0]);
	float x21=(float) (coor2[4]-coor2[0]);
	float y11=(float) (coor2[3]-coor2[1]);
	float y21=(float) (coor2[5]-coor2[1]);
	float det;det=(float) (x10*y20-y10*x20);
	if (det==0) return 0;//fail
	a[0]=coor2[0]+  (  -coor1[0]*x11*y20 + coor1[1]*x11*x20 -coor1[1]*x21*x10 +x21*y10*coor1[0] )/det;					//a[0] se multiplica por 1 para hallar x'
	a[1]=( y20*x11 - y10*x21) /det; //a[1] se multiplica por x para hallar x'
	a[2]=(-x20*x11 + x10*x21) /det; //a[2] se multiplica por y para hallar x'
	b[0]=coor2[1]+  (  -coor1[0]*y11*y20 + coor1[1]*y11*x20 -coor1[1]*y21*x10 +y21*y10*coor1[0] )/det;					//b[0] se multiplica por 1 para hallar y'
	b[1]=( y20*y11 - y10*y21) /det; //b[1] se multiplica por x para hallar y'
	b[2]=(-x20*y11 + x10*y21) /det; //b[2] se multiplica por y para hallar y'
	return 1;
}

//Usa el vector de trasformada a[6] calculado en la funcion anterior
void transformada3P(float a[6],__int16 xy1[2],__int16 xy2[2])
{
	xy2[0]=(__int16) (0.5+a[0]+a[1]*xy1[0]+a[2]*xy1[1]);
	float *b=a+3;                                         //a[6]= {a[0],a[1],a[2], b[0],b[1],b[2]}
	xy2[1]=(__int16) (0.5+b[0]+b[1]*xy1[0]+b[2]*xy1[1]);
}




//3. ==================================================================================
int trasformada3p_vect_hallacoef(s_xy_bgr v0,s_xy_bgr v1,s_xy_bgr v2,double coef[9])
{
	__int16 ax[9]={
		v0.x,v0.y,1,
		v1.x,v1.y,1,
		v2.x,v2.y,1 	};
	double bx[9];
	if (invierte3x3(ax,bx)==0) return 0;

	__int16 cx[9]={
		(__int16 )v0.bgr[0],(__int16 )v0.bgr[1],(__int16 )v0.bgr[2],
		(__int16 )v1.bgr[0],(__int16 )v1.bgr[1],(__int16 )v1.bgr[2],
		(__int16 )v2.bgr[0],(__int16 )v2.bgr[1],(__int16 )v2.bgr[2] };

	multiplica3x3(bx,cx,coef);
	return 1;
}
void trasformada3p_vect(double coef[9],s_xy_bgr &vn)
{
	uchar *bgr=vn.bgr;
	__int16 a[3]={vn.x,vn.y,1};
	bgr[0]=(uchar) (0.5+a[0]*coef[0]+a[1]*coef[3]+a[2]*coef[6]);
	bgr[1]=(uchar) (0.5+a[0]*coef[1]+a[1]*coef[4]+a[2]*coef[7]);
	bgr[2]=(uchar) (0.5+a[0]*coef[2]+a[1]*coef[5]+a[2]*coef[8]);
}

double invierte3x3(__int16 *ax,double *bx)
{
	__int16 (*a)[3]= (__int16 (*)[3]) ax;
	double  (*b)[3]= (double  (*)[3]) bx;

	double det =     a[0][0]*(a[1][1]*a[2][2]-a[2][1]*a[1][2])
							-a[0][1]*(a[1][0]*a[2][2]-a[1][2]*a[2][0])
							+a[0][2]*(a[1][0]*a[2][1]-a[1][1]*a[2][0]);
	if (det==0) return 0;
	b[0][0] =  (a[1][1]*a[2][2]-a[2][1]*a[1][2])/det;
	b[0][1] = -(a[0][1]*a[2][2]-a[0][2]*a[2][1])/det;
	b[0][2] =  (a[0][1]*a[1][2]-a[0][2]*a[1][1])/det;
	b[1][0] = -(a[1][0]*a[2][2]-a[1][2]*a[2][0])/det;
	b[1][1] =  (a[0][0]*a[2][2]-a[0][2]*a[2][0])/det;
	b[1][2] = -(a[0][0]*a[1][2]-a[1][0]*a[0][2])/det;
	b[2][0] =  (a[1][0]*a[2][1]-a[2][0]*a[1][1])/det;
	b[2][1] = -(a[0][0]*a[2][1]-a[2][0]*a[0][1])/det;
	b[2][2] =  (a[0][0]*a[1][1]-a[1][0]*a[0][1])/det;
	return det;
}

void multiplica3x3(__int16 *ax,double *bx,double *cx)//multiplica cx=ax*bx
{
	__int16 (*a)[3]= (__int16 (*)[3]) ax;
	double  (*b)[3]= (double  (*)[3]) bx;
	double  (*c)[3]= (double  (*)[3]) cx;
	c[0][0]=a[0][0]*b[0][0]+a[0][1]*b[1][0]+a[0][2]*b[2][0];
	c[0][1]=a[0][0]*b[0][1]+a[0][1]*b[1][1]+a[0][2]*b[2][1];
	c[0][2]=a[0][0]*b[0][2]+a[0][1]*b[1][2]+a[0][2]*b[2][2];

	c[1][0]=a[1][0]*b[0][0]+a[1][1]*b[1][0]+a[1][2]*b[2][0];
	c[1][1]=a[1][0]*b[0][1]+a[1][1]*b[1][1]+a[1][2]*b[2][1];
	c[1][2]=a[1][0]*b[0][2]+a[1][1]*b[1][2]+a[1][2]*b[2][2];

	c[2][0]=a[2][0]*b[0][0]+a[2][1]*b[1][0]+a[2][2]*b[2][0];
	c[2][1]=a[2][0]*b[0][1]+a[2][1]*b[1][1]+a[2][2]*b[2][1];
	c[2][2]=a[2][0]*b[0][2]+a[2][1]*b[1][2]+a[2][2]*b[2][2];
}

void multiplica3x3(double *ax,__int16 *bx,double *cx)//multiplica cx=ax*bx
{
	double  (*a)[3]= (double  (*)[3]) ax;
	__int16 (*b)[3]= (__int16 (*)[3]) bx;
	double  (*c)[3]= (double  (*)[3]) cx;
	c[0][0]=a[0][0]*b[0][0]+a[0][1]*b[1][0]+a[0][2]*b[2][0];
	c[0][1]=a[0][0]*b[0][1]+a[0][1]*b[1][1]+a[0][2]*b[2][1];
	c[0][2]=a[0][0]*b[0][2]+a[0][1]*b[1][2]+a[0][2]*b[2][2];

	c[1][0]=a[1][0]*b[0][0]+a[1][1]*b[1][0]+a[1][2]*b[2][0];
	c[1][1]=a[1][0]*b[0][1]+a[1][1]*b[1][1]+a[1][2]*b[2][1];
	c[1][2]=a[1][0]*b[0][2]+a[1][1]*b[1][2]+a[1][2]*b[2][2];

	c[2][0]=a[2][0]*b[0][0]+a[2][1]*b[1][0]+a[2][2]*b[2][0];
	c[2][1]=a[2][0]*b[0][1]+a[2][1]*b[1][1]+a[2][2]*b[2][1];
	c[2][2]=a[2][0]*b[0][2]+a[2][1]*b[1][2]+a[2][2]*b[2][2];
}
//3. ==================================================================================


//4. ==================================================================================

int trasformada3p_vect_dif_hallacoef(s_xy_bgr v0,s_xy_bgr v1,s_xy_bgr v2,double coef[6])
{
	//inverse of dif array:
	__int16 dx01=v1.x-v0.x;
	__int16 dy01=v1.y-v0.y;
	__int16 dx02=v2.x-v0.x;
	__int16 dy02=v2.y-v0.y;
	int mdet=dx01*dy02-dx02*dy01;
	if (mdet==0) return 0;
	double det=(double) 1.0/mdet;
	double inv[4]={det*dy02, -det*dx02, -det*dy01, det*dx01};
	coef[0]=inv[0]*(v1.bgr[0]-v0.bgr[0])+inv[2]*(v2.bgr[0]-v0.bgr[0]);	coef[1]=inv[0]*(v1.bgr[1]-v0.bgr[1])+inv[2]*(v2.bgr[1]-v0.bgr[1]);	coef[2]=inv[0]*(v1.bgr[2]-v0.bgr[2])+inv[2]*(v2.bgr[2]-v0.bgr[2]);		
	coef[3]=inv[1]*(v1.bgr[0]-v0.bgr[0])+inv[3]*(v2.bgr[0]-v0.bgr[0]);	coef[4]=inv[1]*(v1.bgr[1]-v0.bgr[1])+inv[3]*(v2.bgr[1]-v0.bgr[1]);	coef[5]=inv[1]*(v1.bgr[2]-v0.bgr[2])+inv[3]*(v2.bgr[2]-v0.bgr[2]);		
	return mdet;
}
//calculates v1.bgr as a function of: v0,  v1.x and v1.y. Where v0 is the new coordinates system
void trasformada3p_vect_dif(double coef[3],s_xy_bgr &v0,s_xy_bgr &v1)
{
	__int16 dx=v1.x-v0.x;
	__int16 dy=v1.y-v0.y;
	double dif;
	//calculo para r:
	dif=coef[0]*dx+coef[3]*dy;v1.bgr[0]=v0.bgr[0]+(uchar)(0.5+dif);
	//calculo para g:
	dif=coef[1]*dx+coef[4]*dy;v1.bgr[1]=v0.bgr[1]+(uchar)(0.5+dif);
	//calculo para b:
	dif=coef[2]*dx+coef[5]*dy;v1.bgr[2]=v0.bgr[2]+(uchar)(0.5+dif);
}