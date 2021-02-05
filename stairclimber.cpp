/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : John Schneiderhan
 * Date        : September 29, 2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector<vector<int>> container;
vector<int> steps;
int stairCount = 0;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
	stairCount = num_stairs;

	if(num_stairs <= 0){
		container.push_back(steps);
	}
	if(num_stairs >= 1){
		steps.push_back(1);
		get_ways(num_stairs - 1);
		steps.pop_back();
	}
	if(num_stairs >= 2){
		steps.push_back(2);
		get_ways(num_stairs - 2);
		steps.pop_back();
	}
	if(num_stairs >= 3){
		steps.push_back(3);
		get_ways(num_stairs - 3);
		steps.pop_back();
	}

	return container;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	int width = 0;
	int temp = ways.size();
	while(temp >= 1){
		temp /= 10;
		width++;
	}
	if(ways.size() > 1)
		cout << ways.size() << " ways to climb " << ways[0].size() << " stairs." << endl;
	else
		cout << ways.size() << " way to climb " << ways[0].size() << " stair." << endl;
	for(unsigned int i = 0; i < ways.size(); i++){
		cout << setw(width) << i + 1 << ". [";
		for(unsigned int k = 0; k < ways[i].size(); k++){
			cout << ways[i][k];
			if(k != ways[i].size() - 1){
				cout << ", ";
			}
		}
		cout << "]" << endl;
	}
}

int main(int argc, char * const argv[]) {
	istringstream iss;
	int stair;

	if(argc != 2){
		cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
		return 1;
	}
	iss.str(argv[1]);
	if(!(iss >> stair)){
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	if(stair <= 0){
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	else{
		display_ways(get_ways(stair));
	}
}
