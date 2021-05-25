#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "find.h"
#include "decrement.h"
#include "int_to_string.h"
#include "futureTable.h"
#include "findMaxIndex.h"
#include "findMinIndex.h"
#include "firstInFirstOut.h"
#include "optimal.h"
#include "leastRecentlyUsed.h"
#include "writeFile.h"
#include "readFile.h"


int main() {
	string inputFilename = "input.txt";
	string outputFilename = "output.txt";
	string content = "";

	vector<int> pages;
	int pageNum, framesNum, requestsNum;

	pages = readFile(inputFilename, pageNum, framesNum, requestsNum);
	content += firstInFirstOut(pages, framesNum, requestsNum) + "\n";
	content += optimal(pages, framesNum, requestsNum) + "\n";
	content += leastRecentlyUsed(pages, framesNum, requestsNum);
	writeFile(outputFilename, content);

	cout << "Complete!!!" << endl;

	return 0;
}