#include "iostream"
#include "cstdio"
using namespace std;

int times[10009][2] = { 0 };

template <class T>
void quick_sort(T start, T end) {
	if (start == end)
		return;
	auto i = start, j = end;
	--j;
	if (i == j)
		return;
	//½»»»
	auto key = (*start)[0];
	auto tmp = (*start)[1];
	for (bool status = true; i != j;) {
		if (status) {
			if ((*j)[0] < key) {
				(*i)[0] = (*j)[0];
				(*i)[1] = (*j)[1];
				++i;
				status = false;
			}
			else
				--j;
		}
		else {
			if ((*i)[0] > key) {
				(*j)[0] = (*i)[0];
				(*j)[1] = (*i)[1];
				--j;
				status = true;
			}
			else
				++i;
		}
	}
	(*i)[1] = tmp;
	(*i)[0] = key;
	//µÝ¹é
	quick_sort(start, i + 1);
	quick_sort(i + 1, end);
}

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &times[i][0], &times[i][1]);
	}
	quick_sort(times, times + n);

	int ans = 0;
	int cur_left = 0, cur_right = 0;
	for (int i = 0; i < n; ++i) {
		if (times[i][0] > cur_right) {
			ans += cur_right - cur_left;
			cur_left = times[i][0];
			cur_right = times[i][1];
		}
		else {
			if (cur_right < times[i][1])
				cur_right = times[i][1];
		}
	}
	ans += cur_right - cur_left;

	cout << ans;

	return 0;
}