#include <stdio.h>
#include "matrix.h"
void matrixOut (FILE* fout, Matrix m);
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
	Matrix summ = matr;
	summ+=matr;
	bool flag;
	Matrix mul = matr;
	mul*=matr.toInvertibleMatrix(flag);
	Matrix mulscal = matr;
	mulscal*=5;

	FILE* fout = fopen ("matrix.out","w");
	Matrix tryMul1 (3,3);	 
	for (int i=0;i<3;i++)
		for (int j=0;j<3;j++)
		{
			tryMul1[i][j]=1;
		}
	tryMul1*=tryMul1;
	matrixOut (fout,tryMul1);
	fprintf (fout,"A+A :\n");
	matrixOut (fout,summ); 

	fprintf (fout,"det A = %0.2f\n",matr.det());
	Matrix inv = matr.toInvertibleMatrix (flag);

	fprintf (fout,"A^(-1):\n");
	matrixOut (fout,inv);

	fprintf (fout,"A:\n");
	matrixOut (fout,matr);
	Matrix row  = inv;
	//row.makeUnitMatrix(3);
	row*=matr;
	fprintf (fout," A^(-1)* A:\n");
	matrixOut (fout,row);  
	fprintf (fout,"5*A :\n");
	matrixOut (fout,mulscal);  
	
	for (int i=0;i<matr.getRows();i++)
	{
		for (int j=0;j<matr.getColumns();j++)
			fprintf (fout,"COFACTOR (%d,%d) = %0.2f\n",i,j,matr.cofactor(i,j));
		fprintf (fout,"\n");
	}
	 
	fclose (fout);
   
   return 0;
}
void matrixOut (FILE* fout, Matrix m)
{
	for (int i=0;i<m.getRows();i++)
	{
		for (int j=0;j<m.getColumns ();j++)
			fprintf (fout,"%0.2f\t",m[i][j]);
		fprintf (fout,"\n");
	}

}