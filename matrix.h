#ifndef MATRIX_H
#define MATRIX_H


// исключения
struct BadDimensions {};
struct BadFirstIndex {};
struct BadSecondIndex {};

// интерфейс класса Matrix
class Matrix
{
	long	n_, m_;	// размерности матрицы
	double*	p_;		// указатель на матрицу
	Matrix();
	class row
	{
		long	m_;	// размерность строки
		double* p_;	// указатель на строку
	public:
		row(long m, double* p);
			// оператор индексирования
		double& operator [] (long j);				// throw BadFirstIndex
		const double& operator [] (long j) const;	// throw BadSecondIndex
	};
public:
		// конструкторы
	Matrix(long n, long m);
	Matrix(const Matrix& m);
		// деструктор
	~Matrix();
		// оператор присваивания
	Matrix& operator = (const Matrix& m);	// throw BadDimensions
		// оператор индексирования
	row operator [] (long i);				// throw BadFirstIndex
	const row operator [] (long i) const;	// throw BadFirstIndex
		// унарные операторы
	Matrix& operator += (const Matrix& m);	// throw BadDimensions
	Matrix& operator -= (const Matrix& m);	// throw BadDimensions
	Matrix& operator *= (const Matrix& m);	// throw BadDimensions
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
};

#endif // MATRIX_H
