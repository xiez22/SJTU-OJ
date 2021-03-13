#include "iostream"
#include "cstdio"
using namespace std;

long long cal(long long x, long long y) {
	if (y == 0 || x == 0)
		return 0;
	if (y >= x) {
		return cal(x, y % x) + y / x * x * 4;
	}
	else {
		return cal(x % y, y) + x / y * y * 4;
	}
}

int main() {
	long long x, y;
	cin >> x >> y;

	cout << cal(x, y);

	return 0;
}