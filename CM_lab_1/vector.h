#pragma once

#include <vector>
#include <fstream>

using namespace std;

struct Vector
{
	Vector() {};
	Vector(fstream& file, size_t size);
	Vector(size_t size) { V.resize(size); };
	Vector(size_t size, double fill) : V(size, fill) {};
	Vector(vector<double>& vec) : V(vec) {};

	Vector(const Vector& vec) : V(vec.V) {};
	Vector(Vector&& vec) : V(std::move(vec.V)) {};

	vector<double> V;

	size_t size() { return V.size(); }
	void resize(size_t size) { V.resize(size); }

	double& operator [](size_t n) { return V[n]; }

	double dot(Vector vec)
	{
		double ans = 0;
		for (size_t i = 0; i < V.size(); i++)
			ans += V[i] * vec[i];
		return ans;
	}

	Vector block(size_t begin, size_t size)
	{
		return Vector(vector<double>(V.begin() + begin, V.begin() + begin + size));
	}

	Vector& operator *= (const double D);
	Vector& operator /= (const double D);
	Vector& operator += (const double D);
	Vector& operator -= (const double D);

	Vector& operator += (const Vector vec);
	Vector& operator -= (const Vector vec);

	Vector operator - (const Vector vec);

	Vector operator * (const double D);
	Vector operator / (const double D);
	Vector operator + (const double D);
	Vector operator - (const double D);

	Vector& operator = (Vector && vec) 
	{
		if (this == &vec)
			throw std::exception("Wrong rvlue");
		V = std::move(vec.V);
		return *this;
	}

	void print(ostream& stream);
	void print(fstream& file);
};

inline ostream& operator << (ostream& stream, Vector& vec) 
{ 
	vec.print(stream); 
	return stream; 
}



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

inline Vector Vector::operator - (Vector vec)
{

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

