#include "norms.h"
#include "types.h"
#include <algorithm>

double norm_1(Matrix M)
{
	double ans = 0;
	for (size_t i = 0; i < M.size(); i++)
	{
		double buf = 0;
		for (size_t j = 0; j < M[i].size(); j++)
			buf += fabs(M[i][j]);
		ans = std::max(ans, buf);
	}
	return ans;
}

double norm_inf(Matrix M)
{
	double ans = 0;
	for (size_t i = 0; i < M.size(); i++)
	{
		double buf = 0;
		for (size_t j = 0; j < M[i].size(); j++)
			buf += fabs(M[j][i]);
		ans = std::max(ans, buf);
	}
	return ans;
}

double norm_e(Matrix M)
{
	double ans = 0;
	for (size_t i = 0; i < M.size(); i++)
		for (size_t j = 0; j < M[i].size(); j++)
			ans += M[j][i] * M[j][i];

	return sqrt(ans);
}