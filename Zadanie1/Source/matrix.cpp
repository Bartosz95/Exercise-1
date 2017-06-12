#include <iostream>
#include <tuple>
#include "Headers/matrix.hpp"

template <typename T>
Matrix::Matrix(int in_x, int in_y) {
	x = in_x;
	y = in_y;
	std::cout << "x";
	M = new int *[x];
	for (int i = 0; i < x; i++) {
		M[i] = new T[y];
		for (j = 0; j < y; j++) {
			M[j] = 0;
			std::cout << "1" << " ";
		}cout << endl;
	}
}
template <typename T>
Matrix::tuple<int,int > size() {
	return make_tuple(x, y);
}