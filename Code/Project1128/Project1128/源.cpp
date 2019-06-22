#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	
	vector<pair<int, int>> vector_data(n);
	
	for (int i = 0; i < n; ++i) {
		cin >> vector_data[i].first >> vector_data[i].second;
	}

	sort(vector_data.begin(), vector_data.end(), [](pair<int, int>& a, pair<int, int>& b) {return a.second > b.second; });

	int ans = 0;
	priority_queue<int> queue_data;
	for (int t = vector_data.front().second, i = 0; t > 0; --t) {
		for (; i < vector_data.size() && vector_data[i].second >= t; ++i)
			queue_data.push(vector_data[i].first);
		if (!queue_data.empty()) {
			ans += queue_data.top();
			queue_data.pop();
		}
	}

	cout << ans;

	return 0;
}