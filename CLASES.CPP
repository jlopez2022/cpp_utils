//acceso a clases
/*
private	 :Class members declared as private can be used only 
          by member functions and friends (classes or functions) of the class.
protected:Class members declared as protected can be used 
          by member functions and friends (classes or functions) of the class. Additionally, they can be used by classes derived from the class.
public	 :Class members declared as public can be used 
          by any function.
*/
class A
   {
   public:
      int a_pub;
   protected:
      int a_pro;
      int incrementa(int);
   private:
      int a_pri;
   };

class B : public A
   {
   public:
      void prueba(int);
   };

int  A::incrementa(int i)
   {
   return (i+1);
   }

void B::prueba(int i)
   {
   a_pub=i;
   a_pro=i;
   // a_pri=i;    error
   i=incrementa(i);
   }


void main()
{
B b;
b.a_pub=7;
}