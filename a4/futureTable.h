#ifndef FUTURETABLE_H
#define FUTURETABLE_H

// return an associcating vector with next-use time
/*	Example:
		vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1}
	vector<int> nextUse = {17, 3, 11, 5, 2, 4, 4, 0, 4, 2, 5, 0, 2, 3, 0, 3, 3, 0, 0, 0}

	0 indicates it is not going to be used in the future (infinite next-use time)	*/
vector<int> futureTable(vector<int> pages, int requestsNum);

#endif // !FUTURETABLE_H
