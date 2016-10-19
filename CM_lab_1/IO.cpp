#include <fstream>

#include "types.h"
#include "IO.h"

using namespace std;

Matrix read_matrix(fstream& in, size_t sizeX, size_t sizeY)
{
	sizeY = sizeY == -1 ? sizeX : sizeY;
	Matrix ans(sizeX);

	for (size_t i = 0; i < sizeX; i++)
		ans[i].resize(sizeY);

	for (size_t i = 0; i < sizeX; i++)
		for (size_t j = 0; j < sizeY; j++)
			in >> ans[i][j];
	return ans;
}

Vector read_vector(fstream& in, size_t size)
{
	Vector ans(size);
	for (size_t i = 0; i < size; i++)
		in >> ans[i];
	return ans;
}

void print_matrix(fstream& out, Matrix M)
{
	for (size_t i = 0; i < M.size(); i++)
	{
		for (size_t j = 0; j < M[i].size(); j++)
			out << M[i][j] << " ";
		out << "\n";
	}
}

void print_vector(fstream& out, Vector V)
{
	for (size_t i = 0; i < V.size(); i++)
		out << V[i] << " ";
	out << "\n";
}