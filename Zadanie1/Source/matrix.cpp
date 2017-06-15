#include "stdafx.h"
#include <iostream>
#include <tuple>
#include <cstdlib>
#include <sstream>
#include "..\Headers\matrix.h"

using namespace std;
template <typename T>
matrix<T>::matrix()
{
	this->x = 1;
	this->y = 1;
	M = new T *[1];
	M[0] = new T [1];
	M[0][0] = 1;
}
template <typename T>
matrix<T>::matrix(int in_x, int in_y)
{
	this->x = in_x;
	this->y = in_y;
	M = new T *[y];
	for (int i = 0; i < y; i++) {
		M[i] = new T [x];
		for (int j = 0; j < x; j++)
			 M[i][j] = rand();
	}
}
template <typename T>
matrix<T>::~matrix()
{
	for (int i = 0; i < y; i++) {
		delete M[i];
	}
}
template <typename T>
std::tuple<int, int > matrix<T>::size() {
	return std::make_tuple(this->x, this->y);
}
template class matrix<int>;
template class matrix<double>;