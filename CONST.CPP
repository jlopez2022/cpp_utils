void f(const int &) ;

void main()
{
int i=10;
f(i);
i=3;
}



void f(const int &i)  
   {
   int j;
   j=i;
   // i=7000;  error
   }
