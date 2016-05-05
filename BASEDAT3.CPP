#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include "BASEDAT3.h"

void mensaje(int level,char *label0,char *label1,char *label2,char *label3,char *label4)
   {
   char c;
   printf("*******************************************************\n");
   switch(level)
     {
     case 0:return;
     case 1:{printf("NOTA");break;}
     case 2:{printf("WARNING");break;}
     case 3:{printf("ERROR ");break;}
     case 4:{printf("ERROR FATAL");break;}
     default:return;                          
     }
   printf(" %s%s%s%s%s\n",label0,label1,label2,label3,label4);
   printf("*******************************************************\n");
   if (level>1)
      {
      printf("Meter caracter:");
      scanf("%c%c",&c,&c);
      }
   }

Matriz::Matriz(ch32 label,ulong x,ulong y,ulong z)
   {
   strncpy(nombre_matriz,label,8);
   nombre_matriz[8]='\0';
   error_matriz=0;

   matrizcontrol.inserta(this);
   if (!matrizcontrol.redimensiona( x*y*z,1,nombre_matriz ) )
      {
      x=1;y=1;z=1;
      matrizcontrol.redimensiona( 1,1,nombre_matriz );      
      } 
   dimx=x;
   dimy=y;
   dimz=z;
   matrix=new double[x*y*z];
   } 

Matriz::~Matriz()
   {
   leeerror();
   matrizcontrol.elimina(this);
   matrizcontrol.redimensiona( dimension() ,-1 ,nombre_matriz );
   delete[] matrix;
   }  

int Matriz::leeerror()
   {
   if (error_matriz) 
      {
      error_matriz=0;
      mensaje(2,"Detectado que hubo intento infructuoso de lectura/escritura sobre matriz ",nombre_matriz);
      return(0);
      }
   return(1);
   }

//*** ¡¡¡ ATENCION !!!  MIRADIMENSION DEVUELVE POSICION+1 SI NO HAY ERROR o 0 SI LO HAY
inline ulong Matriz::miradimension(ulong x,ulong y,ulong z,int error)
   {
   if ( x<dimx && y<dimy && z<dimz )
      return(1 + z + dimz*( y + dimy*x ) );
   else if (error)
      {
      char line[100],label1[256]="(",label2[256]="(";
      _ultoa(x,line,10)   ;strcat(line,",");strcat(label1,line);
      _ultoa(y,line,10)   ;strcat(line,",");strcat(label1,line);
      _ultoa(z,line,10)   ;strcat(line,")");strcat(label1,line);

      _ultoa(dimx,line,10);strcat(line,",");strcat(label2,line);
      _ultoa(dimy,line,10);strcat(line,",");strcat(label2,line);
      _ultoa(dimz,line,10);strcat(line,")");strcat(label2,line);

      mensaje(3,label1," fuera de los límites de ",nombre_matriz,label2);
      return(0);
      }
   error_matriz=1;
   return(0);
   }

void Matriz::escribe(double dato,ulong x,ulong y,ulong z,int error)
   {
   ulong posicion=miradimension(x,y,z,error);
   if (posicion)
      matrix[--posicion]=dato;
   }

double Matriz::lee(ulong x,ulong y,ulong z,int error)
   {
   ulong posicion=miradimension(x,y,z,error);
   if (posicion)
      return (matrix[--posicion]);
   return(DBL_MIN);
   }

void   Matriz::redim  (ulong x,ulong y, ulong z)
   {
   if (matrizcontrol.redimensiona(dimension(),-1,nombre_matriz) )
   if (matrizcontrol.redimensiona(x*y*z,1,nombre_matriz) )
      {
      delete[] matrix;
      matrix=new double[x*y*z];
      dimx=x; dimy=y; dimz=z;
      return;
      }
   }

ulong Matriz::dimension()
   {
   return(dimx*dimy*dimz);
   }
/******************* matrizcontrol : **********************/

Matrizcontrol::Matrizcontrol(ulong i,ulong j)
   {
   numero_matrices=0;
   dimension_total=0;
   TOPMATRIZ=i;
   TOPDIMENSION=j;
   primera_matriz=NULL;
   ultima_matriz=NULL;
   }

Matrizcontrol::~Matrizcontrol()     
   {
   Matriz *ptr=primera_matriz;
   if (ptr)
      while(ptr->siguiente_matriz)
         {
         ptr=ptr->siguiente_matriz;
         delete   ptr->anterior_matriz;
         }
   if (ptr) delete ptr;
   }   

