#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <exception>

#include "matrix.h"
#include "vector.h"
#include "Dense"

using namespace std;
//using namespace Eigen;



fstream fin;

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

	fin.open("input.txt");

	Matrix* m = nullptr;
	Vector* f = nullptr;

	int n;
	fin >> n;

	for (int i = 0; i < n; i++)
	{
		cout << "Test #" << i << "\n\n";
		read_linear_system(m, f);
		cout << m->solve_Purcell(*f) << "\n\n\n\n\n";
		delete m;
		delete f;
	}

	system("pause");
	return;
}


//Матрица Гильберта
//Норма ошибки
