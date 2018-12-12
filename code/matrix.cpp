#include "Matrix.h"
#include <stdarg.h>
#include <iostream>
using namespace std;



Matrix::Matrix(int rowNum, int colomnNum) : \
RowNum(rowNum), ColomnNum(colomnNum), PMatrix(new double*[RowNum])
{
	//动态创建二维数组作为矩阵
	for (int i = 0; i < RowNum; i++)
	{
		PMatrix[i] = new double[ColomnNum] {0};
	}
}

Matrix::Matrix(int rowNum, int colomnNum, double *row, ...) : \
Matrix(rowNum, colomnNum)
{
	int i;
	//为矩阵赋值
	va_list rows;
	va_start(rows, row);
	while (rowNum-- > 0)
	{
		for (i = 0; i < ColomnNum; i++)
		{
			PMatrix[RowNum - rowNum - 1][i] = row[i];
		}
		row = va_arg(rows, double *);
	}
	va_end(rows);
}

Matrix::Matrix(const Matrix & matrix) : \
Matrix(matrix.RowNum, matrix.ColomnNum)
{
	for (int i = 0; i < RowNum; i++)
	{
		for (int j = 0; j < ColomnNum; j++)
		{
			PMatrix[i][j] = matrix.PMatrix[i][j];
		}
	}
}


Matrix::~Matrix()
{
	for (int i = 0; i < RowNum; i++)
	{
		delete[] PMatrix[i];
	}
	delete[] PMatrix;
}

void Matrix::Print() const
{
	if (RowNum == 0)
	{
		cout << "null matrix" << endl;
		return;
	}
	for (int i = 0; i < RowNum; i++)
	{
		for (int j = 0; j < ColomnNum; j++)
		{
			cout.setf(ios::scientific | ios::showpos);
			cout.precision(4);
			if (abs(PMatrix[i][j]) < 1e-10)
			{
				cout << 0.0 << '\t';
			}
			else
			{
				cout << PMatrix[i][j] << "\t";
			}
		}
		cout << endl;
	}
}

Matrix Matrix::TransposeMatrix() const
{
	Matrix matrix(ColomnNum, RowNum);
	for (int i = 0; i < RowNum; i++)
	{
		for (int j = 0; j < ColomnNum; j++)
		{
			matrix.PMatrix[j][i] = PMatrix[i][j];
		}
	}
	return matrix;
}

int Matrix::Rank() const
{
	int rank = 0;
	Matrix temp_matrix = LeastLineMatrix(); //先求矩阵的最简行阶梯矩阵
	//再数最简行阶梯矩阵的1的数量（即矩阵的秩）
	for (int i = 0, k = 0; i < RowNum && k < ColomnNum; i++, k++) 
	{
		if (temp_matrix.PMatrix[i][k] == 1)
		{
			rank++;
		}
		else
		{
			i--;
		}
	}
	//以下注释掉的代码求得的秩考虑不充分
	/*double rate;
	int flag, i, j, k, row_rank = 0;
	for (i = 0; i < RowNum; i++)
	{
		//首先判断该行是否全为零
		flag = 0;
		for (j = 0; j < ColomnNum; j++)
		{
			if (PMatrix[i][j] != 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			goto after; //跳过rank++
		}
		//再判断这一行是不是某一行的倍数
		for (j = i + 1; j < RowNum; j++)
		{
			rate = 0; //第i行与i以后的行之间的倍数值
			for (k = 0; k < ColomnNum; k++)
			{
				if (PMatrix[i][k] == 0) //如果i行k列元素为零
				{
					if (PMatrix[j][k] != 0) //如果j行k列元素不为零
					{
						goto outer; //排除第i行为第j行的倍数关系
					}
					else
					{
						continue;
					}
				}
				else if (PMatrix[j][k] == 0) //如果第i行k列的元素不为零且第j行k列元素为零
				{
					goto outer; //排除第i行为第j行的倍数关系
				}
				else if (rate == 0) //如果第i行k列的元素不为零且第j行k列元素不为零且倍数值未被赋值
				{
					rate = PMatrix[i][k] / PMatrix[j][k]; //那么为倍数值赋值
				}
				else if (rate != PMatrix[i][k] / PMatrix[j][k]) //如果倍数值已被赋值且不等于新的倍数
				{
					goto outer; //排除第i行为第j行的倍数关系
				}
			}
			goto after;
		outer:;
		}
		row_rank++;
	after:;
	}*/
	return rank;
}

void Matrix::MultiplyKToRowI(double k, int i) const
{
	for (int j = 0; j < ColomnNum; j++)
	{
		if (PMatrix[i][j] != 0)
		{
			PMatrix[i][j] *= k;
		}
	}
}

void Matrix::AddRowsKIToJ(double k, int i, int j) const
{
	for (int m = 0; m < ColomnNum; m++)
	{
		if (PMatrix[i][m] != 0)
		{
			PMatrix[j][m] += PMatrix[i][m] * k;
		}
	}
}

