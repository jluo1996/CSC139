#include <string>
#include <vector>
using namespace std;

#include "leastRecentlyUsed.h"
#include "find.h"
#include "findMinIndex.h"
#include "int_to_string.h"

string leastRecentlyUsed(vector<int> pages, int framesNum, int requestsNum) {
	vector<int> frames(framesNum);		// simulates frames
	vector<int> timerInFrames(framesNum, 0);			// initiate all timers to 0		
	int index = 0;		// index of frames
	int pageFault = 0;		// record how many page faults occur
	int frameUsedTime = framesNum;
	int timer = 0;
	string output = "LRU\n";

	if (requestsNum > 0) {
		// if there is page request
		for (int i = 0; i < requestsNum; i++) {
			int currentRequestingPage = pages.at(i);
			if (find(frames, currentRequestingPage)) {
				// if current requesting page is not in the frames
				if (frameUsedTime == 0) {
					// only get here when there is no free frame
					int index = findMinIndex(timerInFrames, framesNum);		// index points to the frame with smallest timer
					int replacingPage = frames.at(index);		// get the page number that is getting replaced
					frames.at(index) = currentRequestingPage;
					pageFault++;
					timerInFrames.at(index) = timer;
					output += ("Page " + int_to_string(replacingPage) + " unloaded from Frame " + int_to_string(index) + ", Page " + int_to_string(currentRequestingPage) + " loaded into Frame " + int_to_string(index) + "\n");
				}
				else {
					frames.at(index) = currentRequestingPage;
					pageFault++;
					timerInFrames.at(index) = timer;
					output += ("Page " + int_to_string(currentRequestingPage) + " loaded into Frame " + int_to_string(index) + "\n");
					index++;
					frameUsedTime--;
				}

			}
			else {
				// else if current requesting page is already in one of the frames
				for (int j = 0; j < framesNum; j++) {
					if (frames.at(j) == currentRequestingPage) {
						timerInFrames.at(j) = timer;
						output += ("Page " + int_to_string(currentRequestingPage) + " already in Frame " + int_to_string(j) + "\n");
						break;
					}
				}
			}
			timer++;
		}
	}
	output += (int_to_string(pageFault) + " page faults\n");

	return output;
}