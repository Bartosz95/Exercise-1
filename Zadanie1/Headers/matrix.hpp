#include <tuple>

using namespace std;

template <typename T>
class Matrix {
private:
	int x;
	int y;
	T **M;
public:
	Matrix(int in_x, int in_y) {
		x = in_x;
		y = in_y;
		M = nullptr;
	}
	tuple<int, int> size() {
		return make_tuple(x, y);
	}
};
