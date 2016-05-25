#include <iostream>
#include <limits.h>

using namespace std;

/* 20 -> 2, 4, 5, 10
 * 19 is prime
 * 18 -> 2, 3, 6, 9
 * 17 is prime
 * 16 -> 2, 4, 8
 * 14 -> 2, 7
 * 13 is prime.
 * 11 is prime.
 */

int main(int argc, const char* argv[]) {

	cout << "\n";

	for (int i = 2520; i < INT_MAX; i++) {
		if (i % 20 == 0) {
			if (i % 18 == 0) {
				if (i % 16 == 0) {
					if (i % 14 == 0) {
						if (i % 11 == 0) {
							if (i % 13 == 0) {
								if (i % 17 == 0) {
									if (i % 19 == 0) {
										cout << "The smallest positive number that is evenly divisible by all of the numbers from 1 to 20 is " << i << ".\n";
										return 0;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	cout << "Try harder.\n";

	return 0;
}
