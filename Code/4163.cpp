#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

int val_data[100009] = { 0 };

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	int left = 0, right = 0;

	for (int i = 0; i < n; ++i) {
		scanf("%d", &val_data[i]);
		right += val_data[i];
		left = val_data[i] > left ? val_data[i] : left;
	}

	int right_ans = 0;

	while (left <= right) {
		auto mid = (left + right) >> 1;
		int cnt = 0;
		for (int i = 0; i < n; ) {
			int cur_ans = 0;
			++cnt;
			for (int j = i;; ++j) {
				cur_ans += val_data[j];
				if (cur_ans > mid) {
					i = j;
					break;
				}
				if (j == n - 1) {
					i = j + 1;
					break;
				}
			}
		}
		if (cnt <= m) {
			right_ans = mid;
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}

	cout << right_ans;

	return 0;
}