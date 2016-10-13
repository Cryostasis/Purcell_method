#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <exception>

#include "Dense"

using namespace std;
using namespace Eigen;

fstream fin;

VectorXd solve_purcell(MatrixXd mat, VectorXd f)
{
	if (mat.rows() != mat.cols() || f.size() != mat.rows())
		throw std::exception("Wrong matrix/vector size");

	size_t size = mat.rows();
	MatrixXd V(size + 1, size + 1);
	MatrixXd A(size, size + 1);
	A << mat, -f;
	V.setIdentity();
	for (size_t k = 0; k < size; k++)
	{
		VectorXd Vbuf_k = V.col(k);
		for (size_t j = k + 1; j < size + 1; j++)

			V.col(j) = V.col(j) - Vbuf_k * 
				(A.row(k).dot(V.col(j)) /
				A.row(k).dot(Vbuf_k));
		cout << V << "\n\n";
	}
	return V.col(size).block(0, 0, size, 1);
}

void read_linear_system(MatrixXd& m, VectorXd& f)
{
	int sz;
	fin >> sz;
	m.resize(sz, sz);
	f.resize(sz);
	for (int i = 0; i < sz; i++)
		for (int j = 0; j < sz; j++)
			fin >> m(i, j);
	for (int i = 0; i < sz; i++)
		fin >> f(i);
}

void main()
{
	setlocale(LC_ALL, "Russian");

	fin.open("input.txt");

	MatrixXd m;
	VectorXd f;

	int n;
	fin >> n;

	for (int i = 0; i < n; i++)
	{
		cout << "Text �" << i << "\n\n";
		read_linear_system(m, f);
		cout << solve_purcell(m, f) << "\n\n\n\n\n";
	}

	system("pause");
	return;
}


//Матрица Гильберта
//Норма ошибки
