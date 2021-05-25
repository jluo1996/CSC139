#include <string>
#include <sstream>
using namespace std;

#include "int_to_string.h"

string int_to_string(int num) {
	stringstream ss;
	string output;

	ss << num;
	ss >> output;

	return output;
}