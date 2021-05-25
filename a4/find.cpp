#include <vector>
using namespace std;

#include "find.h"

bool find(vector<int> v, int target) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
		if (*it == target) {
			return false;		// return false when found
		}
	}

	return true;		// if not found, return true
}