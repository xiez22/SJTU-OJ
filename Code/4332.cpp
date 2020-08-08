#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n;
	cin >> n;

	vector<bool> d(n + 1, false);

	for (int i = 2; i <= n; ++i) {
		if (d[i])
			continue;
		for (int j = 2; i * j <= n; ++j) {
			d[i * j] = true;
		}
	}

	for (int i = n; i >= 0; --i) {
		if (!d[i]) {
			cout << 2 * i;
			break;
		}
	}

	return 0;
}