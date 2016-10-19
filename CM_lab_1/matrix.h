#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include "vector.h"

using namespace std;

struct Matrix
{
	Matrix() {}
	Matrix(size_t size) { M.resize(size); }
	Matrix(size_t size, double fill) : Matrix(size) 
	{
		for (size_t i = 0; i < size; i++)
			M[i] = Vector(size, fill);
	}
	Matrix(vector<Vector> vec);
	Matrix(fstream& file, size_t size);

	Matrix(Matrix && mat)
	{

	}

	void init_frome_file(fstream& file, size_t size);

	vector<Vector> M;

	size_t size() { return M.size(); }
	void resize(size_t size) { M.resize(size); }

	Vector& operator[](size_t n) { return M[n]; }
	Vector operator()(size_t n);

	Vector operator * (Vector vec);
	Matrix operator * (Matrix mat);

	void print(ostream& stream);
	void print(fstream& file);

	void Matrix::set_identity(size_t size);

	double norm_1();
	double norm_e();
	double norm_inf();

	double condition_number_1();
	double condition_number_e();
	double condition_number_inf();

	Matrix get_inverted();
	Vector solve_gauss(Vector B);
	Vector solve_Purcell(Vector f);

private:
	double Matrix::dot_purcell_aux(Vector& f, Vector& dot, size_t ind)
	{
		double ans = 0;
		size_t size = M.size();
		for (size_t i = 0; i < size; i++)
			ans += M[ind][i] * dot[i];
		return ans - f[ind] * dot[size];
	}
};

inline ostream& operator << (ostream& stream, Matrix& m) 
{ 
	m.print(stream);
	return stream;
}

