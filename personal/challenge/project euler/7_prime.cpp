#include <cstdlib>
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;

uint64_t powerMod(uint64_t n, uint64_t k, uint64_t m) {
	uint64_t result = n;
	while (k > 1) {
		result *= n;
		result %= m;
		k--;
	}
	return result;
}

int isPrime(uint64_t n) {
	srand(time(0));
	if (n > 3) {
		if (n & 1) {
	    	uint64_t s, d;
	    	d = (n - 1) / 2;
	    	s = 1;
	    	while (!(d & 1)) {
	    		d /= 2;
	    		s++;
	    	}
	    	uint64_t a, x;
	    	int pass;
	    	for (int i = 0; i < 100; i++) {
    			a = (rand() % (n - 4)) + 2;
    			x = powerMod(a, d, n);

    			if (!((x == 1) || (x == (n - 1)))) {
    				for (int k = 0; k < s; k++) {
    					pass = 0;
    					x = powerMod(x, 2, n);

    					if (x == 1) {
    						return 0;
    					}
    					if (x == (n - 1)) {
    						pass = 1;
    						break;
    					}
    				}
    				if (!(pass)) {
    					return 0;
    				}
    			}
	    	}
	    	return 1;
		}
  	} else {
  		if ((n == 2) || (n == 3)) {
  			return 1;
  		}
  		return 0;
  	}
}

int main(int argc, const char* argv[]) {

	cout << "\n";

	const char * invalidInput = "Invalid input. Please input one integer, such that 0 < i.\n";

	if (argc != 2) {
		cout << invalidInput;
		return -1;
	}

	uint64_t num;
	istringstream iss;

	iss.str(argv[1]);
	if (!(iss >> num)) {
		cout << invalidInput;
		delete invalidInput;
		return -1;
	}
	iss.clear();

	if (num < 1) {
		cout << invalidInput;
		delete invalidInput;
		return -1;
	} else if (num == 1) {
		cout << "The 1st prime number is 2.\n";
		return 0;
	} else if (num == 2) {
		cout << "The 2nd prime number is 3.\n";
		return 0;
	} else if (num == 3) {
		cout << "The 3rd prime number is 5.\n";
		return 0;
	}

	uint64_t ith = 4;
	uint64_t p = 7;
	uint64_t k = 1;

	while (ith <  num) {
		k++;
		p = 6 * k;
		if (isPrime(p - 1)) {
			ith++;
			if (ith == num) {
				p--;
				continue;
			} else if (isPrime(p + 1)) {
				ith++;
				p++;
			}
		} else if (isPrime(p + 1)) {
			ith++;
			p++;
		}
	}

	cout << "The " << num << "th prime number is " << p <<".\n";

	return 0;
}
