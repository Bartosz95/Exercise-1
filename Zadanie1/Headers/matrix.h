#include <tuple>
#include "Source/matrix.cpp"

using namespace std;

template <typename T>
class Matrix {
private:
	int x;
	int y;
	T **M;
public:
	Matrix(int in_x, int in_y);
	tuple<int, int> size();
};
