#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;

	vector<int> xval(n + 1, 0);
	for (int i = 1; i <= n; ++i)
		xval[i] = xval[i - 1] ^ i;

	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		int k = n / i, r = n % i;
		if (k % 2)
			ans ^= xval[i - 1];
		ans ^= xval[r];
	}

	cout << ans;
	
	return 0;
}