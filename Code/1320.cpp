#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int val_data[1009][1009] = { 0 };
int n;

int dp_data[1009][1009] = { 0 };

int dp(int posi, int posj) {
	if (dp_data[posi][posj] >= 0)
		return dp_data[posi][posj];
	if (posi >= n)
		return 0;

	int ans1 = val_data[posi][posj] + dp(posi + 1, posj),
		ans2 = val_data[posi][posj] + dp(posi + 1, posj + 1);

	dp_data[posi][posj] = max(ans1, ans2);
	return dp_data[posi][posj];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;

	memset(dp_data, -1, sizeof(dp_data));

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= i; ++j) {
			cin >> val_data[i][j];
		}
	}

	cout << dp(0, 0);

	return 0;
}