
#include <string>
#include <io.h> // access
#include <algorithm> //transform
#include <iostream>
#include <windows.h>

#include "../Zadanie2/Headers/dirent.h" // is not my library 

using namespace std;
void IsExist(string filename) {
	if (access(filename.c_str(), 0)){
		string err = "Directory: " + filename + " not exist";
		throw err;
	}
}
void RewriteFile(string filepath) {
	if (!access(filepath.c_str(), 0)) {
		std::cout << "File: " << filepath << " exist." << endl;
		std::cout << "Do you want rewrite it : " << filepath << " ? ";
		string res;
		while (res != "yes" && res != "no") {
			std::cout << endl << "(write Yes or No)";
			std::cin >> res;
			std::transform(res.begin(), res.end(), res.begin(), ::tolower);
		}
		if (res == "no") {
			string err = "Change directory or filename";
			throw err;
		}
	}
}
bool isDirectory(dirent * plik){
	return(plik->d_type) == DT_DIR; // || (plik->d_type)==DT_LNK;
}
void ListFile(const char* filepath) {
	struct dirent * plik;
	DIR *path;

	if ((path = opendir(filepath))) {
		while ((plik = readdir(path))) {
			puts(plik->d_name);
			if (isDirectory(plik)) {
				cout << "tak";
			}
			else {
				cout << "nie";
			}
			closedir(path);
		}
	}
	else
		cout << "Error";

}