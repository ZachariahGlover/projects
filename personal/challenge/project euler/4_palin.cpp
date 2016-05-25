#include <cstdlib>
#include <iostream>

using namespace std;

int reverse(int n) {
	int r = 0;
    while (n != 0) {
        r *= 10;
        r += (n % 10);
        n /= 10;
    }
    return r;
}

int concatenate(int a, int b) {
	int p = 10;
	while (p <= a) {
		p *= 10;
	}
	return (a * p) + b;
}

//Find the largest palindrome made from the product of two 3-digit numbers.
int main(int argc, const char* argv[]) {

	int n = 997;
	int t = concatenate(n, reverse(n));

	int f0, f1;

	while (t > 10000) {
		n--;
		t = concatenate(n, reverse(n));
		for (int i = 100; i < 996; i++) {
			if (t % i == 0) {
				f0 = i;
				f1 = t / f0;
				if ((f1 > 99) && (f1 < 1000)) {
					cout << f0 << " * " << f1 << " = " << t << ".\n";
					return 0;
				}
			}
		}
	}

	return 0;
}
