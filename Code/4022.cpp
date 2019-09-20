#include "iostream"
#include "cstdio"
using namespace std;

int main() {
	long long x, n;
	cin >> x >> n;

	long long ans = 0;
	ans += n / 7 * (250 * 5);

	for (long long i = 0; i < n % 7; ++i) {
		if (x + i != 6 && x + i != 7)
			ans += 250;
	}

	cout << ans;

	return 0;
}