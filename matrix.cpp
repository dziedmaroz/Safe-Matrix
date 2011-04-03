#include "matrix.h"
#include <cstdlib> 
Matrix::Matrix()
{
  this->rows_=0;
  this->columns_=0;
  this->p_=NULL;
}

Matrix::Matrix (long m, long n)
{
	this->rows_=m;
    this->columns_=n;   
    p_ = new double [columns_*rows_];
}
Matrix::Matrix (const Matrix &m)
{
    this->rows_=m.rows_;
    this->columns_=m.columns_;
    this->p_= new double [columns_*rows_];
    for (int i=0;i<columns_*rows_;i++) this->p_[i]=m.p_[i];
}

Matrix& Matrix::operator = (const Matrix& m)
{
	delete [] p_;
	this->columns_=m.columns_;
	this->rows_=m.rows_;
	p_= new double [columns_*rows_];
	for (int i=0;i<columns_*rows_;i++)
		this->p_[i]=m.p_[i];
	return *this;
}
Matrix& Matrix::operator += (const Matrix& m)
{
	BadDimensions err;

    if (this->rows_!=m.rows_ || this->columns_!=m.columns_) throw (err);
    for (int i=0;i<this->rows_*this->columns_;i++) this->p_[i]+=m.p_[i];
    return *this;
}

Matrix& Matrix::operator -= (const Matrix& m)
{

	BadDimensions err;
    if (this->rows_!=m.rows_ || this->columns_!=m.columns_) throw (err);
    for (int i=0;i<this->rows_*this->columns_;i++) this->p_[i]-=m.p_[i];
    return *this;
}

Matrix& Matrix::operator *= (const double& d)
{
    for (int i=0;i<this->rows_*this->columns_;i++) this->p_[i]*=d;
	return *this;
}


inline Matrix::~Matrix () { delete[] p_;}
void Matrix::makeUnitMatrix (long n)
{
	this->rows_=n;
	this->columns_=n;
	delete [] p_;

	 p_=new double [n*n];
	 for (int i=0;i<n;i++)
	     for (int j=0;j<n;j++)
		if (i==j) (*this)[i][j]=1;
		else (*this)[i][j]=0;
}


Matrix& Matrix::operator *=(const Matrix &m)
{
	BadDimensions err;
	if (this->columns_!=m.rows_) throw (err);	
	Matrix tmp (this->rows_,m.columns_);
	for (int i=0;i<tmp.rows_;i++)
		for (int j=0;j<tmp.columns_;j++)
		{
			tmp[i][j]=0;
			double s=0;
			for (int r=0;r<this->columns_;r++)
				s+=(*this)[i][r]*m[r][j];
			tmp[i][j]+=s;
		}
	(*this ) = tmp;
	return *this;
	 
}

Matrix::Row::Row (long rowN, double *p)
{
	p_=p;
	columns_=rowN;
}

const Matrix::Row Matrix::operator [](long i) const
{
	BadFirstIndex err;
	if (i>=rows_) throw (err);
	Matrix::Row tmp  (this->columns_,this->p_+(i*this->columns_));
	return tmp;
}


const double& Matrix::Row::operator [](long j) const
{
	BadSecondIndex err;
	if (j>=this->columns_) throw (err);
	return p_[j];
}

Matrix::Row Matrix::operator [] (long i)
{
    BadFirstIndex err;
    if (i>=rows_) throw (err);
    Matrix::Row tmp  (this->columns_,this->p_+(i*this->columns_));
    return tmp;
}

double& Matrix::Row::operator [] (long j)
{
    BadSecondIndex err;
    if (j>=this->columns_) throw (err);
    return p_[j];
}

Matrix Matrix::toTriangleMatrix ()
{
    Matrix tmp = *this;
    int n=this->columns_<this->rows_?this->columns_:this->rows_;
	double diff =1;
	if ((*this)[0][0]==0)
	{
		int swp=1;
		while (tmp[swp][0]==0 && swp<this->rows_-1) swp++ ;
		for (int i=0;i<rows_;i++)
		{
			double t = tmp[0][i];
			tmp[0][i]=tmp[swp][i];
			tmp[swp][i]=t*(-1);
		}
		//diff*=-1;
	}
    for (int i=0;i<n;i++)
    {
        for (int j=i+1;j<n;j++)
        {
            double hi=tmp[i][i];
			double lo=tmp[j][i];
			if (lo*hi!=0)
			{
				for (int k=i;k<tmp.columns_;k++)
				{
					double a = tmp[j][k];
					double b = tmp [i][k];
					
					tmp [j][k] = (a*hi-b*lo)/hi;
				}
				
			}			 
        }
	}

 
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			tmp[i][j]/=diff;
    return tmp;
}

double Matrix::det ()
{
	BadDimensions err;
	if (this->columns_!=this->rows_) throw (err);
	Matrix tmp = toTriangleMatrix();
	int n=this->columns_<this->rows_?this->columns_:this->rows_;
	double res=1;
	for (int i=0;i<n;i++)
		res*=tmp[i][i];	 
	return res;
}

Matrix Matrix::toInvertibleMatrix (bool& isDegenerate)
{
    BadDimensions err;
    if (this->columns_!=this->rows_) throw (err);
    Matrix A (*this);
    if (det()==0)
    {
        isDegenerate=true;
        return Matrix (0,0);
    }
    Matrix B (*this);
    int n=this->columns_;
	double detA = this->det ();
    for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			B[i][j]=this->cofactor(j,i)/detA;
	return B;
}

double Matrix::cofactor (int x, int y)
{
    Matrix A (this->columns_-1, this->rows_-1);
    int iDiff=0;
    int jDiff=0;
    for (int i=0;i<this->columns_;i++)
    {

        jDiff=0;
        for (int j=0;j<this->columns_;j++)
        {
            if (i==x)
            {
                iDiff=1;
                continue;
            }
            if (j==y)
            {
                jDiff=1;
                continue;
            }
            A[i-iDiff][j-jDiff]=(*this) [i][j];
        }
    }	 
	double diff = (x+y)%2?-1:1;
    return diff*A.det ();
}

//Matrix operator + (const Matrix& m1, const  Matrix& m2)
//{
//	BadDimensions err;
//	if (m1.getColumns()!= m2.getColumns() || m1.getRows() != m2.getRows())
//	throw (err);
//
//}