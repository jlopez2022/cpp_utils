#include <stdio.h>

void main()
{
int i;
char c;
FILE *stream;
stream=fopen("out.bmp","w");
for(i=0;i<256;i++)
{
fprintf(stream,"%3i:%-5c",i,i);
}
fclose(stream);
scanf("%c%c",&c,&c);
}