#include <iostream>
#include <string>
#include <vector>		// vector<>
#include <queue>		// queue<>
#include <iomanip>		// setprecision()		setw()		right
#include <sstream>		// sstream
#include <fstream>		// ofstream		ifstream
#include <algorithm>
using namespace std;

// vector::find()
bool find(vector<int> v, int target) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
		if (*it == target) {
			return false;		// return false when found
		}
	}

	return true;		// if not found, return true
}

// string::to_string(int)
string int_to_string(int num) {
	stringstream ss;
	string output;

	ss << num;
	ss >> output;

	return output;
}

string prNoPremp(vector<vector<int> > processes, int n) {
	vector<int> burstTime;			// store CPU burst time for each process
	vector<int> waitingQueue;		// simulate waiting queue
	vector<int> waitingTime;		// waiting time for each process
	vector<int> priorities;			// priorities 
	vector<int> eachArrivalTime;		// arrival time for each process
	queue<int> arrivalOrder;		// store process numbers for arriving processes later
	queue<int> priorityLater;		// priorities for incoming processes
	queue<int> arrivalTime;			// store arrival time for each incoming process
	queue<int> burstTimeLater;		// store burst time for incoming processes
	int timeCount = 0;				// timer
	string output = "PR_noPREMP\n";

	for (int i = 0; i < n; i++) {
		vector<int> currentProcess = processes.at(i);		// get current process

		if (currentProcess.at(1) == 0) {
			// if arrival time is zero
			waitingQueue.push_back(currentProcess.at(0));		// push its process number into waiting queue
			//burstTime.push_back(currentProcess.at(2));			// push its burst time
			priorities.push_back(currentProcess.at(3));		// push its priority 
		}
		else {
			// if arrival time is later
			arrivalOrder.push(currentProcess.at(0));		// push its process number into incoming queue
			arrivalTime.push(currentProcess.at(1));		// push its arrival time
			priorityLater.push(currentProcess.at(3));		// push its priority
		}
		burstTime.push_back(currentProcess.at(2));			// push its burst time
		eachArrivalTime.push_back(currentProcess.at(1));
	}

	if (waitingQueue.size() > 1) {
		// if there are more than one process in the queue
		int minIndex;		// indicates index for smallest priority number

		// selection sort priorities, waitingQueue
		for (int i = 0; i < n - 1; i++) {
			minIndex = i;

			for (int j = i + 1; j < n; j++) {
				if (priorities.at(j) < priorities.at(minIndex)) {
					// if found a smaller priority number
					minIndex = j;		// update minIndex to the new found index
				}
				else if (priorities.at(j) == priorities.at(minIndex)) {
					// else if both have same priorities
					if (waitingQueue.at(j) < waitingQueue.at(minIndex)) {
						// if found smaller process number
						minIndex = j;
					}
				}
			}

			int temp = priorities.at(minIndex);
			priorities.at(minIndex) = priorities.at(i);
			priorities.at(i) = temp;
			temp = waitingQueue.at(minIndex);
			waitingQueue.at(minIndex) = waitingQueue.at(i);
			waitingQueue.at(i) = temp;
		}
	}

	vector<int> repeated;

	while (!waitingQueue.empty() || !arrivalOrder.empty()) {
		// while something is waiting and something is incomining
		if (waitingQueue.empty() && !arrivalOrder.empty()) {
			// if nothing is waiting but still something will come later
			while (timeCount == arrivalTime.front()) {
				// while new arrival
				int nextArrivalNum = arrivalOrder.front();		// get the new arrival's process number
				int nextArrivalPriority = priorityLater.front();		// get the new arrival's priority number
				waitingQueue.push_back(nextArrivalNum);
				priorities.push_back(nextArrivalPriority);
				burstTime.at(nextArrivalNum - 1)--;
				eachArrivalTime.at(nextArrivalNum - 1)++;
				if (burstTime.at(nextArrivalNum - 1) == 0) {
					// if this process is done
					waitingTime.push_back(timeCount - eachArrivalTime.at(nextArrivalNum - 1));
				}

				stringstream ss;
				ss << setw(3) << left << int_to_string(timeCount) << setw(5) << right << int_to_string(nextArrivalNum) << "\n";
				output += ss.str();
				repeated.push_back(nextArrivalNum);

				arrivalOrder.pop();
				if (arrivalOrder.empty()) {
					// if no more incoming process
					break;		// stop checking
				}
				priorityLater.pop();
				arrivalTime.pop();
			}
			timeCount++;
		}
		else {
			int currentIndex = waitingQueue.front();		// current process's process number 

			waitingTime.push_back(timeCount - eachArrivalTime.at(currentIndex - 1));
			if (find(repeated, currentIndex)) {
				// if this process numebr is not already in the output
				stringstream ss;
				ss << setw(3) << left << int_to_string(timeCount) << setw(5) << right << int_to_string(currentIndex) << "\n";
				output += ss.str();
			}

			for (int i = 0; i < burstTime.at(currentIndex - 1); i++) {
				// process its burst time
				if (!arrivalOrder.empty()) {
					// if there is still more incomign process
					while (timeCount == arrivalTime.front()) {
						// while we catch a new arrival
						int nextArrivalNum = arrivalOrder.front();		// get the new arrival's process number
						int nextArrivalBurstTime = burstTime.at(nextArrivalNum - 1);	// get the new arrival's burst time
						int nextArrivalPriority = priorityLater.front();		// get the new arrival's priority number

						if (waitingQueue.size() == 1) {
							// if there is only one process in the queue
							priorities.push_back(nextArrivalPriority);		// add new arrival into the queue
							waitingQueue.push_back(nextArrivalNum);
						}
						else {
							// else if there are more than one process in the queue
							int j;
							for (j = 1; j < priorities.size(); j++) {
								if (nextArrivalPriority < priorities.at(j)) {
									// if new arrival's priority number is lower
									priorities.insert(priorities.begin() + j, nextArrivalPriority);		// insert it
									waitingQueue.insert(waitingQueue.begin() + j, nextArrivalNum);
									break;		// finish insertion
								}
								else if (nextArrivalPriority == priorities.at(j)) {
									// else if new arrival's priority numbner is equal
									if (nextArrivalNum < waitingQueue.at(j)) {
										// if new arrival has smaller process number
										priorities.insert(priorities.begin() + j, nextArrivalPriority);		// insert it
										waitingQueue.insert(waitingQueue.begin() + j, nextArrivalNum);
										break;		// finish insertion
									}
									else {
										// if new arrival has bigger process number
										if (j < priorities.size()) {
											// this is not the last element in the list
											priorities.insert(priorities.begin() + j + 1, nextArrivalPriority);		// insert it
											waitingQueue.insert(waitingQueue.begin() + j + 1, nextArrivalNum);
											break;		// finish insertion
										}
									}
								}
							}
							if (j == priorities.size()) {
								// if it has the highest priority number than others
								priorities.push_back(nextArrivalPriority);
								waitingQueue.push_back(nextArrivalNum);	// add it at the end of the queue
							}
						}

						arrivalOrder.pop();
						if (arrivalOrder.empty()) {
							// if no more incoming process
							break;		// stop checking
						}
						priorityLater.pop();
						arrivalTime.pop();
					}
				}
				timeCount++;		// tick 1 unit
			}

			waitingQueue.erase(waitingQueue.begin());			// one process done
			priorities.erase(priorities.begin());
		}
	}

	double totalWaitingTime = 0;
	for (vector<int>::iterator it = waitingTime.begin(); it != waitingTime.end(); ++it) {
		totalWaitingTime += *it;
	}

	totalWaitingTime /= n;		// get average waiting time

	stringstream ss;
	ss << fixed << setprecision(2) << totalWaitingTime;		// convert it to string with precision(2)
	output += "AVG Waiting Time: " + ss.str() + "\n";

	return output;
}

