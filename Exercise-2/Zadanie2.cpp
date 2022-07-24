// Zadanie2.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include "fun.h"

using namespace std;


int main(void) {
	string dir1, dir2;
	try {
		dir1;// = "D:\\test\\";
		dir2;// = "D:\\test1\\";
		cout << "Write path to directory or file witch want change."<<endl;
		cin >> dir1;
		cout << "Write path to directory witch you want put file." << endl;
		cin >> dir2;
		IsExist(dir1); 
		typeFile(dir1);
		RewriteFile(dir2);

		MoveThisFile(dir1, dir2);
		cout << "Succes!"<<endl;
	}
	catch (string err)
	{
		cout << err << endl;
	}
	system("pause");
	return 0;
}
