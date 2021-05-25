#include <vector>
using namespace std;

#include "findMinIndex.h"

int findMinIndex(vector<int> v, int size) {
	int index = 0;
	int min = v.at(index);

	for (int i = 1; i < size; i++) {
		if (v.at(i) < min) {
			min = v.at(i);
			index = i;
		}
	}

	return index;
}