string prWithPremp(vector<vector<int> > processes, int n) {
	vector<int> burstTime;			// store CPU burst time for each process
	vector<int> waitingQueue;		// simulate waiting queue
	vector<int> waitingTime;		// waiting time for each process
	vector<int> priorities;			// priorities 
	vector<int> eachArrivalTime;		// arrival time for each process
	queue<int> arrivalOrder;		// store process numbers for arriving processes later
	queue<int> priorityLater;		// priorities for incoming processes
	queue<int> arrivalTime;			// store arrival time for each incoming process
	queue<int> burstTimeLater;		// store burst time for incoming processes
	int timeCount = 0;				// timer
	string output = "PR_withPREMP\n";

	for (int i = 0; i < n; i++) {
		vector<int> currentProcess = processes.at(i);		// get current process

		if (currentProcess.at(1) == 0) {
			// if arrival time is zero
			waitingQueue.push_back(currentProcess.at(0));		// push its process number into waiting queue
			//burstTime.push_back(currentProcess.at(2));			// push its burst time
			priorities.push_back(currentProcess.at(3));		// push its priority 
		}
		else {
			// if arrival time is later
			arrivalOrder.push(currentProcess.at(0));		// push its process number into incoming queue
			arrivalTime.push(currentProcess.at(1));		// push its arrival time
			priorityLater.push(currentProcess.at(3));		// push its priority
		}
		burstTime.push_back(currentProcess.at(2));			// push its burst time
		eachArrivalTime.push_back(currentProcess.at(1));
	}

	vector<int> burstTimeCopy = burstTime;		// make a copy of burst times
	vector<int> arrivalTimeCopy = eachArrivalTime;	// make a copy of arrival times

	if (waitingQueue.size() > 1) {
		// if there are more than one process in the queue
		int minIndex;		// indicates index for smallest priority number

		// selection sort priorities, waitingQueue
		for (int i = 0; i < n - 1; i++) {
			minIndex = i;

			for (int j = i + 1; j < n; j++) {
				if (priorities.at(j) < priorities.at(minIndex)) {
					// if found a smaller priority number
					minIndex = j;		// update minIndex to the new found index
				}
				else if (priorities.at(j) == priorities.at(minIndex)) {
					// else if both have same priorities
					if (waitingQueue.at(j) < waitingQueue.at(minIndex)) {
						// if found smaller process number
						minIndex = j;
					}
				}
			}

			int temp = priorities.at(minIndex);
			priorities.at(minIndex) = priorities.at(i);
			priorities.at(i) = temp;
			temp = waitingQueue.at(minIndex);
			waitingQueue.at(minIndex) = waitingQueue.at(i);
			waitingQueue.at(i) = temp;
		}
	}

	vector<int> repeated;

	while (!waitingQueue.empty() || !arrivalOrder.empty()) {
		// while something is waiting or something is incomining
		stringstream ss;
		int nextProcessNumber;
		if (!waitingQueue.empty()) {
			nextProcessNumber = waitingQueue.front();
		}
		else {
			nextProcessNumber = arrivalOrder.front();
		}
		int outputLength = output.length();
		int lastTimeCount = timeCount;
		if (find(repeated, nextProcessNumber)) {
			ss << setw(3) << left << int_to_string(timeCount) << setw(5) << right << int_to_string(nextProcessNumber) << "\n";
			output += ss.str();
		}
		repeated.clear();

		if (waitingQueue.empty() && !arrivalOrder.empty()) {
			// if nothing is waiting but still something will come later
			while (timeCount == arrivalTime.front()) {
				// while new arrival
				int nextArrivalNum = arrivalOrder.front();		// get the new arrival's process number
				int nextArrivalPriority = priorityLater.front();		// get the new arrival's priority number
				waitingQueue.push_back(nextArrivalNum);
				priorities.push_back(nextArrivalPriority);
				burstTime.at(nextArrivalNum - 1)--;
				eachArrivalTime.at(nextArrivalNum - 1)++;
				if (burstTime.at(nextArrivalNum - 1) == 0) {
					// if this process is done
					waitingTime.push_back(timeCount - eachArrivalTime.at(nextArrivalNum - 1));
				}

				repeated.push_back(nextArrivalNum);

				arrivalOrder.pop();
				if (arrivalOrder.empty()) {
					// if no more incoming process
					break;		// stop checking
				}
				priorityLater.pop();
				arrivalTime.pop();
			}
			timeCount++;
		}
		else {
			int currentIndex = waitingQueue.front();		// current process's process number 

			bool newPriority = false;

			int correctBurstTime = burstTime.at(currentIndex - 1);

			for (int i = 0; i < correctBurstTime; i++) {
				// process its burst time
				if (!arrivalOrder.empty()) {
					// if there is still more incomign process
					while (timeCount == arrivalTime.front()) {
						// while we catch a new arrival
						int nextArrivalNum = arrivalOrder.front();		// get the new arrival's process number
						int nextArrivalBurstTime = burstTime.at(nextArrivalNum - 1);	// get the new arrival's burst time
						int nextArrivalPriority = priorityLater.front();		// get the new arrival's priority number

						if (nextArrivalPriority < priorities.front()) {
							// if new arrival's priority number is lower than current priority
							waitingQueue.insert(waitingQueue.begin(), nextArrivalNum);		// put new arrival into the front of the queue
							priorities.insert(priorities.begin(), nextArrivalPriority);
							currentIndex = waitingQueue.front();		// now point to new priority
							newPriority = true;

							repeated.clear();
							if (lastTimeCount == timeCount) {
								output = output.substr(0, outputLength);		// delete the last line
							}

							stringstream ss;
							ss << setw(3) << left << int_to_string(timeCount) << setw(5) << right << int_to_string(nextArrivalNum) << "\n";
							output += ss.str();

							repeated.push_back(nextArrivalNum);
						}
						else {
							// if new arrival has higher priority number than the current priority
							if (waitingQueue.size() == 1) {
								// if there is only one process in the queue
								priorities.push_back(nextArrivalPriority);		// add new arrival into the queue
								waitingQueue.push_back(nextArrivalNum);
							}
							else {
								// else if there are more than one process in the queue
								int j;
								for (j = 1; j < priorities.size(); j++) {
									if (nextArrivalPriority < priorities.at(j)) {
										// if new arrival's priority number is lower
										priorities.insert(priorities.begin() + j, nextArrivalPriority);		// insert it
										waitingQueue.insert(waitingQueue.begin() + j, nextArrivalNum);
										break;		// finish insertion
									}
									else if (nextArrivalPriority == priorities.at(j)) {
										// else if new arrival's priority numbner is equal
										if (nextArrivalNum < waitingQueue.at(j)) {
											// if new arrival has smaller process number
											priorities.insert(priorities.begin() + j, nextArrivalPriority);		// insert it
											waitingQueue.insert(waitingQueue.begin() + j, nextArrivalNum);
											break;		// finish insertion
										}
										else {
											// if new arrival has bigger process number
											if (j < priorities.size()) {
												// this is not the last element in the list
												priorities.insert(priorities.begin() + j + 1, nextArrivalPriority);		// insert it
												waitingQueue.insert(waitingQueue.begin() + j + 1, nextArrivalNum);
												break;		// finish insertion
											}
										}
									}
								}
								if (j == priorities.size()) {
									// if it has the highest priority number than others
									priorities.push_back(nextArrivalPriority);
									waitingQueue.push_back(nextArrivalNum);	// add it at the end of the queue
								}
							}
						}

						arrivalOrder.pop();
						if (arrivalOrder.empty()) {
							// if no more incoming process
							break;		// stop checking
						}
						priorityLater.pop();
						arrivalTime.pop();
					}
				}
				burstTime.at(currentIndex - 1)--;
				timeCount++;		// tick 1 unit

				if (newPriority) {
					// if current priority was replaced
					break;		// exit for loop
				}
			}

			if (!newPriority) {
				waitingTime.push_back(timeCount - arrivalTimeCopy.at(waitingQueue.front() - 1) - burstTimeCopy.at(waitingQueue.front() - 1));		// waiting time = finish time - arrival time - burst time
				waitingQueue.erase(waitingQueue.begin());			// one process done
				priorities.erase(priorities.begin());
			}
		}
	}

	double totalWaitingTime = 0;
	for (vector<int>::iterator it = waitingTime.begin(); it != waitingTime.end(); ++it) {
		totalWaitingTime += *it;
	}

	totalWaitingTime /= n;		// get average waiting time

	stringstream ss;
	ss << fixed << setprecision(2) << totalWaitingTime;		// convert it to string with precision(2)
	output += "AVG Waiting Time: " + ss.str() + "\n";

	return output;
}

