#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	int max_n = 0;
	for (int i = 0; i < n; ++i) {
		int temp;
		cin >> temp;
		max_n = max(temp, max_n);
	}
	cout << max_n;
	return 0;
}
