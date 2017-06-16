#include "stdafx.h"
#include <iostream>
#include <tuple>
#include <cstdlib>
#include <sstream>
#include <exception>
#include <string>
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
	if ((in_x > this->x) && (in_x < 0)) {
		string ex = "wrong dimensions of x";
		throw ex;
	}
	if ((in_y > this->y) && (in_y < 0)) {
		string ex = "wrong dimensions of y";
		throw ex;
	}
	this->x = in_x;
	this->y = in_y;
	M = new T *[x];
	for (int i = 0; i < x; i++) {
		M[i] = new T [y];
		for (int j = 0; j < y; j++)
			 M[i][j] = 2*i+j;
	}
}
template <typename T>
matrix<T>::~matrix()
{
	for (int i = 0; i < x; i++) {
		//delete[] this->M[i];
	}
	//delete[] this->M;
}
template <typename T>
tuple<int, int > matrix<T>::size() {
	return std::make_tuple(this->x, this->y);
}
template <typename T>
const int matrix<T>::get_x() {
	return this->x;
}
template <typename T>
int matrix<T>::get_y() {
	return this->y;
}
template <typename T>
void  matrix<T>::change(int in_x, int in_y, T value) {
	if ((in_x > this->x) && (in_x < 0)) {
		string ex = "wrong dimensions of x";
		throw ex;
	}
	if ((in_y > this->y) && (in_y < 0)) {
		string ex = "wrong dimensions of y";
		throw ex;
	}
	this->M[in_x][in_y] = value;
}
template <typename T>
matrix<T> & matrix<T>::operator= (const matrix<T> &obj)
{
	if ((this->x != obj.x) || (this->y != obj.y)) {
		string ex = "wrong dimensions of matrix";
		throw ex;
	}
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++)
			this->M[i][j] = obj.M[i][j];
	}
	return *this;
}
template <typename T>
matrix<T> matrix<T>::operator+ (const matrix<T> & obj)
{
	if((this->x != obj.x)||(this->y != obj.y)) {
		string ex = "wrong dimensions of matrix to addition";
		throw ex;
	}
	matrix<T> ret(this->x, this->y);
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++)
			ret.change(i,j,this->M[i][j] + obj.M[i][j]);
	}
	return ret;
}
template <typename T>
matrix<T> matrix<T>::operator- (const matrix<T> & obj)
{
	if ((this->x != obj.x) || (this->y != obj.y)) {
		string ex = "wrong dimensions of matrix to subtraction";
		throw ex;
	}
	matrix<T> ret(this->x, this->y);
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++)
			ret.change(i, j, this->M[i][j] - obj.M[i][j]);
	}
	return ret;
}
template <typename T>
matrix<T> matrix<T>::operator* (const matrix<T> & obj)
{
	if (this->y != obj.x) {
		string ex = "wrong dimensions of matrix to multiplication";
		throw ex;
	}
	matrix<T> ret(this->x,obj.y);
	T val;
	for (int i = 0; i < this->x; i++) {
		for (int j = 0; j < obj.y; j++) {
			val = 0;
			for (int k = 0; k<this->y; k++)
				val += this->M[i][k] * obj.M[k][j];
			ret.change(i, j, val);
		}
	}
	return ret;
}

template class matrix<int>;
template class matrix<double>;