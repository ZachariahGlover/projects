#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

int main(int argc, const char* argv[]) {

	cout << "\n";

	const char * invalidInput = "Invalid input. Please input one integer, such that 1 < i.\n";

	if (argc != 2) {
		cout << invalidInput;
		return -1;
	}

	uint64_t limit;
	istringstream iss;

	iss.str(argv[1]);
	if (!(iss >> limit)) {
		cout << invalidInput;
		delete invalidInput;
		return -1;
	}
	iss.clear();

	if (limit < 2) {
		cout << invalidInput;
		delete invalidInput;
		return -1;
	}

	uint64_t sum_squares = 0;
	uint64_t square_sums = 0;
	uint64_t difference = 0;

	square_sums = (limit * (limit + 1)) / 2;
	square_sums *= square_sums;

	sum_squares = (limit * (limit + 1) * ((2 * limit) + 1)) / 6;

	if (square_sums > sum_squares) {
		difference = square_sums - sum_squares;
	} else {
		difference = sum_squares - square_sums;
	}

	cout << "The difference between the sum of the squares of the first " << limit << " natural numbers and the square of the sums is " << difference <<".\n";

	return 0;
}