string roundRobin(vector<vector<int> > processes, int timeQuantum, int n) {
	vector<int> remainingTime;	// keep track of remaning burst time for each process
	vector<int> waitingTime;		// waiting time for each processs
	queue<int> arrivalTime;
	queue<int> arrivalOrder;
	queue<int> waitingQueue;	// goes by process numbers
	int timeCount = 0;		// timer
	string output = "RR " + int_to_string(timeQuantum) + "\n";

	for (int i = 0; i < n; i++) {
		vector<int> currentProcess = processes.at(i);			// get current process
		remainingTime.push_back(currentProcess.at(2));		// push its CPU burst time into remaining time
		waitingTime.push_back(0);		// initialize waiting time for all processes to zero

		if (currentProcess.at(1) == 0) {
			// if arrival time is 0
			waitingQueue.push(i);		// add it to the waiting queue
		}
		else {
			// esle if arriving later 
			arrivalOrder.push(i);		// push its process number
			arrivalTime.push(currentProcess.at(1));		// push its arrival time
		}
	}

	while (!waitingQueue.empty() || !arrivalOrder.empty()) {
		// while something is waiting or something is incoming
		int currentIndex;		// store current process's process number
		int i = 0;

		if (!waitingQueue.empty()) {
			// if there is something waiting 
			currentIndex = waitingQueue.front();		// get whose term is next

			if (remainingTime.at(currentIndex) < timeQuantum) {
				// if remaning time is less than one time quantum
				i = timeQuantum - remainingTime.at(currentIndex);
			}

			stringstream ss;
			ss << setw(3) << left << int_to_string(timeCount) << setw(5) << right << int_to_string(currentIndex + 1) << "\n";
			output += ss.str();

			for (; i < timeQuantum; i++) {
				remainingTime.at(currentIndex)--;		// process it by 1 time unit
				timeCount++;		// tick 1 time unit

				if (!arrivalTime.empty()) {
					while (arrivalTime.front() == timeCount) {
						// if new arrival happens
						waitingQueue.push(arrivalOrder.front());		// add it to the end of the waiting queue
						arrivalOrder.pop();		// remove it from arriving processes
						arrivalTime.pop();

						if (arrivalOrder.empty()) {
							// if no more process is incoming
							break;	// stop checking for incoming processes
						}
					}
				}
			}

			if (remainingTime.at(currentIndex) > 0) {
				// if current process is not done
				waitingQueue.push(currentIndex);		// add it to the end of the waiting queue	
			}
			else {
				// else if current process is done
				waitingTime.at(currentIndex) = timeCount - processes.at(currentIndex).at(2) - processes.at(currentIndex).at(1);			// waiting time = current time - arrival time - burst time
			}

			waitingQueue.pop();		// remove the first item in the waiting queue
		}
		else {
			// nothing is waiting but soemthing is incoming later
			timeCount++;
		}
	}

	double totalWaitingTime = 0;
	for (vector<int>::iterator it = waitingTime.begin(); it != waitingTime.end(); ++it) {
		totalWaitingTime += *it;		// get sum of each waiting time
	}

	totalWaitingTime /= n;
	stringstream ss;
	ss << fixed << setprecision(2) << totalWaitingTime;
	output += "AVG Waiting Time: " + ss.str() + "\n";

	return output;
}

