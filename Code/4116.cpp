#include "iostream"
using namespace std;

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
	//交换
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
	//递归
	quick_sort(start, ++i, cmp);
	quick_sort(i, end, cmp);
}

//记录被选中的点
int choose[100009] = { 0 };

int main() {
	int n, m;
	ios::sync_with_stdio(false);
	cin >> n >> m;

	int* dis = new int[n];
	for (int i = 0; i < n; i++)
		cin >> dis[i];
	quick_sort(dis, dis + n);
	int cl = 0, cr = dis[n - 1], ans = 0;
	//二分法
	while (cl <= cr) {
		int mid = (cl + cr) >> 1, cnt = 0;
		for (int i = 1, startNum = 0; i < n; i++)
			if (dis[i] - dis[startNum] < mid) cnt++;
			else startNum = i;
		if (cnt > n - m) cr = mid - 1;
		else {
			cl = mid + 1;
			ans = mid;
		}
	}
	cout << ans;
	

	return 0;
}