Matrix Matrix::LeastLineMatrix() const
{
	int i, j, k;
	Matrix new_matrix = *this; //复制构造一个新的矩阵
	for (i = 0, k = 0; i < RowNum && k < ColomnNum; i++, k++) //将矩阵的第i行乘以系数加到其他行上去，最终得到最简行阶梯矩阵
	{
		for (j = i; j < RowNum; j++) //确保第i行的第k个元素（也就是头元素）不为零，并将其化为1
		{
			if (new_matrix.PMatrix[j][k] != 0)
			{
				if (i != j)
				{
					swap(PMatrix[i], PMatrix[j]); //交换这两行
				}
				//将第i行的第k个元素（也就是头元素）变为1
				new_matrix.MultiplyKToRowI(1.0 / new_matrix.PMatrix[i][k], i); 
				break;
			}
		}
		//如果第i行第k列的元素仍为0，那么重新执行这一行（k默认加了1，意味着头元素向后移动了一位）
		if (new_matrix.PMatrix[i][k] == 0) 
		{
			i--;
			continue;
		}
		for (j = 0; j < RowNum; j++) //将第i行以外的其他行的第k列元素变为0
		{
			if (i != j && new_matrix.PMatrix[j][k] != 0)
			{
				new_matrix.AddRowsKIToJ(-new_matrix.PMatrix[j][k], i, j);
			}
		}
	}
	return new_matrix;
}

Matrix Matrix::InverseMatrix() const
{
	if (RowNum != ColomnNum || Rank() != RowNum) //如果矩阵没有逆矩阵
	{
		return Matrix(0, 0); //那么返回空矩阵
	}
	/*求逆矩阵的算法：将该矩阵和单位矩阵一起进行初等行变换使该矩阵成为单位矩阵
	的同时单位矩阵就成了该矩阵的逆矩阵*/
	int i, j;
	Matrix temp_matrix(RowNum, ColomnNum * 2); //构造一个由该矩阵和单位矩阵合并而成的临时矩阵
	for (i = 0; i < RowNum; i++)
	{
		for (j = 0; j < ColomnNum; j++) //初始化该矩阵的部分
		{
			temp_matrix.PMatrix[i][j] = PMatrix[i][j];
		}
		for (j = 0; j < ColomnNum; j++) //初始化单位矩阵的部分
		{
			temp_matrix.PMatrix[i][j + ColomnNum] = i == j ? 1 : 0;
		}
	}
	Matrix result_matrix = temp_matrix.LeastLineMatrix(); //进行初等行变换
	Matrix inversed_matrix(RowNum, ColomnNum); //最终得到的逆矩阵
	for (i = 0; i < RowNum; i++)
	{
		for (j = 0; j < ColomnNum; j++)
		{
			inversed_matrix.PMatrix[i][j] = result_matrix.PMatrix[i][ColomnNum + j];
		}
	}
	return inversed_matrix;
}

Matrix Matrix::Solution() const
{
	if (RowNum < ColomnNum - 1) //如果方程数小于未知数个数，返回空矩阵
	{
		return Matrix(0, 0);
	}
	Matrix least_line_matrix = LeastLineMatrix(); //求得增广矩阵的最简行阶梯矩阵
	int rank = 0;
	for (int i = 0, k = 0; i < RowNum && k < ColomnNum; i++, k++) //求增广矩阵的秩
	{
		if (least_line_matrix.PMatrix[i][k] == 1)
		{
			rank++;
		}
		else
		{
			i--;
		}
	}
	if (rank == ColomnNum - 1) //这是方程组有唯一解的情况
	{
		Matrix result(RowNum, 1);
		for (int i = 0; i < RowNum; i++) //方程组的解就是最后一列的值
		{
			result.PMatrix[i][0] = least_line_matrix.PMatrix[i][ColomnNum - 1];
		}
		return result;
	}
	return Matrix(0, 0); //其他情况均返回空矩阵
}

Matrix Matrix::operator+(const Matrix another) const
{
	//如果两个矩阵行列数不相等，返回空矩阵
	if (!(RowNum == another.RowNum && ColomnNum == another.ColomnNum))
	{
		return Matrix(0, 0);
	}
	Matrix result(RowNum, ColomnNum);
	for (int i = 0; i < RowNum; i++)
	{
		for (int j = 0; j < ColomnNum; j++)
		{
			result.PMatrix[i][j] = PMatrix[i][j] + another.PMatrix[i][j];
		}
	}
	return result;
}

Matrix Matrix::operator-(const Matrix minuend) const
{
	//如果两个矩阵行列数不相等，返回空矩阵
	if (!(RowNum == minuend.RowNum && ColomnNum == minuend.ColomnNum))
	{
		return Matrix(0, 0);
	}
	Matrix result(RowNum, ColomnNum);
	for (int i = 0; i < RowNum; i++)
	{
		for (int j = 0; j < ColomnNum; j++)
		{
			result.PMatrix[i][j] = PMatrix[i][j] - minuend.PMatrix[i][j];
		}
	}
	return result;
}

Matrix Matrix::operator*(const Matrix another) const
{
	if (ColomnNum != another.RowNum) //如果列数不等于行数
	{
		return Matrix(0, 0); //则返回空矩阵
	}
	Matrix result(RowNum, another.ColomnNum);
	for (int i = 0; i < RowNum; i++)
	{
		for (int j = 0; j < another.ColomnNum; j++)
		{
			for (int k = 0; k < ColomnNum; k++)
			{
				result.PMatrix[i][j] += PMatrix[i][k] * another.PMatrix[k][j];
			}
		}
	}
	return result;
}

Matrix Matrix::operator*(const double constant) const
{
	Matrix result = *this;
	for (int i = 0; i < RowNum; i++)
	{
		for (int j = 0; j < ColomnNum; j++)
		{
			result.PMatrix[i][j] *= constant;
		}
	}
	return result;
}
