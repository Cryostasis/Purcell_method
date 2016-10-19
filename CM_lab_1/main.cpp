#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <exception>

#include "matrix.h"
#include "vector.h"
#include "Dense"
 
#include <cstdlib> 
#include <ctime>
#include <Windows.h>

using namespace std;
//using namespace Eigen;

const double EPS = 1e-8;
const int min_value = -1e6;
const int max_value = 1e6;
const int max_size = 1000;

fstream fin;
ofstream fout;

void test_rnd(int cnt)
{
	fout << "Тестирование на произвольных матрицах" << endl;
	for (int k = 0; k < cnt; k++)
	{
		size_t size = rand() % max_size + 2;
		fout << "Размерность = " << size << endl;

		Eigen::MatrixXd example_mat(size, size);
		Eigen::VectorXd	example_vec(size);

		Matrix mat(size);
		Vector f(size);

		for (int i = 0; i < size; i++)
		{
			f[i] = example_vec(i) = 
				(double)(rand() % (max_value * 2) + min_value) /
				(double)(rand() % (max_value * 2) + min_value);
			for (int j = 0; j < size; j++)
				mat[i][j] = example_mat(i, j) =
					(double)(rand() % (max_value * 2) + min_value) / 
					(double)(rand() % (max_value * 2) + min_value);
		}
		Eigen::VectorXd example_X = example_mat.fullPivLu().solve(example_vec);
		long long tick = GetTickCount64();
		Vector X = mat.solve_Purcell(f);
		long long diff = GetTickCount64() - tick;

		double err = 0;
		for (int i = 0; i < size; i++)
			err += fabs(X[i] - example_X(i));

		Eigen::JacobiSVD<Eigen::MatrixXd> svd(example_mat);
		double cond = 
			svd.singularValues()(0) 
			/ svd.singularValues()(svd.singularValues().size() - 1);

		fout << "Время выполнения(в миллисекундах) = " << diff << endl;
		fout << "Число обусловленности = " << cond << endl;
		fout << "Средняя разница между методами = " << err / size << endl;
		fout << "\n\n";
	}
	std::cout << "\n\n\n\n\n\n";
}

void test_Hilbert(int size)
{
	for (int k = 2; k < size; k++)
	{
		Matrix mat(k);
		Vector f(k, 0);
		for (int i = 0; i < k; i++)
			for (int j = 0; j < k; j++)
				f[i] += (mat[i][j] = 1.0 / (i + j + 1));

		Vector X = mat.solve_Purcell(f);
		double err = 0;
		for (int i = 0; i < k; i++)
			err += fabs(X[i] - 1);

		fout << "Размерность = " << k << endl;
		fout << "Число обусловленности = " << mat.condition_number_inf() << endl;
		fout << "Средняя ошибка решения = " << err / k << endl;
		fout << "\n\n";
	}
}

void test_Lehmer(int size)
{
	Matrix mat(size);
	Vector f(size, 0);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			f[i] += (mat[i][j] = fmin(i + 1, j + 1) / fmax(i + 1, j + 1));

	Vector X = mat.solve_Purcell(f);
	double err = 0;
	for (int i = 0; i < size; i++)
		err += fabs(X[i] - 1);

	fout << "Размерность = " << size << endl;
	fout << "Число обусловленности = " << mat.condition_number_inf() << endl;
	fout << "Средняя ошибка решения = " << err / size << endl;
	fout << "\n\n";
}

void read_linear_system(Matrix*& m, Vector*& f)
{
	int n;
	fin >> n;
	m = new Matrix(fin, n);
	f = new Vector(fin, n);
}

void main()
{
	setlocale(LC_ALL, "Russian");

	srand(time(NULL));

	fin.open("input.txt");
	fout.open("output.txt");

	Matrix* m = nullptr;
	Vector* f = nullptr;

	int n;
	fin >> n;


	//test_rnd(100);
	
	for (int i = 300; i <= 500; i += 10)
		test_Lehmer(i);


	system("pause");
	return;
}

