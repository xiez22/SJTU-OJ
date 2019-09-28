#include <iostream>
using namespace std;

int main() {
	uint64_t n, k, A, B, ans = 0;
	cin >> n >> k >> A >> B;

	for (; n >= k && (n / k * k - n / k) * A >= B; n /= k) {
		ans += B + (n - n / k * k) * A;
	}
	ans += (n - 1ull) * A;
	cout << ans;

	return 0;
}