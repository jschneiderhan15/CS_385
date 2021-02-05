/*
 * Name		  : sqrt.cpp
 * Author 	  : John Schneiderhan
 * Version 	  : 1.0
 * Date		  : September 2, 2020
 * Description: Computes the square root of a number.
 * Pledge	  : I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <iostream>
#include <limits>
#include <iomanip>
#include <sstream>

using namespace std;

/**
 * Returns the square root of a number.
 */
double sqrt(double num, double epsilon) {
	double nextGuess, lastGuess;
	if(num < 0){
		return numeric_limits<double>::quiet_NaN();
		}
	else if(num == 0 || num == 1){
		return num;
	}
	lastGuess = num;
	nextGuess = (lastGuess + (num / lastGuess))/ 2;
		while((abs(lastGuess - nextGuess) > epsilon)) {
			lastGuess = nextGuess;
			nextGuess = (lastGuess + (num / lastGuess)) / 2;
		}
	return nextGuess;
}

int main(int argc, char *argv[]){
	double num, eps;
	istringstream iss;

	if(argc > 3 || argc < 2){
			cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
			return 1;
	}

	if(argc == 2){
		iss.str(argv[1]);
		if(!(iss >> num)){
			cerr << "Error: Value argument must be a double." << endl;
			return 1;
		}
		cout  << fixed << setprecision(8) << sqrt(num, 1e-7) << endl;
		return 0;
	}

	iss.clear();

	if(argc == 3){
		iss.str(argv[1]);
		if(!(iss >> num)){
			cerr << "Error: Value argument must be a double." << endl;
			return 1;
		}

		iss.clear();
		iss.str(argv[2]);

		if(!(iss >> eps)){
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}

		if(eps <= 0){
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}
		cout << fixed << setprecision(8) << sqrt(num, eps) << endl;
		return 0;
	}


}





