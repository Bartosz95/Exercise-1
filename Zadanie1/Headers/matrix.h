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
	//KONSTRUKTORY
	matrix();
	matrix(int in_x, int in_y);
	~matrix();

	tuple<int, int> size();
	const int get_x();
	int get_y();
	void change(int in_x, int in_y,T value);

	friend ostream& operator<< (ostream& out, const matrix<T> &obj)
	{
		for (int i = 0; i < obj.x; i++) {
			for (int j = 0; j < obj.y; j++)
				out << obj.M[i][j] << " ";
			out << endl;
		}
		return out;
	}
	matrix<T> & operator= (const matrix<T> &obj);
	matrix<T> operator+ (const matrix<T> & obj);
	matrix<T> operator- (const matrix<T> & obj);
	matrix<T> operator* (const matrix<T> & obj);
};

#ifndef CREATE_INSTANCE
//extern template class matrix<int>;
//extern template class matrix<double>;
#endif 
