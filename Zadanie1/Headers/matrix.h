#pragma once
using namespace std;
#include <sstream>
template <typename T>
class matrix
{
private:
	int x, y;
	T **M;
public:
	matrix();
	matrix(int in_x, int in_y);
	~matrix();
	tuple<int, int> size();
	friend ostream& operator<< (ostream& out, const matrix<T> &ex)
	{
		for (int i = 0; i < ex.y; i++) {
			for (int j = 0; j < ex.x; j++)
				out << ex.M[i][j] << " ";
			out << endl;
		}
		return out;
	}
	matrix<T> operator+ (const matrix<T> & v)
	{
		matrix<T> x;
		return x;
	}
};

#ifndef CREATE_INSTANCE
//extern template class matrix<int>;
//extern template class matrix<double>;
#endif 
