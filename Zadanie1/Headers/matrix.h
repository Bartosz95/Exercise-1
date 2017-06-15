#pragma once
template <typename T>
class matrix
{
public:
	matrix();
	matrix(int in_x, int in_y);
	~matrix();
	//std::tuple<int, int> size();
};

#ifndef CREATE_INSTANCE
extern template class matrix<int>;
extern template class matrix<double>;
#endif 
