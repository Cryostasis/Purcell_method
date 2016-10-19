#include <fstream>
#include <iostream>
#include <algorithm>

#include "vector.h"
#include "matrix.h"

void Matrix::set_identity(size_t size)
{
	M.resize(size);
	for (size_t i = 0; i < size; i++)
	{
		M[i].resize(size);
		M[i][i] = 1;
	}
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
		for (size_t j = i - 1; j > -1; j--)
		{
			ans[j] -= ans[i] * Mat[j][i];
			Mat[j] -= Mat[i] * Mat[j][i];
		}
	}

	return ans;
}

Vector Matrix::solve_Purcell(Vector f)
{
	if (M.size() != f.size())
		throw std::exception("Vector size");

	size_t size = M.size();
	Matrix V;
	V.set_identity(size + 1);
	//vector<Vector> A(size, size + 1);

	for (size_t k = 0; k < size; k++)
	{
		Vector Vbuf_k(V[k]);
		for (size_t j = k + 1; j < size + 1; j++)
			V[j] -= Vbuf_k * 
				dot_purcell_aux(f, V[j], k) /
				dot_purcell_aux(f, Vbuf_k, k);
		//cout << V << "\n\n";
	}
	return V[size].block(0, size);
}

Matrix Matrix::get_inverted()
{
	Matrix Mat(M);
	size_t size = M.size();
	Matrix ans;
	ans.set_identity(size);
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
		for (size_t j = i - 1; j > -1; j--)
		{
			ans[j] -= ans[i] * Mat[j][i];
			Mat[j] -= Mat[i] * Mat[j][i];
		}
	}

	return ans;
}

Vector Matrix::operator()(size_t n)
{
	Vector ans(M.size());
	for (size_t i = 0; i < M.size(); i++)
		ans[i] = M[i][n];
	return ans;
}

Vector Matrix::operator*(Vector vec)
{
	if (vec.size() != M[0].size())
		throw "213";
	size_t n = M.size();
	Vector ans(n);
	for (size_t i = 0; i < n; i++)
		ans[i] = M[i].dot(vec);
	
	return ans;
}

Matrix Matrix::operator*(Matrix mat)
{
	if (mat.size() != M[0].size())
		throw "456";
	size_t n = M.size(), m = M[0].size();
	Matrix ans(n);
	for (size_t i = 0; i < n; i++)
	{
		ans[i].resize(m);
		for (size_t j = 0; i < m; i++)
			ans[i][j] = M[i].dot(mat(j));
	}

	return ans;
}

void Matrix::print(ostream& stream)
{
	for (size_t i = 0; i < M.size(); i++)
	{
		for (size_t j = 0; j < M[i].size(); j++)
			stream << M[i][j] << " ";
		stream << "\n";
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

Matrix::Matrix(vector<Vector> vec) : M(vec.size())
{
	for (size_t i = 0; i < vec.size(); i++)
		M[i] = Vector(vec[i]);
}

Matrix::Matrix(fstream& file, size_t size) : M(size)
{
	init_frome_file(file, size);
}

void Matrix::init_frome_file(fstream & file, size_t size)
{
	for (size_t i = 0; i < size; i++)
		M[i].resize(size);

	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
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
	return norm_1() * get_inverted().norm_1();
}

double Matrix::condition_number_e()
{
	return norm_e() * get_inverted().norm_e();
}

double Matrix::condition_number_inf()
{
	return norm_inf() * get_inverted().norm_inf();
}
