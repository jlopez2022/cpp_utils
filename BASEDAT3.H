typedef char ch9[9];
typedef char ch32[32];
typedef unsigned long ulong;

void mensaje(int level,char *label0,char *label1="\0",char *label2="\0",char *label3="\0",char *label4="\0");

/********************** clase matriz *******************/

class Matriz
   {
   public:
      Matriz(ch32 label="anonimo",ulong x=1,ulong y=1, ulong z=1);
      ~Matriz();
      void   redim  (ulong x=1,ulong y=1, ulong z=1);
      double lee    (ulong x=1,ulong y=1, ulong z=1, int error=0);
      void   escribe(double dato=0,ulong x=1,ulong y=1, ulong z=1, int error=0);
      int    leeerror(); //mira si hay error y lo borra
      ch9    nombre_matriz;
      ulong  dimension();

      Matriz *anterior_matriz,*siguiente_matriz;

   private:
      ulong  miradimension(ulong x=0,ulong y=0,ulong z=0,int error=0);
      ulong  dimx,dimy,dimz;
      int    error_matriz;
      double *matrix;
   };

/********** clase matrizcontrol ************/
class Matrizcontrol  
   {
   public:
   typedef unsigned long ulong;
   Matrizcontrol(ulong i,ulong j=500*1024);
   ~Matrizcontrol();
   ulong inserta(Matriz *ptr);
   void  elimina(Matriz *ptr);
   ulong redimensiona(ulong,int,ch9);
   void  lista(ch32 fichero="stdout");
   private:
   ulong TOPMATRIZ;
   ulong TOPDIMENSION;
   ulong numero_matrices,dimension_total;
   Matriz *primera_matriz,*ultima_matriz;
   } matrizcontrol(1024,500*1024);

/*
void operator delete(void *Matriz)
   {
   ~Matriz();
   }
*/