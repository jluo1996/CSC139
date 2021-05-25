#include <vector>
#include <string>
using namespace std;

#include "optimal.h"
#include "futureTable.h"
#include "int_to_string.h"
#include "findMaxIndex.h"
#include "find.h"
#include "decrement.h"

string optimal(vector<int> pages, int framesNum, int requestsNum) {
	vector<int> nextUse = futureTable(pages, requestsNum);		// get a corresponding next-use table
	vector<int> frames(framesNum);		// simulate frames
	vector<int> nextUseInFrames(framesNum);
	int index = 0;			// index of frames
	int freeFrame = framesNum;
	int pageFault = 0;			// record how many page faults occur
	string output = "Optimal\n";

	if (requestsNum > 0) {
		// if there is page request
		for (int i = 0; i < requestsNum; i++) {
			int currentRequestingPage = pages.at(i);
			int currentRequestingPageNextUseTime = nextUse.at(i);
			if (find(frames, currentRequestingPage)) {
				// if current requesting page is not in the frames
				if (freeFrame > 0) {
					// if there are still free frames
					frames.at(index) = currentRequestingPage;		// store the page 
					nextUseInFrames.at(index) = currentRequestingPageNextUseTime;		// update its next-use time
					pageFault++;
					output += ("Page " + int_to_string(currentRequestingPage) + " loaded into Frame " + int_to_string(index) + "\n");
					index++;
					freeFrame--;
				}
				else {
					// if all frames are used
					int index = findMaxIndex(nextUseInFrames, framesNum);
					int replacePageNum = frames.at(index);		// get the page number we are going to replace
					for (index = 0; index < framesNum; index++) {
						// find the replacing page number
						if (frames.at(index) == replacePageNum) {
							frames.at(index) = currentRequestingPage;
							nextUseInFrames.at(index) = currentRequestingPageNextUseTime;		// update its next-use time
							pageFault++;
							output += ("Page " + int_to_string(replacePageNum) + " unloaded from Frame " + int_to_string(index) + ", Page " + int_to_string(currentRequestingPage) + " loaded into Frame " + int_to_string(index) + "\n");
							break;
						}
					}
				}
			}
			else {
				// else if current requesting page is already in one of the frames
				for (int j = 0; j < framesNum; j++) {
					if (frames.at(j) == currentRequestingPage) {
						nextUseInFrames.at(j) = currentRequestingPageNextUseTime;
						output += ("Page " + int_to_string(currentRequestingPage) + " already in Frame " + int_to_string(j) + "\n");
						break;
					}
				}
			}
			decrement(nextUseInFrames);
		}
	}
	output += (int_to_string(pageFault) + " page faults" + "\n");

	return output;
}