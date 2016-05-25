#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

uint64_t largestPrimeFactor(uint64_t n) {
	uint64_t k = 2;

	while (k < n) {
		if (n % k == 0) {
			n /= k;
			k = 2;
		} else {
			k++;
		}
	}

	return k;
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
		out << invalidInput;
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
