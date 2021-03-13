#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	vector<int> up(n + 1), down(n + 1), ups(n + 1, 0), downs(n + 1, 0);

	for (int i = 1; i <= n; ++i) {
		cin >> up[i];
		ups[i] = ups[i - 1] + up[i];
	}
	for (int i = 1; i <= n; ++i)
		cin >> down[i];
	
	downs[n] = down[n];
	for (int i = n - 1; i >= 1; --i)
		downs[i] = downs[i + 1] + down[i];

	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		int cur_ans = ups[i] + downs[i];
		ans = cur_ans > ans ? cur_ans : ans;
	}

	cout << ans;

	return 0;
}