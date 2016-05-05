#include <stdio.h>

void main()
{
int i;
char c;
FILE *stream;

stream=fopen("prue.txt","w");

for(i=0;i<79;i++) fprintf(stream,"=");
for(i=0;i<79;i++) printf("=");

fprintf(stream,"\n");
printf("\n");

for(i=25;i<256;i++)
  {
  c=(char) i;
  fprintf(stream,"    %3i:%c.",i,c);
  printf("    %3i:%c.",i,c);
  }

fprintf(stream,"\n");
printf("\n");
for(i=0;i<79;i++) fprintf(stream,"=");
for(i=0;i<79;i++) printf("=");
printf("\n");

scanf("%c%c",&c,&c);
fclose(stream);
}