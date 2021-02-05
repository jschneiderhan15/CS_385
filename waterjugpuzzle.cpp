/*
 * Name		  : waterjug.cpp
 * Author 	  : John Schneiderhan, Aleks Sekulovski
 * Version 	  : 1.0
 * Date		  : October 11, 2020
 * Description: Creates a water jug that prints out instructions to reach desired water levels.
 * Pledge	  : I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include <iterator>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

struct State{
	int a, b, c;
	string directions;
	State *parent;

	State(int _a, int _b, int _c, string _directions) :
		a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr}{}

	//String representation of state in tuple form.
	string to_String(){
		ostringstream oss;
		oss << directions << "(" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}

};

string bfs(State* stat, string d, State fin, State cap){
	queue<State*> cue;
	State* current;
	string plural;
	vector<State*> seen;

	int A_capacity = cap.a;
	int B_capacity = cap.b;
	int C_capacity = cap.c;

	cue.push(stat);

	while(!cue.empty()){
		current = cue.front();
		cue.pop();
		if(current->a == fin.a && current->b == fin.b && current->c == fin.c) {
			State* ref = current;
			string output = "";
			while (current->parent != NULL) {
				output.insert(0, current->to_String());
				output.insert(0, "\n");
				current = current->parent;
			}
			output.insert(0, current->to_String());
			cout << output << endl;
			delete ref;
			while(!cue.empty()){
					delete cue.front();
					cue.pop();
			}
			for(unsigned int i = 0; i < seen.size(); i++){
				delete seen[i];
			}
			return output;
		}

		bool see = false;
		for(unsigned int i = 0; i < seen.size(); i++){
			if(seen[i]->a == current->a && seen[i]->b == current->b){
				delete current;
				see = true;
				break;
			}
		}
		if(see)
			continue;

		seen.push_back(current);

		// C to A
		if (current->c != 0 && current->a <= A_capacity) {
			plural = "";
			int pour_amount = A_capacity - current->a;
			if (pour_amount > current->c) {
				pour_amount = current->c;
			}
			if (pour_amount > 1) {
				plural = "s";
			}

			State* C_to_A = new State(current->a + pour_amount, current->b, current->c - pour_amount, "Pour " + to_string(pour_amount) + " gallon" + plural +" from C to A. ");
			C_to_A->parent = current;
			cue.push(C_to_A);
		}

		// C to B
		if (current->c != 0 && current->b <= B_capacity) {
			plural = "";
			int pour_amount = B_capacity - current->b;
			if (pour_amount > current->c) {
				pour_amount = current->c;
			}
			if (pour_amount > 1) {
				plural = "s";
			}
			State* C_to_B = new State(current->a, current->b + pour_amount, current->c - pour_amount, "Pour " + to_string(pour_amount) + " gallon" + plural +" from C to B. ");
			C_to_B->parent = current;
			cue.push(C_to_B);
		}
		// B to A
		if (current->b != 0 && current->a <= A_capacity) {
			plural = "";
			int pour_amount = A_capacity - current->a;
			if (pour_amount > current->b) {
				pour_amount = current->b;
			}
			if (pour_amount > 1) {
				plural = "s";
			}

			State* B_to_A = new State(current->a+ pour_amount, current->b - pour_amount, current->c, "Pour " + to_string(pour_amount) + " gallon" + plural +" from B to A. ");
			B_to_A->parent = current;
			cue.push(B_to_A);
		}


		// A to B
		if (current->a != 0 && current->b <= B_capacity) {
			plural = "";
			int pour_amount = B_capacity - current->b;
			if (pour_amount > current->a) {
				pour_amount = current->a;
			}
			if (pour_amount > 1) {
				plural = "s";
			}

			State* A_to_B = new State(current->a- pour_amount, current->b + pour_amount, current->c , "Pour " + to_string(pour_amount) + " gallon" + plural +" from A to B. ");
			A_to_B->parent = current;
			cue.push(A_to_B);
		 }

		// B to C
		if (current->b != 0 && current->c <= C_capacity) {
			plural = "";
			int pour_amount = C_capacity - current->c;
			if (pour_amount > current->b) {
				pour_amount = current->b;
			}
			if (pour_amount >1) {
				plural = "s";
			}

			State* B_to_C = new State(current->a, current->b - pour_amount, current->c+ pour_amount, "Pour " + to_string(pour_amount) + " gallon" + plural +" from B to C. ");
			B_to_C->parent = current;
			cue.push(B_to_C);
		}

		// A to C
		if (current->a != 0 && current->c <= C_capacity) {
			plural = "";
			int pour_amount = C_capacity - current->c;
			if (pour_amount > current->a) {
				pour_amount = current->a;
			}
			if (pour_amount > 1){
				plural = "s";
			}
			State* A_to_C = new State(current->a - pour_amount, current->b, current->c + pour_amount, "Pour " + to_string(pour_amount) + " gallon" + plural +" from A to C. ");
			A_to_C->parent = current;
			cue.push(A_to_C);
		}
	}
	cout << "No solution." << endl;
	while(!cue.empty()){
		delete cue.front();
		cue.pop();
	}
	for(unsigned int i = 0; i < seen.size(); i++){
		delete seen[i];
	}
	return "No solution.";
}

int main(int argc, char * const argv[]) {
	istringstream iss;
	int num;
	//char letter;


	if(argc != 7){
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}


    vector<int> input;
    iss.str(argv[1]);
    int x = 1;
    while (iss >> num && x < 7)  {
    	iss >> num;
    	if (num < 0 || (x == 3 &&  num == 0)) {break;}
    	input.push_back(num);
    	iss.clear();
    	x++;
    	if (x < 7)	{
    		iss.str(argv[x]);
    	}
    }

    if (input.size() < 3) {
    		cerr << "Error: Invalid capacity '" << argv[x] << "' for jug " << char((int)'A' + input.size()) << ".";
				return 1;
    }

    if (input.size() < 6) {
    		cerr << "Error: Invalid goal '" << argv[x] << "' for jug " << char((int)'A' + (input.size() - 3)) << ".";
				return 1;
    }

	for(unsigned int i=0; i < input.size() - 3; i++) {
		if (input[i] < input[i+3]) {
			cerr << "Error: Goal cannot exceed capacity of jug " << char((int)'A' + i) << "." << endl;
			return 1;
		}
	}
	double sum = input[3] + input[4] + input[5];

	if (sum != input[2]) {
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}

	const State capacity(input[0], input[1], input[2], "");
	const State final(input[3], input[4], input[5], "");
	State* initial = new State(0, 0, input[2], "Initial state. ");

	bfs(initial, initial->directions, final, capacity);
	return 0;
	}



