#include <vector>
#include <string>
using namespace std;

#include "firstInFirstOut.h"
#include "find.h"
#include "int_to_string.h"

string firstInFirstOut(vector<int> pages, int framesNum, int requestsNum) {
	vector<int> frames(framesNum);		// simulate frames
	int index = 0;			// the index of frames
	string output = "FIFO\n";		// to store the result string
	int pageFault = 0;		// record how many page faults occurs

	if (requestsNum > 0) {
		// if there is page request
		for (int i = 0; i < requestsNum; i++) {
			int currentRequestingPage = pages.at(i);
			if (find(frames, currentRequestingPage)) {
				// if current requesting page is not in the frames
				if (i > framesNum) {
					// only get here after the frames are all used for the first time
					output += ("Page " + int_to_string(frames.at(index)) + " unloaded from Frame " + int_to_string(index) + ", ");
				}
				frames.at(index) = currentRequestingPage;		// store the new page number in the pointing frame and replace the original page
				output += ("Page " + int_to_string(currentRequestingPage) + " loaded into Frame " + int_to_string(index) + "\n");
				pageFault++;
				index++;
				if (index == framesNum) {
					// if it reaches the end of the frames
					index = 0;		// point back to the first frame
				}
			}
			else {
				// else if current reqeusting page is already in one of the frames
				for (int j = 0; j < framesNum; j++) {
					if (frames.at(j) == currentRequestingPage) {
						output += ("Page " + int_to_string(currentRequestingPage) + " already in Frame " + int_to_string(j) + "\n");
						break;
					}
				}
			}
		}
	}
	output += int_to_string(pageFault) + " page faults\n";

	return output;
}