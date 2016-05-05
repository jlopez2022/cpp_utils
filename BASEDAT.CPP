#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define TOP 512*1024     //Máximo número de datos en la base de datos (512k*size(double))
#define TOPCABEZA 400    //Máximo número de variables
#define BASE 1           //BASE = 1 o 0 si los índices comienzan en 1 o 0
typedef char ch32[32]; 
typedef char ch9[9]; 
typedef unsigned long ulong;

void mensaje(int level,char *errlin);

void __stdcall ANSERR
(
int    *level,    //Nivel: 1,2,3,4=nota,warning,error o fatal
char   *errlin,   //línea error
unsigned int long_ch1,  
double *dpin,     //Número doble precisión
ch32   *chin,     //Vector de hasta 32 caracteres conteniendo el texto del mensaje
unsigned int long_ch2
);

//double matriz[TOP];           //base de datos double

class Basedatos
{
public:
// 1. Estructuras públicas:
typedef unsigned long ulong;

struct Cabeza
   {
   ch9 nombre;
   ulong dimxyz[3];
   ulong inicio;
   };

union
   {
   ch9 label9;
   double dp;
   } conversion;

// 2. Funciones públicas:

Basedatos();
~Basedatos();
ulong metedato   (ch9 *label9,ulong *nxyz,double *dato);
ulong leedato    (ch9 *label9,ulong *nxyz,double *dato);
int creacabeza   (ch9 *label9,ulong *dimxyz);
double prueba_lectura_base_datos(ulong i); 

private:

ulong miradato   (ch9 *label9,ulong *nxyz);
int buscacabeza  (ch9 *label9);

Cabeza *cabeza;
double *matriz;           //base de datos double
int    ultimacabeza;     
ulong  ultimodato;       
};



Basedatos::Basedatos()
  {
  cabeza=new Cabeza[TOPCABEZA];
  ultimacabeza=0;
  ultimodato=1;
  matriz=new double[TOP];
  };

Basedatos::~Basedatos()
  { 
  delete[] cabeza; 
  delete[] matriz;
  }

ulong Basedatos::miradato (ch9 *label9,ulong *nxyz)
   {
   int i,numcabeza;
   ulong posicion;

   for (i=0;i<8;i++) label9[0][i]=tolower(label9[0][i]);


   label9[0][8]='\0';
   numcabeza=buscacabeza(label9);
   if (numcabeza==-1)
      {
      char lin[256]="En base de datos: No encontrada la variable o matriz : ";
      strcat(&lin[0],&label9[0][0]);
      mensaje(2,lin);
      return(0);
      }

      {//inicio de bloque comprobación de dimensiones
      char  linea[256],lin2[64],lineb[256];
      int error=0;
      ulong posicion=0;
      linea[0]='\0';
      lineb[0]='\0';
      for (i=0;i<3;i++)
         {
         if (nxyz[i]>=cabeza[numcabeza].dimxyz[i]) error=1;
         if (nxyz[i]<0) error=1;
         }
      if (error) 
         {
         for (i=0;i<3;i++)
            {
            _ultoa(nxyz[i]+BASE,lin2,10);
            strcat(lin2,",");
            strcat(linea,lin2);
            _ultoa(cabeza[numcabeza].dimxyz[i],lin2,10);
            strcat(lin2,",");
            strcat (lineb,lin2);
            }

         strcat(linea," Fuera de rango de la matriz ");
         strcat(linea,&label9[0][0]); 
         strcat(linea,"(");
         strcat(linea,lineb); 
         strcat(linea,")");
         mensaje(3,linea);
         return(0);
         }
      }// fin de bloque

   posicion=cabeza[numcabeza].inicio 
            + nxyz[0] 
            + nxyz[1] * cabeza[numcabeza].dimxyz[0] 
            + nxyz[2] * cabeza[numcabeza].dimxyz[0]* cabeza[numcabeza].dimxyz[1];

   return(posicion);          
}

ulong Basedatos::metedato   (ch9 *label9,ulong *nxyz,double *dato)
{
ulong posicion;

   { //bloque de mirar posicion:===
   int i;
   if (BASE) 
      for (i=0;i<3;i++) nxyz[i]--;
   posicion=miradato(label9,nxyz);
   if (BASE) 
      for (i=0;i<3;i++) nxyz[i]++;
   } //fin del bloque ============
if (posicion)
   {
   matriz[posicion]=*dato;
   return(posicion);
   }
return(0);
}

ulong Basedatos::leedato    (ch9 *label9,ulong *nxyz,double *dato)
{
ulong posicion;

*dato=0;

   { //bloque de mirar posicion:===
   int i;
   if (BASE) 
      for (i=0;i<3;i++) nxyz[i]--;
   posicion=miradato(label9,nxyz);
   if (BASE) 
      for (i=0;i<3;i++) nxyz[i]++;
   } //fin del bloque ============

if (posicion)
   {
   *dato=(matriz[posicion]);
   return(posicion);
   }
return(0);
}