string shortestJobFirst(vector<vector<int> > processes, int n) {
	vector<int> burstTime;			// store CPU burst time for each process
	vector<int> waitingQueue;		// simulate waiting queue
	vector<int> arrivalTime;		// store arrival time for each process
	vector<int> waitingTime;		// waiting time for each process
	queue<int> arrivalOrder;		// store process numbers for arriving processes later
	queue<int> arrivalTimeLater;
	queue<int> burstTimeLater;		// store burst time for incoming processes
	int timeCount = 0;				// timer
	string output = "SJF\n";		// result

	for (int i = 0; i < n; i++) {
		vector<int> currentProcess = processes.at(i);

		if (currentProcess.at(1) == 0) {
			// if arrival time is zero
			waitingQueue.push_back(currentProcess.at(0));	// push its process number into waiting queue
			burstTime.push_back(currentProcess.at(2));			// store burst time for each process

		}
		else {
			// else if arriving later
			arrivalOrder.push(currentProcess.at(0));	// push its process number
			arrivalTimeLater.push(currentProcess.at(1));		// store arrival time for incoming processes
			burstTimeLater.push(currentProcess.at(2));		// store burst time for incoming processes
		}
		arrivalTime.push_back(currentProcess.at(1));		// store arrival time for each process
	}

	if (waitingQueue.size() > 1) {
		// if there are more than one process in the queue
		int minIndex;		// indecates index for smallest

		// selection sort burstTime and waitingQueue
		for (int i = 0; i < n - 1; i++) {
			minIndex = i;

			for (int j = i + 1; j < n; j++) {
				if (burstTime.at(j) < burstTime.at(minIndex)) {
					// if found a smaller element
					minIndex = j;		// update minIndex to the new found smallest
				}
				else if (burstTime.at(j) == burstTime.at(minIndex)) {
					// if elements are equal
					if (arrivalTime.at(j) < arrivalTime.at(minIndex)) {
						// if arrival time is earlier
						minIndex = j;
					}
					else if (arrivalTime.at(j) == arrivalTime.at(minIndex)) {
						// if they both arrive at the same time
						if (waitingQueue.at(j) < waitingQueue.at(minIndex)) {
							// choose the smaller process number
							minIndex = j;
						}
					}
				}
			}

			// swap two values in burstTime and waitingQueue
			int temp = burstTime.at(minIndex);
			burstTime.at(minIndex) = burstTime.at(i);
			burstTime.at(i) = temp;
			temp = waitingQueue.at(minIndex);
			waitingQueue.at(minIndex) = waitingQueue.at(i);
			waitingQueue.at(i) = temp;
		}
	}

	while (!waitingQueue.empty() || !arrivalOrder.empty()) {
		// while there is something waiting or something is incoming
		int currentIndex;		// store current process's process number
		currentIndex = waitingQueue.front() - 1;		// get whose term is next

		waitingTime.push_back(timeCount - arrivalTime.at(currentIndex));		// waiting time = current time - arrival time

		stringstream ss;
		ss << setw(3) << left << int_to_string(timeCount) << setw(5) << right << int_to_string(waitingQueue.front()) << "\n";
		output += ss.str();

		for (int i = 0; i < burstTime.front(); i++) {
			// process its burst time
			if (!arrivalOrder.empty()) {
				// if there is still more incoming process
				while (timeCount == arrivalTimeLater.front()) {
					// while we have new arrivals
					int nextArrivalNum = arrivalOrder.front();		// get the new arrival's process number
					int nextArrivalBurstTime = burstTimeLater.front();		// get the new arrival's burst time

					// insert it into the queue
					if (waitingQueue.size() == 1) {
						// if there is only one process in the queue
						burstTime.push_back(nextArrivalBurstTime);		// add it after the only process
						waitingQueue.push_back(nextArrivalNum);		// add it after the only process in the queue
					}
					else {
						// else if there are more than one process in the queue
						int j;
						for (j = 1; j < burstTime.size(); j++) {
							if (nextArrivalBurstTime < burstTime.at(j)) {
								// if new arrival's burst time is smaller
								burstTime.insert(burstTime.begin() + j, nextArrivalBurstTime);		// insert it
								waitingQueue.insert(waitingQueue.begin() + j, nextArrivalNum);		// insert its process number into waiting queue
								break;	// finish insertion
							}
							else if (nextArrivalBurstTime == burstTime.at(j)) {
								// if a new arrival has the same burst time
								if (arrivalTimeLater.front() < arrivalTime.at(waitingQueue.at(j)) - 1) {
									// if new arrival has earlier arrival time
									burstTime.insert(burstTime.begin() + j, nextArrivalBurstTime);		// insert it
									waitingQueue.insert(waitingQueue.begin() + j, nextArrivalNum);		// insert its process number into waiting queue
									break;	// finish insertion
								}
								else if (arrivalTimeLater.front() == arrivalTime.at(waitingQueue.at(j)) - 1) {
									// else if they have the same arrival time and burst time
									if (currentIndex < waitingQueue.at(j)) {
										// if new arriva has smaller process number
										burstTime.insert(burstTime.begin() + j, nextArrivalBurstTime);		// insert it
										waitingQueue.insert(waitingQueue.begin() + j, nextArrivalNum);		// insert its process number into waiting queue
										break;	// finish insertion
									}
									else {
										if (j < burstTime.size()) {
											// if this is not the last element in the list
											burstTime.insert(burstTime.begin() + j + 1, nextArrivalBurstTime);		// insert it
											waitingQueue.insert(waitingQueue.begin() + j + 1, nextArrivalNum);		// insert its process number into waiting queue
											break;	// finish insertion
										}
									}
								}
							}
						}
						if (j == burstTime.size()) {
							// if new arrival's burst time is greater than all others in the queue
							burstTime.push_back(nextArrivalBurstTime);
							waitingQueue.push_back(nextArrivalNum);		// add it at the end of the queue
						}
					}

					arrivalOrder.pop();
					if (arrivalOrder.empty()) {
						// if no more incoming process
						break;		// stop chekcing for incomings
					}
					burstTimeLater.pop();
					arrivalTimeLater.pop();
				}
			}

			timeCount++;		// tick the timer by 1 unit
		}

		waitingQueue.erase(waitingQueue.begin());		// pop the first in the queue
		burstTime.erase(burstTime.begin());
	}

	double totalWaitingTime = 0;
	for (vector<int>::iterator it = waitingTime.begin(); it != waitingTime.end(); ++it) {
		totalWaitingTime += *it;
	}

	totalWaitingTime /= n;
	stringstream ss;
	ss << fixed << setprecision(2) << totalWaitingTime;		// convert it to string with precision(2)
	output += "AVG Waiting Time: " + ss.str() + "\n";

	return output;
}

