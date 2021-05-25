#include <vector>
using namespace std;

#include "decrement.h"

void decrement(vector<int>& v) {
	for (int i = 0; i < v.size(); i++) {
		if (v.at(i) > 0) {
			v.at(i)--;
		}
	}
}