ulong Matrizcontrol::inserta(Matriz *ptr)
   {
   if (primera_matriz==NULL)
      {
      primera_matriz=ptr;
      ptr->anterior_matriz=NULL;
      }
   else
      {
      ultima_matriz->siguiente_matriz=ptr;
      ptr->anterior_matriz=ultima_matriz;
      }
   ptr->siguiente_matriz=NULL;
   ultima_matriz=ptr;
   if (++numero_matrices>=TOPMATRIZ) mensaje(1,"La matriz ",ptr->nombre_matriz," ha superado el número máximo de matrices");
   return(numero_matrices);
   }

  void Matrizcontrol::elimina(Matriz *ptr)
     {
     if (numero_matrices==0) 
        {
        mensaje(3," no existen más matrices que eliminar");
        return;
        }
     numero_matrices--;
     if (ptr->siguiente_matriz) 
        (ptr->siguiente_matriz)->anterior_matriz=ptr->anterior_matriz;
     else
        ultima_matriz=ptr->anterior_matriz;
     if (ptr->anterior_matriz) 
        (ptr->anterior_matriz)->siguiente_matriz=ptr->siguiente_matriz;
     else
        primera_matriz=ptr->siguiente_matriz;
     }

ulong Matrizcontrol::redimensiona(ulong u,int signo,ch9 nombrematriz)
   {
   if ( u==0)
      {
      mensaje(1,"Error de dimensionado de matriz ",nombrematriz," , la dimension no puede ser 0.\nMatriz no redimensionada o dimension 1");
      return(0);
      }

   if (signo==-1)
      {
      if (dimension_total<u)
         {
         mensaje(3,"Error de dimensionado de matriz ",nombrematriz," : la dimension total<0. \nMatriz no redimensionada o dimension 1");
         return(0);
         }
      u = dimension_total - u;
      dimension_total=u;
      if (!u) u=1;
      return(u);
      }

   if (signo==1)    
      {
      u = dimension_total + u;
      if (u>TOPDIMENSION)
         {
         char label[100];
         _ultoa(TOPDIMENSION,label,10);
         mensaje(3,"Error de dimensionado de matriz ",nombrematriz," , la dimension total>",label," . Matriz no redimensionada o dimension 1");
         return(0);
         }
      dimension_total=u;
      if (!u) u=1;
      return(u);
      }

   mensaje(3,"Error de programación en matriz ",nombrematriz," , el signo debe ser +-1");
   return(0);
   }
   
void Matrizcontrol::lista(ch32 fichero)
   {
   FILE *stream;
   Matriz *ptr=primera_matriz;
   double muestra=0;

   if (!strcmp(fichero,"stdout"))
      stream=stdout;
   else if (!(stream=fopen(fichero,"w") ) )
      {
      mensaje(3,"No se ha podido abrir fichero : ",fichero);
      return;
      }
   fprintf(stream,"------------ Listado de matrices existentes ----------------\n");
   while (ptr)
      {
      fprintf(stream,"%32s :size=%lu\n",ptr->nombre_matriz,ptr->dimension());
      ptr=ptr->siguiente_matriz;
      }
   fprintf(stream,"Numero total de matrices             = %lu\n",numero_matrices);
   fprintf(stream,"Numero total de variables contenidas = %lu\n",dimension_total);
   fprintf(stream,"Numero total de Kbytes               = %lf\n",(double) (1./1024 * sizeof(muestra) * dimension_total ));
   fprintf(stream,"-------------------------------------------------------------\n");
   fclose (stream);
   }
   
int main()
{
int k;
//int i,j;
Matriz *x1=new Matriz("mat_x1",1,100,1024);
Matriz *x2=new Matriz("mat_x2",2,100,1024);
Matriz *x3=new Matriz("mat_x3",3,100,1024);
matrizcontrol.lista();
delete x2;
delete x3;
/*
double x,mp[10][10][10];

for(i=0;i<9;i++)
for(j=0;j<9;j++)
for(k=0;k<9;k++)
   {x=(i+1)*10000+(j+1)*100+k+1;
   x1->escribe(x,i,j,k,1);
   mp[i][j][k]=x;
   }

for(i=0;i<3;i++)
for(j=0;j<4;j++)
for(k=0;k<5;k++)
   {
   char label[256];
   if ( mp[i][j][k]==x1->lee(i,j,k,1) ) strcpy(label,"OK");
      else  strcpy(label,"XX");
   printf("%10lf %-20lf %s\n",mp[i][j][k],x1->lee(i,j,k,1),label);
   }
*/
x1->redim(1,10,1024);
delete x1;
k=0;
return 777;
}
