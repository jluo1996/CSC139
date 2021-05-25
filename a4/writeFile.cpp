#include <string>
#include <fstream>
#include <iostream>
using namespace std;

#include "writeFile.h"

void writeFile(string fileName, string content) {
	ofstream fout(fileName.c_str());		// open file for writing

	if (fout.is_open()) {
		// if file is open sucessfully
		fout << content;	// write content to the file
		fout.close();		// close file when finish
	}
	else {
		// if file cannot be opened
		cout << "File " << fileName << " cannot be opened!\n";
	}
	return;
}