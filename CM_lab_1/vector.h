#pragma once

#include <vector>
#include <fstream>

using namespace std;

struct Vector
{
	Vector() {}
	~Vector() { V.clear(); }
	Vector(fstream& file, size_t size);
	Vector(size_t size) { V.resize(size); }
	Vector(vector<double> vec)
	{
		V.resize(vec.size());
		for (size_t i = 0; i < vec.size(); i++)
			V[i] = vec[i];
	}

	vector<double> V;

	size_t size() { return V.size(); }
	void resize(size_t size) { V.resize(size); }

	double& operator [](int n) { return V[n]; }

	Vector& operator *= (double D);
	Vector& operator /= (double D);
	Vector& operator += (double D);
	Vector& operator -= (double D);

	Vector& operator += (Vector vec);
	Vector& operator -= (Vector vec);

	Vector operator * (double D);
	Vector operator / (double D);
	Vector operator + (double D);
	Vector operator - (double D);

	void print();
	void print(fstream& file);
};


inline Vector& Vector::operator *= (double D)
{
	for (size_t i = 0; i < V.size(); i++)
		V[i] *= D;
	return *this;
}

inline Vector& Vector::operator /= (double D)
{
	for (size_t i = 0; i < V.size(); i++)
		V[i] /= D;
	return *this;
}

inline Vector& Vector::operator += (double D)
{
	for (size_t i = 0; i < V.size(); i++)
		V[i] += D;
	return *this;
}

inline Vector& Vector::operator -= (double D)
{
	for (size_t i = 0; i < V.size(); i++)
		V[i] -= D;
	return *this;
}

inline Vector& Vector::operator += (Vector vec)
{
	if (V.size() != vec.size())
		throw "–азные длины складываемых векторов";
	for (size_t i = 0; i < V.size(); i++)
		V[i] += vec[i];
	return *this;
}

inline Vector& Vector::operator -= (Vector vec)
{
	if (V.size() != vec.size())
		throw "–азные длины складываемых векторов";
	for (size_t i = 0; i < V.size(); i++)
		V[i] -= vec[i];
	return *this;
}

inline Vector Vector::operator * (double D)
{
	Vector ans(V.size());
	for (size_t i = 0; i < V.size(); i++)
		ans.V[i] = V[i] * D;
	return Vector(ans.V);
}

inline Vector Vector::operator / (double D)
{
	Vector ans(V.size());
	for (size_t i = 0; i < V.size(); i++)
		ans.V[i] = V[i] / D;
	return Vector(ans.V);
}

inline Vector Vector::operator + (double D)
{
	Vector ans(V.size());
	for (size_t i = 0; i < V.size(); i++)
		ans.V[i] = V[i] + D;
	return Vector(ans.V);
}

inline Vector Vector::operator - (double D)
{
	Vector ans(V.size());
	for (size_t i = 0; i < V.size(); i++)
		ans.V[i] = V[i] - D;
	return Vector(ans.V);
}

