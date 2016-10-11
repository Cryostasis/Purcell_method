#pragma once

#include <fstream>
#include "types.h"

using namespace std;

Matrix read_matrix(fstream& in, size_t sizeX, size_t sizeY = -1);
Vector read_vector(fstream& in, size_t size);
void print_matrix(fstream& out, Matrix M);
void print_vector(fstream& out, Vector V);
