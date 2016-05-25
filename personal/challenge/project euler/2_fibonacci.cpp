#include <iostream>
#include <sstream>

using namespace std;

int fibSum(int m, int b) {
	int s = 0;
	int ft = 0;
	int fp = 1;
	int fc = 1;
	while (fc + fp < b) {
		ft = fc;
		fc += fp;
		fp = ft;
		if (fc % m == 0) {
			s+= fc;
		}
	}
	return s;
}

int main(int argc, const char* argv[]) {

	cout << "\n";
	const char * invalidInput = "Invalid input. Please input two integers separated by spaces, such that 1 < i0 < i1.\n";

	if (argc != 3) {
		cout << invalidInput;
		return -1;
	}

	int multiple, bound;
	istringstream iss;

	iss.str(argv[1]);
	if (!(iss >> multiple)) {
		cout << invalidInput;
		delete invalidInput;
		return -1;
	}
	iss.clear();

	iss.str(argv[2]);
	if (!(iss >> bound)) {
		cout << invalidInput;
		delete invalidInput;
		return -1;
	}
	iss.clear();

	if ((1 < multiple) && (multiple < bound)) {
		int sum = fibSum(multiple, bound);
		cout << "The sum of all fibonacci numbers divisible by " << multiple << " below " << bound << " is " << sum << ".\n";
		delete invalidInput;
	} else {
		cout << invalidInput;
		delete invalidInput;
		return -1;
	}

	return 0;
}
