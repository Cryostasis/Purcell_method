#include "matrix.h"
#include "vector.h"

Vector::Vector(fstream& file, size_t size)
{
	V.resize(size);
	for (size_t i = 0; i < size; i++)
		file >> V[i];
}

void Vector::print()
{
	for (size_t i = 0; i < V.size(); i++)
		cout << V[i] << endl;
}

void Vector::print(fstream& file)
{
	for (size_t i = 0; i < V.size(); i++)
		file << V[i] << endl;
}