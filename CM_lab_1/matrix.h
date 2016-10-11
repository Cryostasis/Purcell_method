#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include "vector.h"

using namespace std;

struct Matrix
{
	Matrix() {}
	~Matrix() { M.clear(); }
	Matrix(size_t size) { M.resize(size); }
	Matrix(vector<Vector> vec);
	Matrix(fstream& file, size_t sizeX, size_t sizeY = -1);

	vector<Vector> M;

	size_t size() { return M.size(); }
	void resize(size_t size) { M.resize(size); }

	Vector& operator[](int n) { return M[n]; }

	void print();
	void print(fstream& file);

	double norm_1();
	double norm_e();
	double norm_inf();

	double condition_number_1();
	double condition_number_e();
	double condition_number_inf();

	Matrix Matrix::invertible_mat();
	Vector solve_gauss(Vector B);
	Vector solve_purcell(Vector B);

};

Matrix identity_matrix(size_t size);
