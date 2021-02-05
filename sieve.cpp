/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : John Schneiderhan
 * Date        : September 14, 2020
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

/*
 * PrimesSieve class that initializes a sieve with an array True and False,
 * respective to each number and it's prime status.
 */
class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

/*
 * Constructor for the PrimesSieve class.
 * limit is the limit of numbers to go up to.
 */
PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

/*
 * Displays prime numbers, organized with a certain width and row size.
 */
void PrimesSieve::display_primes() const {
    //initializing max width of primes and primes per row
	const int max_prime_width = num_digits(max_prime_),
			  primes_per_row = 80 / (max_prime_width + 1);
	int tempPrimes = primes_per_row;
	//if there is only one line of primes, no space formatting is required
	if(count_num_primes() < primes_per_row){
		for(int i = 0; i <= limit_; i++){
			if(is_prime_[i]){
				if(i == max_prime_){
					cout << i;
				}
				else{
					cout << i << " ";
				}
			}
		}
	}
	//if there is more than one line, space formatting is required
	else{
		for(int i = 0; i <= limit_; i++){
			if(is_prime_[i]){
				//if the number is the last number in a line, no space is necessary afterwards
				if (i == max_prime_ || tempPrimes == 1){
					cout << setw(max_prime_width) << i;
				}
				else{
					cout << setw(max_prime_width) << i << " ";
				}
				tempPrimes--;
				//once primes in a row have been "used up", break and go to the next line
				if(tempPrimes == 0){
					cout << endl;
					tempPrimes = primes_per_row;
				}
			}
		}
	}
}

/*
 * Counts the number of primes up to the limit.
 */
int PrimesSieve::count_num_primes() const {
	int numPrimes = 0;
	//increment numPrime everytime a true is found in num_primes_
	for(int i = 0; i <= limit_; i++){
		if(is_prime_[i]){
			numPrimes++;
		}
	}
    return numPrimes;
}

/*
 * "Sieves" prime numbers through the sieve algorithm
 * given on the document.
 */
void PrimesSieve::sieve() {
	//first two numbers (base cases) are not prime
	is_prime_[0] = false;
	is_prime_[1] = false;
	//filling the entire array with true initially
	for(int i = 2; i <= limit_; i++){
		is_prime_[i] = true;
	}
	//sieve algorithm from requirements document
	for(int i = 2; i <= sqrt(limit_); i++){
		if(is_prime_[i]){
			for(int j = pow(i, 2); j <= limit_; j+= i){
				is_prime_[j] = false;
			}
		}
	}
	//looping back through is_prime_ to find the max prime
	for(int i = 2; i <= limit_; i++){
		if(is_prime_[i]){
			max_prime_ = i;
		}
	}
	//setting num_primes_
	num_primes_ = count_num_primes();
}

/*
 * Algorithm to calculate the number of digits in a single number.
 */
int PrimesSieve::num_digits(int num) {
	int tempNum = num;
	int digits = 0;
	//divide number by 10 while simultaneously incrementing digits, while the number is still an integer
	while(tempNum >= 1){
		digits++;
		tempNum /= 10;
	}
    return digits;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    PrimesSieve siv(limit);
    cout << endl;
    cout << "Number of primes found: " << siv.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    siv.display_primes();
    return 0;
}
