
double f(double x);
double integra(double inicio,double final,long iter);


void main()
   {
   double inicio=0,final=2,s;
   s=integra(inicio,final,2000000);
   }




double integra(double inicio,double final,long iter)
   {
   double x=inicio;
   double step,suma=0;
   long i;
   step=(final-inicio)/(double) iter;
   suma=f(inicio)+f(final);
   i=1;
   while(i<iter)
      {
      x+=step;
      suma+=f(x);
      i++;
      }
   suma*=step;
   return(suma);
   }



double f(double x)
   {
   return(x*x);
   }

