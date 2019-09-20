#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	vector<int> vdata(2 * n);

	for (int i = 0; i < 2 * n; ++i)
		cin >> vdata[i];
	sort(vdata.begin(), vdata.end());

	int ans = 0;
	for (int i = 0; i < n; ++i) {
		ans -= vdata[i];
	}
	for (int i = n; i < 2 * n; ++i) {
		ans += vdata[i];
	}

	cout << ans;

	return 0;
}