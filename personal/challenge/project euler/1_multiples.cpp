#include <iostream>
#include <sstream>

using namespace std;

int sumByMultiple(int m, int b) {
	int k = 1;
	int s = 0;
	while (k * m < b) {
		s += k * m;
		k++;
	}
	return s;
}

int main(int argc, const char* argv[]) {

	cout << "\n";
	const char * invalidInput = "Invalid input. Please input three integers separated by spaces, such that 1 < i0 <> i1 < i2.\n";

	if (argc != 4) {
		cout << invalidInput;
		return -1;
	}

	int m0, m1, bound;
	istringstream iss;

	iss.str(argv[1]);
	if (!(iss >> m0)) {
		cout << invalidInput;
		delete invalidInput;
		return -1;
	}
	iss.clear();

	iss.str(argv[2]);
	if (!(iss >> m1)) {
		cout << invalidInput;
		delete invalidInput;
		return -1;
	}
	iss.clear();

	iss.str(argv[3]);
	if (!(iss >> bound)) {
		cout << invalidInput;
		delete invalidInput;
		return -1;
	}
	iss.clear();

	if ((m0 != m1) && (m0 > 1) && (m1 > 1) && (bound > m0) && (bound > m1)) {
		int sum = sumByMultiple(m0, bound) + sumByMultiple(m1, bound) - sumByMultiple(m0 * m1, bound);
		cout << "The sum of all the multiples of " << m0 << " or " << m1 << " below " << bound << " is " << sum << ".\n";
		delete invalidInput;
	} else {
		cout << invalidInput;
		delete invalidInput;
		return -1;
	}

	return 0;
}
