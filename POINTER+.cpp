void main()
   {
   int i,ii[100000],jj[100000];

   for (i=0;i<100000;i++)
      ii[i]=i;

   int *ptri,*ptrj;
   ptri=&ii[50];
   ptrj=&jj[0];

   for (i=0;i<90000;i++)
      {
      *ptrj++=*(ptri-50);
      ptri++;
      }
   }

