#include "stdafx.h"
#include <iostream>
#include "..\Headers\matrix.h"

template <typename T>
matrix<T>::matrix()
{
	std::cout << "Helloworld";
}
template <typename T>
matrix<T>::matrix(int in_x, int in_y)
{
	std::cout << in_x << "Helloworld"<< in_y;
}
template <typename T>
matrix<T>::~matrix()
{
}
template class matrix<int>;
template class matrix<double>;