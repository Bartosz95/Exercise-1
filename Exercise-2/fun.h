 // is not my library 
#include "stdafx.h"
#include "dirent.h"

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
		std::cout << "Do you want rewrite/append: " << filepath << " ? ";
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
	return(plik->d_type) == DT_DIR;
}
bool isRegularFile(dirent * plik) {
	return(plik->d_type) == DT_REG;
}
bool FilePermissions(string dirname) {
	if (closedir(opendir(dirname.c_str())) == 0)
		return true;
	else {
		string err = "You don't have a access to this file: " + (string)dirname;
		throw err;
	}
}
void MoveThisFile(string filepath, string newfilepath) {
	struct dirent * plik;
	DIR *path;
	FilePermissions(filepath);
	FilePermissions(newfilepath);
	if ((path = opendir(filepath.c_str()))) {
		while ((plik = readdir(path))) {
			if ((((string)plik->d_name)==(string)".")||(((string)plik->d_name) == (string)"..")) {
			}
			else if (isDirectory(plik)) {
				const char * a = "\\";
				string newpath = newfilepath + (string)a + plik->d_name+a+a;
				string newdir = newfilepath + (string)a + plik->d_name;
				string olddir = filepath + plik->d_name + a + a;
				if(CreateDirectoryA((LPCSTR)newdir.c_str(), NULL)) {
					MoveThisFile(olddir, newpath);
					RemoveDirectoryA(olddir.c_str());
				}
				else if (!access(newpath.c_str(), 0)) {
					MoveThisFile(olddir, newpath);
					RemoveDirectoryA(olddir.c_str());
				}else{
					string err = "You can't create directory: "+ newdir;
					throw err;
				}
			}
			else if(isRegularFile(plik)) {
				string newpath = filepath + plik->d_name;
				string newdir = newfilepath + plik->d_name;
				MoveFileA((LPCSTR)newpath.c_str(), (LPCSTR)newdir.c_str());
			}
		}
		closedir(path);
	}
	else
		cout << "Error";

}
void typeFile(string filepath) {
	struct dirent * plik;
	DIR *path;
	string res;
	if ((path = opendir(filepath.c_str()))) {
		if ((plik = readdir(path))) {
			if(isRegularFile(plik)) {
				std::cout << "Do you want a move file: " << filepath << " to another directory?" << endl;
				while (res != "yes" && res != "no") {
					std::cout << endl << "(write Yes or No)";
					std::cin >> res;
					std::transform(res.begin(), res.end(), res.begin(), ::tolower);
				}
			}
			else if (isDirectory(plik)) {
				std::cout << "This is a directory. Do you want move this directory with a file?"<<endl<<"(path: " << filepath << ")" << endl;
				while (res != "yes" && res != "no") {
					std::cout << endl << "(write Yes or No)";
					std::cin >> res;
					std::transform(res.begin(), res.end(), res.begin(), ::tolower);
				}
			}
			else {
				string err = "Unknow file or directory. You can't move it.";
				throw err;
			}
			if (res == "no") {
				string err = "program is close.";
				throw err;
			}
		}
	}
}
