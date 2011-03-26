#include <stdio.h>
#include "matrix.h"
int main(int argc, char *argv[])        
{
   FILE* fin = fopen ("matrix.in","r");
   int n,m;
   fscanf(fin,"%d %d",&n,&m);
   Matrix matr (n,m);
   for (int i=0;i<n;i++)
       for (int j=0;j<m;j++)
         fscanf (fin,"%lf",&matr[i][j]);

  // matr.makeUnitMatrix (n);
   matr+=matr;

   for (int i=0;i<n;i++)
   {
       for (int j=0;j<m;j++)
         printf ("%9.2lf ",matr[i][j]);
       printf ("\n");

   }
   printf ("\n\n");
   Matrix matrTr = matr.toTriangleMatrix ();
   for (int i=0;i<n;i++)
   {
       for (int j=0;j<m;j++)
         printf ("%9.2lf ",matrTr[i][j]);
       printf ("\n");

   }
   printf ("det Matr %0.2f\n", matr.det());
   fclose (fin);
   return 0;
}
