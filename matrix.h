#ifndef MATRIX_H
#define MATRIX_H


// исключения
struct BadDimensions {};
struct BadFirstIndex {};
struct BadSecondIndex {};

// интерфейс класса Matrix
class Matrix
{
	long	columns_, rows_;	// размерности матрицы
	double*	p_;		// указатель на матрицу
	Matrix();

	class Row
	{
		long	columns_;	// размерность строки
		double* p_;	// указатель на строку
	public:
		Row(long rowN, double* p);
			// оператор индексирования
		double& operator [] (long j);				// thRow BadFirstIndex
		const double& operator [] (long j) const;	// thRow BadSecondIndex		
	};

	double cofactor (int i,int j);


public:
		// конструкторы
	void makeUnitMatrix (long n);
	Matrix(long n, long m);
	Matrix(const Matrix& m);
		// деструктор
	~Matrix();
		// оператор присваивания
	Matrix& operator = (const Matrix& m);	// thRow BadDimensions
		// оператор индексирования
	Row operator [] (long i);				// thRow BadFirstIndex
	const Row operator [] (long i) const;	// thRow BadFirstIndex
		// унарные операторы
	Matrix& operator += (const Matrix& m);	// thRow BadDimensions
	Matrix& operator -= (const Matrix& m);	// thRow BadDimensions
	Matrix& operator *= (const Matrix& m);	// thRow BadDimensions
	Matrix& operator *= (const double& d);
		// унарные операторы
	friend Matrix operator -(const Matrix& m);
	friend Matrix operator +(const Matrix& m);
		// бинарные операторы
	friend Matrix operator * (const double& d, const Matrix& m);
	friend Matrix operator * (const Matrix& m, const double& d);
		// следующие бинарные операторы
		// могут выбросить исключение BadDimensions
	friend Matrix operator + (const Matrix& m1, const Matrix& m2);
	friend Matrix operator - (const Matrix& m1, const Matrix& m2);
	friend Matrix operator * (const Matrix& m1, const Matrix& m2);

	double det ();
	long getRows ();
	long getColumns();
	Matrix toInvertibleMatrix ();
	Matrix toTriangleMatrix ();

};

#endif // MATRIX_H
