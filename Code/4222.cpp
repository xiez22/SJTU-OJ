#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	for (; t; --t) {
		int n, m;
		cin >> n >> m;

		vector<bool> mdata(m, false);
		mdata[0] = true;

		int cur_sum = 0;
		bool flag = false;
		for (int i = 0; i < n; ++i) {
			int temp;
			cin >> temp;
			if (flag)
				continue;
			cur_sum = (cur_sum + temp) % m;
			if (mdata[cur_sum]) {
				flag = true;
			}
			else
				mdata[cur_sum] = true;
		}
		if (flag)
			cout << "YES\n";
		else
			cout << "NO\n";
	}

	return 0;
}