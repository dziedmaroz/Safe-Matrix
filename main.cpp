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
	fclose (fin);
  // matr.makeUnitMatrix (n);    
	//Matrix summ = matr;
	//summ+=matr;
	//bool flag;
	//Matrix mul = matr;
	//mul*=matr.toInvertibleMatrix(flag);
	//Matrix mulscal = matr;
	//mulscal*=5;

	FILE* fout = fopen ("matrix.out","w");
	//fprintf (fout,"A+A :\n");
	//for (int i=0;i<n;i++)
	//{
	//	for (int j=0;j<n;j++)
	//		fprintf (fout,"%0.3f   ",summ[i][j]);
	//	fprintf (fout,"\n");
	//}

	//fprintf (fout,"det A = %0.2f\n",matr.det());
	//Matrix inv = matr.toInvertibleMatrix (flag);

	//fprintf (fout,"A^(-1):\n");
	//for (int i=0;i<n;i++)
	//{
	//	for (int j=0;j<n;j++)
	//		fprintf (fout,"%0.3f   ",inv[i][j]);
	//	fprintf (fout,"\n");
	//}
 //   Matrix row  = inv;//(1,n);
	////for (int i=0;i<n;i++)
	////	row[0][i]=1;	
	//row*=matr;


	//fprintf (fout," (1, 1, ...,1)* A:\n");
	//for (int i=0;i<row.getRows();i++)
	//{
	//	for (int j=0;j<row.getColumns();j++)
	//		fprintf (fout,"%0.3f   ",row[i][j]);
	//	fprintf (fout,"\n");
	//}




	//fprintf (fout,"5*A :\n");
	//for (int i=0;i<n;i++)
	//{
	//	for (int j=0;j<n;j++)
	//		fprintf (fout,"%0.3f   ",mulscal[i][j]);
	//	fprintf (fout,"\n");
	//}
	 	
	for (int i=2;i<n;i++)
		for (int j=0;j<m;j++)
			fprintf (fout,"COF (%d,%d) = %0.3lf\n",i,j,matr.cofactor(i,j));
	fclose (fout);
   
   return 0;
}
