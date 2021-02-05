/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : John Schneiderhan and Aleks Sekulovski
 * Version     : 1.0
 * Date        : October 27, 2020
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <string>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);


/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
	long inv = 0;
		for (int i = 0; i < length; i++) {
			for (int j =i + 1; j < length; j++) {
				if (array[i] > array[j]) {
					inv++;
				}
			}
		}
	return inv;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    int* scratch = new int[length];
    long counter = mergesort(array, scratch, 0, length - 1);
    delete [] scratch;
    return counter;
}

static long mergesort(int array[], int scratch[], int low, int high) {
	long count = 0;
	if(low < high){
		int mid = low + (high - low) / 2;
		count += mergesort(array, scratch, low, mid);
		count += mergesort(array, scratch, mid + 1, high);
		long L = low;
		long H = mid + 1;
		for(int k = low; k <= high; k++){
			if(L <= mid && (H > high || array[L] <= array[H])){
				scratch[k] = array[L];
				L++;
			}
			else{
				scratch[k] = array[H];
				H++;
				count += mid - L + 1;
			}
		}
		for(int i = low; i <= high; i++){
			array[i] = scratch[i];
		}
	}
	return count;
}

int main(int argc, char *argv[]) {
	if (argc > 2) {
			cerr << "Usage: " << argv[0] << " [slow]" << endl;
			return 1;
	}

	string method;

	if (argc == 2) {
		istringstream iss;
		iss.str(argv[1]);
		iss >> method;
		iss.clear();
		if(method.compare("slow") != 0){
				cerr << "Error: Unrecognized option '" + method + "'." << endl;
				return 1;
		}
	}


	cout << "Enter sequence of integers, each followed by a space: " << flush;

	istringstream iss;
	int value, index = 0;
	vector<int> values;
	string str;
	str.reserve(11);
	char c;
	while (true) {
		c = getchar();
		const bool eoln = c == '\r' || c == '\n';
		if (isspace(c) || eoln) {
			if (str.length() > 0) {
				iss.str(str);
				if (iss >> value) {
					values.push_back(value);
	               } else {
	               	cerr << "Error: Non-integer value '" << str
	               			<< "' received at index " << index << "." << endl;
	               	return 1;
                }
				iss.clear();
				++index;
			}
			if (eoln) {
				break;
			}
			str.clear();
		} else {
			str += c;
		}
	}
	int length = values.size();

	if(length == 0){
		cerr << "Error: Sequence of integers not received." << endl;
		return 1;
	}
	cout << "Number of inversions: ";
	if (method == "slow") {
		cout << count_inversions_slow(&values[0],  length);
		return 0;
	}
	else{
		cout << count_inversions_fast(&values[0], length);
	}

	return 0;
}
