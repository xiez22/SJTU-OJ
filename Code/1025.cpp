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
	
	vector<pair<int, int>> val_data(n);

	for (int i = 0; i < n; ++i) {
		cin >> val_data[i].first >> val_data[i].second;
	}

	sort(val_data.begin(), val_data.end(), [](pair<int, int>& a, pair<int, int>& b) {return a.first < b.first; });

	long long ans = 0;
	int cur_start = val_data[0].first, cur_end = val_data[0].second;
	for (auto p : val_data) {
		if (p.first > cur_end) {
			ans += (long long)cur_end - (long long)cur_start;
			cur_start = p.first;
			cur_end = p.second;
		}
		else {
			cur_end = p.second > cur_end ? p.second : cur_end;
		}
	}
	ans += (long long)cur_end - (long long)cur_start;

	cout << ans;

	return 0;
}