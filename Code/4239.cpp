#include "iostream"
#include "cstdio"
using namespace std;

int stack_data[300009] = { 0 };
int stack_n = 0;

int mid_search(int l, int r, int val) {
	if (val > stack_data[stack_n - 1])
		return stack_n;
	int right_ans = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (stack_data[mid] >= val) {
			right_ans = mid;
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}
	return right_ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		int l, r;
		cin >> l >> r;
		
		int lpos = mid_search(0, stack_n - 1, l),
			rpos = mid_search(0, stack_n - 1, r);

		if (lpos == stack_n) {
			stack_data[stack_n++] = l;
		}
		else {
			if (rpos == stack_n)
				++stack_n;
			for (; rpos > lpos; --rpos) {
				stack_data[rpos] = stack_data[rpos - 1] + 1;
			}
			stack_data[lpos] = l;
		}
	}

	cout << stack_n;

	return 0;
}