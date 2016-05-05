#include <stdio.h>
#define GEOM1_MAX 8
#define GEOM2_MAX 5
#define MATER_MAX 3
#define  TENS_MAX 5
#define   ESF_MAX 6
#define RESUL_MAX 9
#define EJEMP_MAX 10

void main()
{
int i,j,j0;
char c=0;
double geom1[EJEMP_MAX][GEOM1_MAX];
double geom2[EJEMP_MAX][GEOM2_MAX];
double mater[EJEMP_MAX][MATER_MAX];
double  tens[EJEMP_MAX][ TENS_MAX];
double   esf[EJEMP_MAX][  ESF_MAX];
double resul[EJEMP_MAX][RESUL_MAX];

FILE *stream;
FILE *stream2=fopen("kaka.wri","w");

if ( (stream=fopen("AISCPRU.TXT","r")))
   {
   char label[256];
   char titulo[100][21];

   fgets(label,256,stream);
   for (j=0;j<(GEOM1_MAX+GEOM2_MAX+MATER_MAX+TENS_MAX+ESF_MAX);j++)
      {
      fgets(&titulo[j][0],6,stream);
      titulo[j][4]=':';
      }
   for (i=0;i<RESUL_MAX;i++)
      {
      fgets(&titulo[i+j][0],14,stream);
      titulo[i+j][4]=':';
      titulo[i+j][5]='\0';
      }
//   fgets(label,256,stream);

   for (i=0 ; i<EJEMP_MAX;i++)
      {
      for (j=0;j<GEOM1_MAX;j++) fscanf(stream,"%lf",&geom1[i][j]);
      for (j=0;j<GEOM2_MAX;j++) fscanf(stream,"%lf",&geom2[i][j]);
      for (j=0;j<MATER_MAX;j++) fscanf(stream,"%lf",&mater[i][j]);
      for (j=0;j< TENS_MAX;j++) fscanf(stream,"%lf", &tens[i][j]);
      for (j=0;j<  ESF_MAX;j++) fscanf(stream,"%lf",  &esf[i][j]);

      for (j=0;j<RESUL_MAX;j++) fscanf(stream,"%lf",&resul[i][j]);
      }

   fprintf(stream2,"\n================================================== GEOM1 ==============================================");
   j0=0;
   for (j=0;j<GEOM1_MAX;j++) 
      {
      fprintf(stream2,"\n%5s",titulo[j0+j]);
      for (i=0 ; i<EJEMP_MAX;i++)
         fprintf(stream2,"%-9.4lG ",geom1[i][j]);
      }
   j0+=j;
 
   fprintf(stream2,"\n================================================== GEOM2 ==============================================");
   for (j=0;j<GEOM2_MAX;j++) 
      {
      fprintf(stream2,"\n%5s",titulo[j0+j]);
      for (i=0 ; i<EJEMP_MAX;i++)
         fprintf(stream2,"%-9.4lG ",geom2[i][j]);
      }
   j0+=j;
   fprintf(stream2,"\n================================================== MATER ==============================================");
      
   for (j=0;j<MATER_MAX;j++) 
      {
      fprintf(stream2,"\n%5s",titulo[j0+j]);
      for (i=0 ; i<EJEMP_MAX;i++)
         fprintf(stream2,"%-9.4lG ",mater[i][j]);
      }
   j0+=j;
   fprintf(stream2,"\n================================================== TENS  ==============================================");
   
   for (j=0;j< TENS_MAX;j++)
      {
      fprintf(stream2,"\n%5s",titulo[j0+j]);
      for (i=0 ; i<EJEMP_MAX;i++)
         fprintf(stream2,"%-9.4lG ",tens[i][j]);
      }
   j0+=j;
   fprintf(stream2,"\n================================================== ESF   ==============================================");
   for (j=0;j<  ESF_MAX;j++) 
      {
      fprintf(stream2,"\n%5s",titulo[j0+j]);
      for (i=0 ; i<EJEMP_MAX;i++)
         fprintf(stream2,"%-9.4lG ",esf[i][j]);
      }
   j0+=j;
   fprintf(stream2,"\n================================================== RESUL ==============================================");

   for (j=0;j<RESUL_MAX;j++)
      {
      fprintf(stream2,"\n%5s",titulo[j0+j]);
      for (i=0 ; i<EJEMP_MAX;i++)
         fprintf(stream2,"%-9.4lG ",resul[i][j]);
      }
   j0=j;
   fprintf(stream2,"\n================================================== FIN   ==============================================");
      
   fclose(stream);
   fclose(stream2);
   }
}
