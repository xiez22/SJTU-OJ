#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int m;
	cin >> m;

	vector<int> mdata(m);
	
	int maxn = 0;
	for (int i = 0; i < m; ++i) {
		cin >> mdata[i];
		maxn = mdata[i] > maxn ? mdata[i] : maxn;
	}

	vector<bool> isNum(maxn + 1, true);
	vector<int> cnt(maxn + 1, 0);
	for (int i = 2; i <= maxn; ++i) {
		if (!isNum[i]) {
			cnt[i] = cnt[i - 1];
			continue;
		}
		for (int j = 2 * i; j <= maxn; j += i)
			isNum[i] = false;
		cnt[i] = cnt[i - 1] + 1;
	}

	for (auto p : mdata) {

	}

	return 0;
}