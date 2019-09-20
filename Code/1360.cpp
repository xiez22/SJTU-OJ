#include "iostream"
#include "cmath"
#include "cstdio"
using namespace std;

int times[100009][2] = { 0 };

template <class T>
void quick_sort(T start, T end) {
	if (start == end)
		return;
	auto i = start, j = end;
	--j;
	if (i == j)
		return;
	//½»»»
	auto key = (*start)[1];
	auto tmp = (*start)[0];
	for (bool status = true; i != j;) {
		if (status) {
			if ((*j)[1] < key) {
				(*i)[0] = (*j)[0];
				(*i)[1] = (*j)[1];
				++i;
				status = false;
			}
			else
				--j;
		}
		else {
			if ((*i)[1] > key) {
				(*j)[0] = (*i)[0];
				(*j)[1] = (*i)[1];
				--j;
				status = true;
			}
			else
				++i;
		}
	}
	(*i)[0] = tmp;
	(*i)[1] = key;
	//µÝ¹é
	quick_sort(start, i + 1);
	quick_sort(i + 1, end);
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &times[i][0], &times[i][1]);
	}
	//ÅÅÐò
	quick_sort(times, times + n);
	int ans = 0;
	for (int i = 0, cur_time = 0; i < n; ++i) {
		if (times[i][0] >= cur_time) {
			++ans;
			cur_time = times[i][1];
		}
	}

	cout << ans;

	return 0;
}