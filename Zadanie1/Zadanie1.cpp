// Zadanie1.cpp: Okre�la punkt wej�cia dla aplikacji konsoli.
//

#include "stdafx.h"
#include "iostream"
#include <tuple>

#include "Headers\matrix.hpp"

using namespace std;
int main()
{
	Matrix<int> x(2, 5);
	auto size = x.size();
	cout << get<0>(size)<<endl;
	cout << get<1>(size)<<endl;
 
	getchar();
    return 0;
}
