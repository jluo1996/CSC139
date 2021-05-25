#include <vector>
using namespace std;

#include "futureTable.h"

vector<int> futureTable(vector<int> pages, int requestsNum) {
	vector<int> nextUsed(requestsNum, 0);		// default next-use time is infinite

	for (int i = 0; i < requestsNum; i++) {
		int currentPage = pages.at(i);

		for (int j = i + 1; j < requestsNum; j++) {
			// only look at the pages that are after the current page
			if (pages.at(j) == currentPage) {
				// if find the same page in the future
				nextUsed.at(i) = (j - i);		// store the next-used time in the corresponding index
				break;
			}
		}
	}

	return nextUsed;
}