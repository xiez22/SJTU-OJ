#include <iostream>
using namespace std;

int fast_pow(int a, int n) {
	int ans = 1, base = a;
	for (; n; n >>= 1) {
		if (n & 1)
			ans = (ans * base) % 2019;
		base = (base * base) % 2019;
	}
	return ans;
}

int main() {
	int a, n;
	cin >> a >> n;
	cout << fast_pow(a, n);

	return 0;
}