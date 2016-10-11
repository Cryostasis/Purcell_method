#include <fstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>

//#include "Dense"

#include "vector.h"
#include "matrix.h"

using namespace std;

//using namespace Eigen;

void main()
{
	setlocale(LC_ALL, "Russian");

	fstream input, output;
	input.open("input.txt", fstream::in);
	output.open("output.txt", fstream::out);
	
	int n;
	input >> n;
	Matrix M(input, n);
	Vector B(input, n);

	//cout << norm_1(M) << " " << norm_e(M) << " " << norm_inf(M) << endl;
	
	//cout << M.norm_inf() << " " << M.invertible_mat().norm_inf() << "\n\n";
	
	//cout << M.condition_number_e() << endl;
	//cout << M.condition_number_inf() << endl;
	
	//M.invertible_mat().print();

	cout << "При e = 10^0:\n";
	cout << "Число обусловленности:\n" << M.condition_number_1() << "\nРешение системы:\n";
	M.solve_gauss(B).print();

	system("pause");
	return;
}