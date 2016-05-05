#include <stdio.h>
#include <math.h>       /* round, floor, ceil, trunc */

double round1(double num) {     return (num > 0.0) ? floor(num + 0.5) : ceil( num - 0.5); }
long   round2(double num) {     return (num > 0.0) ? (int)(num + 0.5) : (int)(num - 0.5); }


int main ()
{
  const char * format = "%.1f \t%.1f \t%5i\t%.1f \t%.1f\n";
  printf ("value\tround1\tround2\tfloor\tceil\n");
  printf ("-----\t------\t------\t----\t----\n");
  printf (format, 2.3,round1( 2.3),round2( 2.3),floor( 2.3),ceil( 2.3));
  printf (format, 3.8,round1( 3.8),round2( 3.8),floor( 3.8),ceil( 3.8));
  printf (format, 5.5,round1( 5.5),round2( 5.5),floor( 5.5),ceil( 5.5));
  printf (format,-2.3,round1(-2.3),round2( -2.3),floor(-2.3),ceil(-2.3));
  printf (format,-3.8,round1(-3.8),round2( -3.8),floor(-3.8),ceil(-3.8));
  printf (format,-5.5,round1(-5.5),round2( -5.5),floor(-5.5),ceil(-5.5));
  getchar();getchar();
  return 0;
}