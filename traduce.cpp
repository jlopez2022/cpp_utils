// Este programa lee ficheros *.OBR para lectura de 
// canales analógicos 
// Entrada: fichero.txt
// Salida:  output.txt


#include <stdio.h>
#include <string.h>

void mensaje(int level,char *label0,char *label1="\0",char *label2="\0",char *label3="\0",char *label4="\0");


void main()
   {
   int i;
   FILE *stream1,*stream2;
   char line[255];

   if (!(stream1=fopen("fichero.txt","r")))
      mensaje(3,"No se ha podido abrir fichero : ");
   stream2=fopen("output.txt","w");

   while (!feof(stream1))
      {
      fscanf(stream1,"%s",line);
      if (strncmp(line,"C43B",4)==0)
         fprintf(stream2,"\nChannel= %s",&line[4]);
      if (strncmp(line,"C4380A00",8)==0)
         {
         for(i=0;i<6;i++)
            fscanf(stream1,"%s",line);
         fprintf(stream2," Dato= %s",&line[10]);
         }
      }
   fclose(stream1);
   fclose(stream2);
   }





void mensaje(int level,char *label0,char *label1,char *label2,char *label3,char *label4)
   {
   char c;
   printf("*******************************************************\n");
   switch(level)
     {
     case 0:return;
     case 1:{printf("NOTA");break;}
     case 2:{printf("WARNING");break;}
     case 3:{printf("ERROR ");break;}
     case 4:{printf("ERROR FATAL");break;}
     default:return;                          
     }
   printf(" %s%s%s%s%s\n",label0,label1,label2,label3,label4);
   printf("*******************************************************\n");
   if (level>1)
      {
      printf("Meter caracter:");
      scanf("%c%c",&c,&c);
      }
   }
