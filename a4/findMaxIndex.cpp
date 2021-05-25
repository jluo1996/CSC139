#include <vector>
using namespace std;

#include "findMaxIndex.h"

int findMaxIndex(vector<int> v, int size) {
	int index = 0;
	int max = -1;

	for (int i = 0; i < size; i++) {
		if (v.at(i) == 0) {
			// if this is the first infinite next-use time we find
			return i;	// return as soon as we find a zero
		}
		else if (v.at(i) > max) {
			// else if we found a longer next-use time
			max = v.at(i);			// update max
			index = i;
		}
	}

	return index;
}