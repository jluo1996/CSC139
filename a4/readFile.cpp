#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

#include "readFile.h"

vector<int> readFile(string filename, int& pageNum, int& framesNum, int& requestsNum) {
	vector<int> pages;
	string oneLine;

	ifstream fin(filename.c_str());		// open file for reading
	if (fin.is_open()) {
		// if file is opened sucessfully
		int lineNumber = 0;		// current line number

		while (getline(fin, oneLine)) {
			// keep reading each line until reach the end
			stringstream ss;
			ss << oneLine;

			if (lineNumber == 0) {
				// reading the first line which contains number of pages, number of frames, number of page requests
				ss >> pageNum >> framesNum >> requestsNum;
				lineNumber++;
			}
			else {
				int temp;
				ss >> temp;
				pages.push_back(temp);
			}
			ss.str("");		// clear the stringstream
		}
		fin.close();		// close the file after finish
	}
	else {
		// else if file cannot be opened
		cout << "File " << filename << " cannot be opened!\n";
	}

	return pages;
}