#include <fstream>
#include <iostream>
#include <algorithm>

#include "vector.h"
#include "matrix.h"

Matrix identity_matrix(size_t size)
{
	Matrix ans(size);
	for (size_t i = 0; i < size; i++)
	{
		ans[i].resize(size);
		ans[i][i] = 1;
	}
	return ans;
}

Vector Matrix::solve_gauss(Vector B)
{
	Matrix Mat(M);
	size_t size = M.size();
	Vector ans = Vector(B);

	for (size_t i = 0; i < size; i++)
	{
		ans[i] /= Mat[i][i];
		Mat[i] /= Mat[i][i];

		for (size_t j = i + 1; j < size; j++)
		{
			ans[j] -= ans[i] * Mat[j][i];
			Mat[j] -= Mat[i] * Mat[j][i];
		}
	}

	for (size_t i = size - 1; i > 0; i--)
	{
		for (int j = i - 1; j > -1; j--)
		{
			ans[j] -= ans[i] * Mat[j][i];
			Mat[j] -= Mat[i] * Mat[j][i];
		}
	}

	return ans;
}

Vector Matrix::solve_purcell(Vector B)
{
	size_t size = M.size();
	Matrix V = identity_matrix(size + 1)

	return Vector();
}

Matrix Matrix::invertible_mat()
{
	Matrix Mat(M);
	size_t size = M.size();
	Matrix ans = identity_matrix(size);

	for (size_t i = 0; i < size; i++)
	{
		ans[i] /= Mat[i][i];
		Mat[i] /= Mat[i][i];

		for (size_t j = i + 1; j < size; j++)
		{
			ans[j] -= ans[i] * Mat[j][i];
			Mat[j] -= Mat[i] * Mat[j][i];
		}
	}

	for (size_t i = size - 1; i > 0; i--)
	{
		for (int j = i - 1; j > -1; j--)
		{
			ans[j] -= ans[i] * Mat[j][i];
			Mat[j] -= Mat[i] * Mat[j][i];
		}
	}

	return ans;
}

void Matrix::print()
{
	for (size_t i = 0; i < M.size(); i++)
	{
		for (size_t j = 0; j < M[i].size(); j++)
			cout << M[i][j] << " ";
		cout << "\n";
	}
}

void Matrix::print(fstream& file)
{
	for (size_t i = 0; i < M.size(); i++)
	{
		for (size_t j = 0; j < M[i].size(); j++)
			file << M[i][j] << " ";
		file << "\n";
	}
}

Matrix::Matrix(vector<Vector> vec)
{
	M.resize(vec.size());
	for (size_t i = 0; i < vec.size(); i++)
	{
		M[i].resize(vec[i].size());
		for (size_t j = 0; j < vec[i].size(); j++)
			M[i][j] = vec[i][j];
	}
}

Matrix::Matrix(fstream& file, size_t sizeX, size_t sizeY)
{
	sizeY = sizeY == -1 ? sizeX : sizeY;
	M.resize(sizeX);

	for (size_t i = 0; i < sizeX; i++)
		M[i].resize(sizeY);

	for (size_t i = 0; i < sizeX; i++)
		for (size_t j = 0; j < sizeY; j++)
			file >> M[i][j];
}

double Matrix::norm_inf()
{
	double ans = 0;
	for (size_t i = 0; i < M.size(); i++)
	{
		double buf = 0;
		for (size_t j = 0; j < M[i].size(); j++)
			buf += fabs(M[i][j]);
		ans = std::max(ans, buf);
	}
	return ans;
}

double Matrix::norm_1()
{
	double ans = 0;
	for (size_t i = 0; i < M.size(); i++)
	{
		double buf = 0;
		for (size_t j = 0; j < M[i].size(); j++)
			buf += fabs(M[j][i]);
		ans = std::max(ans, buf);
	}
	return ans;
}

double Matrix::norm_e()
{
	double ans = 0;
	for (size_t i = 0; i < M.size(); i++)
		for (size_t j = 0; j < M[i].size(); j++)
			ans += M[j][i] * M[j][i];

	return sqrt(ans);
}

double Matrix::condition_number_1()
{
	return norm_1() * invertible_mat().norm_1();
}

double Matrix::condition_number_e()
{
	return norm_e() * invertible_mat().norm_e();
}

double Matrix::condition_number_inf()
{
	return norm_inf() * invertible_mat().norm_inf();
}
