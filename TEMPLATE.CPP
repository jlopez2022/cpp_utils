#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef unsigned long ulong;
typedef  struct Nombre
   {
   char label9[9];
   ulong dato[10];
   }nmbf;

template<class T> class Prueba
   {
   public:
      Prueba(ulong dim);
      ~Prueba();
      void escribe(T,ulong);
      T *m;
   private:
      ulong size;
   };

template<class T>
Prueba<T>::Prueba(ulong dim)
   {
   m=new T[dim];
   size=dim;
   }

template<class T>
Prueba<T>::~Prueba()
   {
   delete[] m;
   }

template<class T>
void Prueba<T>::escribe(T dato,ulong dir)
   {
   if (dir<size) m[dir]=dato;
   }


void main()
   {
   ulong i;
   char c;
   Prueba<double>  mat1(20240);
   Prueba<char>    mat2(20240);
   Prueba<ulong>   mat3(20240);
   Prueba<Nombre>  mat4(20240);
   Nombre nombre;

   for (i=0;i<99;i++)
      {
      mat1.m[i]=1.e8+i;
      mat2.escribe((unsigned char) (i+100),i);
      mat3.escribe(i*10000,i);
      mat4.m[i].dato[0]=1000+i;
      }
   for (i=0;i<20;i++)
      printf("%2u:%12.0lf %c=%4u %12lu %12lu\n",i,mat1.m[i],mat2.m[i],mat2.m[i],mat3.m[i],mat4.m[i].dato[0]);
   scanf("%c%c",&c,&c);
   strcpy(nombre.label9,"prue1");
   for (i=0;i<8;i++)
      nombre.dato[i]=8000+i;
   mat4.escribe(nombre,0);
   mat4.escribe(nombre,1);
   i=3;
   }