void writeFile(string fileName, string content) {
	ofstream fout(fileName.c_str());		// open file for writing

	if (fout.is_open()) {
		// if file is open sucessfully
		fout << content;	// write content to the file
		fout.close();		// close file when finish
	}
	else {
		// if file cannot be opened
		cout << "File " << fileName << " cannot be opened!\n";
	}
	return;
}

vector<vector<int> > readFile(string fileName, int& n, int& timeQuantum, string& method) {
	vector<vector<int> > processes;
	vector<int> process;
	string oneLine;

	ifstream fin(fileName.c_str());		// open file for reading
	if (fin.is_open()) {
		// if file is opened sucessfully
		int lineNumber = 0;		// indicates the current line number

		while (getline(fin, oneLine)) {
			// keep reading until reach the end
			stringstream ss;
			ss << oneLine;

			if (lineNumber == 0) {
				// reading the first line which contains the method name and potentially time quantum
				string temp;	// to hold each word of the line
				ss >> temp;		// temp now contains the method name
				method = temp;		// store the method name

				if (temp == "RR") {
					// if method is RR
					ss >> temp;		// get the next word which is the time quantum
					stringstream tempInt(temp);
					tempInt >> timeQuantum;		// convert it from string to integer
				}
				else {
					// else if it is other method beside RR
					timeQuantum = 0;		// time quantum is zero
				}
			}
			else if (lineNumber == 1) {
				// reading the second line which contains the number of processes
				stringstream tempInt(oneLine);
				tempInt >> n;		// convert it from string to integer
			}
			else {
				// reading the lines after the second line
				while (!ss.eof()) {		// expected to loop 4 times
					// while it is not the end of the line
					int tempNum;
					ss >> tempNum;		// conver the string to an integer
					process.push_back(tempNum);			// push it to the process
				}
				processes.push_back(process);
			}
			lineNumber++;		// finish reading one line
			process.clear();		// clear the vector
			ss.str("");		// clear the stringstream
		}
		fin.close();		// close the file after finish
	}
	else {
		// else if file cannot be opened
		cout << "File " << fileName << " cannot be opened!\n";
	}

	return processes;
}

int main() {
	vector<int> process;		// process number, arrival time, CPU burst time, priority
	vector<vector<int> > processes;			// a vector of processes
	string inputFileName = "input.txt";		// name for input file
	string outputFileName = "output.txt";		// name for output file
	string content;
	int n;			// number of processes
	int timeQuantum;	
	string method;		// to hold the method name
	
	processes = readFile(inputFileName, n, timeQuantum, method);		// reading input.txt

	if (method == "RR") {
		// use round robin
		content = roundRobin(processes, timeQuantum, n);
	}
	else if (method == "SJF") {
		// use shortest job first
		content = shortestJobFirst(processes, n);
	}
	else if (method == "PR_noPREMP"){
		// use priority without preemption
		content = prNoPremp(processes, n);
	}
	else if (method == "PR_withPREMP") {
		// use priority with preemption
		content = prWithPremp(processes, n);
	}
	else {
		// Invalid method
		cout << "Invalid Method!" << endl;
	}

	writeFile(outputFileName, content);			// writing output.txt
	cout << "Finish!\n";
}