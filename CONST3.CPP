#include <string.h>

void f(const char *) ;

void main()
{
char c='A',c2[256];
const char *d=&c;
c='B';
strcpy(c2,d);
f(d);
c='C';
}



void f(const char *c)  
   {
   char c1;
   c1=*c;
   //*c=0;
   }
