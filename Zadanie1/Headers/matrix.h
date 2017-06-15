#include <tuple>

template <typename T>
class Matrix {
private:
	int x;
	int y;
	T **M;
public:
	Matrix(int in_x, int in_y);
	std::tuple<int, int> size();
};

template <typename T>
Matrix<T>::Matrix(int in_x, int in_y) {
	x = in_x;
	y = in_y;
	std::cout << "x";
}

template <typename T>
std::tuple<int, int > Matrix<T>::size() {
	return std::make_tuple(x, y);
}