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

uint64_t largestPrimeFactor(uint64_t n) {
	uint64_t k = 2;
	while (k < n) {
		if (n % k == 0) {
			if (isPrime(n / k)) {
				return (n / k);
			}
		}
		k++;
	}
	return -1;
}

int main(int argc, const char* argv[]) {

	cout << "\n";
	const char * invalidInput = "Invalid input. Please input one integer, such that 3 < i.\n";

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

	if (num < 4) {
		cout << invalidInput;
		delete invalidInput;
		return -1;
	}

	if (num > 3) {
		uint64_t prime = largestPrimeFactor(num);
		if (prime == -1) {
			cout << "Something broke, lol.\n";
			delete invalidInput;
			return -1;
		}
		cout << "The largest prime factor of " << num << " is " << prime << ".\n";
		delete invalidInput;
	} else {
		cout << invalidInput;
		delete invalidInput;
		return -1;
	}

	return 0;
}
