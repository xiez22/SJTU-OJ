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
	vector<int> vdata(n - 1);

	for (int i = 0; i < n - 1; ++i)
		cin >> vdata[i];

	int ans = vdata[0] + vdata[n - 2];
	for (int i = 0; i < n - 2; ++i)
		ans += min(vdata[i], vdata[i + 1]);

	cout << ans;

	return 0;
}