#include "../Headers/matrix.h"
#include <iostream>
//template <typename T>
Matrix::Matrix(int in_x, int in_y) {
	this->x = in_x;
	this->y = in_y;
	std::cout << "x";
}
/*
template <typename T>
std::tuple<int, int > Matrix<T>::size() {
	return std::make_tuple(x, y);
}*/