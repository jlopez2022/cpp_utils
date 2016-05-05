#include <stdio.h>

void main()
{
FILE *stream;
int i;
double x;
char c;

stream=fopen("kaka.wri","w");
for (i=0;i<20;i++) fprintf(stream,"%lf ",(0.001*i+i));
fclose(stream);

stream=fopen("kaka.wri","r");
for (i=0;i<20;i++) 
   {
   fscanf(stream,"%lf",&x);
   printf("%9.4lg ",x);
   }
fclose(stream);
scanf("%c%c",&c,&c);
}