#pragma once
class Matrix
{
private:
	const int RowNum; //矩阵的行数
	const int ColomnNum; //矩阵的列数
	double ** const PMatrix; //指向矩阵的指针
	Matrix(int rowNum, int colomnNum);
public:
	Matrix(int rowNum, int colomnNum, double *row, ...);
	Matrix(const Matrix & matrix);
	~Matrix();

	void Print() const; //输出矩阵
	Matrix TransposeMatrix() const; //求矩阵的转置
	int Rank() const; //求矩阵的秩
	void MultiplyKToRowI(double k, int i) const; //矩阵的第i行乘以k倍
	void AddRowsKIToJ(double k, int i, int j) const; //将第i行的k倍加到第j行
	Matrix LeastLineMatrix() const; //求矩阵的最简行阶梯矩阵
	Matrix InverseMatrix() const; //求矩阵的逆矩阵
	Matrix Solution() const; //把矩阵看作增广矩阵，求方程组的解（仅考虑解唯一和无解两种情况）

	Matrix operator+(const Matrix another) const; //矩阵加法
	Matrix operator-(const Matrix minuend) const; //矩阵减法
	Matrix operator*(const Matrix another) const; //矩阵乘法
	Matrix operator*(const double constant) const; //矩阵数乘
};

