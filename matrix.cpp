#include "matrix.h"

Matrix::Matrix()
{
  this->m_=0;
  this->n_=0;
  this->p_=NULL;
}

Matrix::Matrix (long n, long m)
{
    this->n_=n;
    this->m_=m;
    p = new double [n_*m_];
}
Matrix::Matrix (const Matrix &m)
{
    this->m_=m.m_;
    this->n_=m.n_;
    this->p_= new double [n_*m_];
    for (int i=0;i<n_*m_;i++) this->p_[i]=m.p_[i];
}

inline Matrix& Matrix::operator = (const Matrix& m){ return Matrix(m);}
Matrix& Matrix::operator += (const Matrix& m)
{

    if (this->m_!=m.m_ || this->n_!=m.n_) throw (BadDimensions);
    for (int i=0;i<this->m_*this->n_;i++) this->p_[i]+=m.p_[i];
    return this;
}

Matrix& Matrix::operator -= (const Matrix& m)
{

    if (this->m_!=m.m_ || this->n_!=m.n_) throw (BadDimensions);
    for (int i=0;i<this->m_*this->n_;i++) this->p_[i]-=m.p_[i];
    return this;
}

Matrix& Matrix::operator *= (const double d)
{
    for (int i=0;i<this->m_*this->n_;i++) this->p_[i]*=d;
}


inline Matrix::~Matrix () { delete[] p;}
