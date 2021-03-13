#include <iostream>
using namespace std;

int map_data[20][20] = { 0 };

int mmin(int a, int b) {
	return a < b ? a : b;
}

bool visited[20] = { 0 };
int n;

int dfs(int pos, int m) {
	if (m == n - 1) {
		return map_data[pos][0];
	}
	visited[pos] = true;
	int ans = 999999999;
	for (int i = 0; i < n; ++i) {
		if (i != pos && !visited[i]) {
			auto cur_ans = dfs(i, m + 1) + map_data[pos][i];
			ans = cur_ans < ans ? cur_ans : ans;
		}
	}
	visited[pos] = false;
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> map_data[i][j];

	/*
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				map_data[i][j] = mmin(map_data[i][j], map_data[i][k] + map_data[k][j]);
			}
		}
	}*/

	cout << dfs(0, 0);

	return 0;
}