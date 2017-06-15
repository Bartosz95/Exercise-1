// Zadanie1.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <iostream>
#include <tuple>
#include "Headers\matrix.h"

using namespace std;

int main()
{
	matrix<int> a(10,5);
	matrix<int> b(3, 4);

	a + b;
	matrix<int> c;
	cout << c;
 
	getchar();
    return 0;
}
