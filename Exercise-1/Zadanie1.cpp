// Zadanie1.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <iostream>
#include "Headers\matrix.h"

using namespace std;

int main()
{	

	int x1, x2, y1, y2;
	char z = 'q';
	while (z != 'z') {
		cout << "HELLO IN MATRIX PROGRAM" << endl << endl;
		cout << "First matrix dimencions:";
			cout << endl << "vertical:";
			cin >> x1;
			cout << "horizontal:";
			cin >> y1;
			cout << endl << "Second matrix dimencions:";
			cout << endl << "vertical:";
			cin >> x2;
			cout << endl << "horizontal:";
			cin >> y2;
		try {
			matrix<int> a(x1, y1);
			matrix<int> b(x2, y2);
			cout << b << endl;
			cout << a << endl;
			cout << "What do ypu want to do?" << endl;
			cout << "addition press '+'" << endl;
			cout << "subtraction press '-'" << endl;
			cout << "multiplication press '*'" << endl;
			cout << "end the program press 'z'" << endl << "";
			cin >> z;
			switch (z) {
			case '+':
				cout << a + b;
				break;
			case '-':
				cout << a - b;
				break;
			case '*':
				cout << a * b;
				break;
			case 'z':
				break;
			default:
				cout << "Unrecognizable sign" << endl;
				break;
			}
		}
		catch (string ex) {
			cout << ex << endl;
		}
	}
    return 0;
}
