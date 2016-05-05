#include <io.h>
#include <fcntl.h>
#include <stdio.h>

void main()
   {
   int fhl;
   char c;

   if (fhl = _open( "prue31.raw",_O_RDONLY))
      {
      printf( "Longitud= %ld\n", _filelength( fhl ) );
      scanf("%c%c",&c,&c);
      }
   }
