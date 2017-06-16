// Zadanie1.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <iostream>
#include <tuple>
#include "Headers\matrix.h"

using namespace std;

int main()
{
	matrix<int> a(3,4);
	matrix<int> b(4,3);
	cout << b<<endl;
	cout << a<<endl;
	//a.change(2, 3, 100);
	cout << a * b;
	//matrix<int>  a * b;

	//cout << c;
	getchar();
    return 0;
}
