#include "iostream"
#include "cstdio"
using namespace std;

constexpr long long mod = (long long)(1e9 + 7);

int pos[300009] = { 0 };

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


int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; ++i)
		scanf("%d", &pos[i]);

	quick_sort(pos, pos + n);

	long long ans = 0, cur_ans = 0, cnt = 0;

	for (int i = 1; i < n; ++i) {
		cnt = (cnt * 2 + 1) % mod;
		cur_ans = (cur_ans * 2 + (pos[i] - pos[i - 1]) * cnt) % mod;
		ans = (ans + cur_ans) % mod;
	}

	cout << ans;

	return 0;
}