int   Basedatos::creacabeza (ch9 *label9,ulong *dimxyz)
   {
   int i,numcabeza;
   ulong ultimodato2;
   for (i=0;i<8;i++) label9[0][i]=tolower(label9[0][i]);
   label9[0][8]='\0';
   numcabeza=buscacabeza(label9);
   if (numcabeza>-1)
      {
      mensaje(2,"En base de datos: La variable o matriz ya existe. Variable no creada");
      return(-1);
      }
   ultimodato2 = ultimodato + dimxyz[0] * dimxyz[1] * dimxyz[2];
   if (ultimodato2>TOP)
      {
      char label1[256]="En base de datos: Superada la memoria, ampliarla o reducir dimensiones. Volver a arrancar. La memoria actual=";
      char label2[30];
      double x=1.;
      _ultoa(TOP*sizeof(x),label2,10);
      strcat(label1,label2);  
      mensaje(4,label1);
      return(-1);
      }

   if (ultimacabeza>=TOPCABEZA)
      {
      char label1[256]="En base de datos: Superado el número máximo de variables TOPCABEZA, ampliarlo o reducir el número de variables. Volver a arrancar. El número máximo de variables =";
      char label2[30];
      _itoa(TOPCABEZA,label2,10);
      strcat(label1,label2);  
      mensaje(4,label1);
      return(-1);
      }
   cabeza[ultimacabeza].inicio=ultimodato;
   ultimodato=ultimodato2;
   strcpy(cabeza[ultimacabeza].nombre,&label9[0][0]);
   cabeza[ultimacabeza].dimxyz[0]=dimxyz[0];
   cabeza[ultimacabeza].dimxyz[1]=dimxyz[1];
   cabeza[ultimacabeza].dimxyz[2]=dimxyz[2];

   return(ultimacabeza++);
   }

int   Basedatos::buscacabeza(ch9 *label9)
   {
   int i;
   char c;
   c=label9[0][0];
   for(i=0;i<ultimacabeza;i++)
      {
      if (cabeza[i].nombre[0]==c)
         if ( strncmp(cabeza[i].nombre,&label9[0][0],8)==0) return(i);
      }
   return (-1);
   }

double Basedatos::prueba_lectura_base_datos(ulong i)
{
if (i<ultimodato) return(matriz[i]); 
return(-111.);
}

// subrutina de avisos:
void mensaje(int level,char *errlin)
   {
   double dpin;     //Número doble precisión
   ch32   chin="\0\0";     //Vector de hasta 32 caracteres conteniendo el texto del mensaje
   ANSERR(&level,&errlin[0],0,&dpin,&chin,0);
   }


void __stdcall ANSERR
(
int    *level,    //Nivel: 1,2,3,4=nota,warning,error o fatal
char   *errlin,   //línea error
unsigned int long_ch1,  
double *dpin,     //Número doble precisión
ch32   *chin,     //Vector de hasta 32 caracteres conteniendo el texto del mensaje
unsigned int long_ch2
)
{
char c;
printf("*******************************************************\n");
switch(*level)
  {
  case 0:return;
  case 1:{printf("NOTA");break;}
  case 2:{printf("WARNING");break;}
  case 3:{printf("ERROR ");break;}
  case 4:{printf("ERROR FATAL");break;}
  default:return;                          
  }
printf(" %s",errlin);
printf(" valor=%-15lg",*dpin);
printf("%s\n",chin);
printf("*******************************************************\n");
printf("Meter caracter:");
scanf("%c%c",&c,&c);
}


static Basedatos basedatos;
 
void main()
{
ch9 label1,label2,label3;
ulong nxyz[3]   ={1,1,1},
      dimxyz[3] ={1,1,1},
      i,j; 
double x;

strcpy(basedatos.conversion.label9,"AAAAAAAA");
basedatos.conversion.dp=10.;

strcpy(label1,"CABEZA01");
dimxyz[0]=2;
dimxyz[1]=1;
basedatos.creacabeza(&label1,dimxyz);

strcpy(label2,"CABEZA02");
dimxyz[0]=2;
dimxyz[1]=1;
basedatos.creacabeza(&label2,dimxyz);

strcpy(label3,"CABEZA03");
dimxyz[0]=4;
dimxyz[1]=3;
dimxyz[2]=2;
basedatos.creacabeza(&label3,dimxyz);

for(j=1;j<3;j++)
   {
   x=100.+j;
   nxyz[0]=j;
   basedatos.metedato(&label1,nxyz,&x);
   }

for(j=1;j<3;j++)
   {
   x=200.+j;
   nxyz[0]=j;
   basedatos.metedato(&label2,nxyz,&x);
   }

for (int k=1;k<3;k++) 
   for(i=1;i<4;i++)
      for(j=1;j<5;j++)
         {
         x=3000000.+k*10000+i*100+j;
         nxyz[2]=k;
         nxyz[1]=i;
         nxyz[0]=j;
         basedatos.metedato(&label3,nxyz,&x);
         }
/*
i=0;
while ( (x=basedatos.prueba_lectura_base_datos(i))!=-111) 
    printf("%8li=%-le\n",i++,x);
*/
for (k=1;k<3;k++) 
   for(i=1;i<4;i++)
      for(j=1;j<5;j++)
         {
         double y;
         x=3000000.+k*10000+i*100+j;
         nxyz[2]=k;
         nxyz[1]=i;
         nxyz[0]=j;
         basedatos.leedato(&label3,nxyz,&y);
         printf("%le=%-le\n",x,y);
         }


mensaje(1,"=======FIN=========="); 

}   
