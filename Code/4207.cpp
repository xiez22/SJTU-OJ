#include "iostream"
#include "cstdio"
using namespace std;

int a[5009] = { 0 };

template <class T, class T_val = decltype(*declval<T>()),
	class Compare = bool (*)(T_val, T_val)>
	void quick_sort(T start, T end,
		Compare cmp = [](T_val a, T_val b) {return a < b; }) {
	if (start == end)
		return;
	auto i = start, j = end;
	--j;
	if (i == j)
		return;
	//½»»»
	auto key = *start;
	for (bool status = true; i != j;) {
		if (status) {
			if (cmp(*j, key)) {
				*i = *j;
				++i;
				status = false;
			}
			else
				--j;
		}
		else {
			if (cmp(key, *i)) {
				*j = *i;
				--j;
				status = true;
			}
			else
				++i;
		}
	}
	*i = key;
	//µÝ¹é
	quick_sort(start, ++i, cmp);
	quick_sort(i, end, cmp);
}

int dp_data[5000][5000] = { 0 };
int n;

int dp(int pos, int k) {
	if (pos >= n || k <= 0) {
		return 0;
	}
	if (dp_data[pos][k] > 0)
		return dp_data[pos][k];
	int ans1 = dp(pos + 1, k), ans2 = 0, i = pos;
	for (; i < n; ++i) {
		if (a[i] - a[pos] <= 5)
			++ans2;
		else
			break;
	}
	ans2 += dp(i, k - 1);
	dp_data[pos][k] = ans1 < ans2 ? ans2 : ans1;
	return dp_data[pos][k];
}

int main() {
	int k;
	cin >> n >> k;

	for (int i = 0; i < n; ++i)
		scanf("%d", &a[i]);

	quick_sort(a, a + n);

	cout << dp(0, k);

	return 0;
}