#include <stdio.h>
//prueba de enum
class  Semana
   {
   public:
   typedef enum Dia{Lunes,Martes,Miercoles,Jueves,Viernes,Sabado,Domingo};
   Dia diario;
//   Dia  operator++(Semana::Dia &d,int);

   };

inline Semana::Dia operator++(Semana::Dia &d,int)
      {
      return d=(Semana::Dia) (d+1);
      }


void main()
{
Semana semana;

semana.diario=Semana::Lunes;

for (int i=0;i<6;i++)
   semana.diario++;

}                                  