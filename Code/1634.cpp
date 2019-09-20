#include "iostream"
#include "cstdio"
using namespace std;

long long cnt = 0;

int val_data[1000009] = { 0 };

void quick_sort(int* left, int* right) {
	if (left >= right - 1)
		return;
	auto p = left, q = right - 1;
	auto key = *p;
	bool flag = true;
	while (p < q) {
		if (flag) {
			if (*q < key) {
				*p = *q;
				flag = false;
				++p;
			}
			else {
				--q;
			}
			++cnt;
		}
		else {
			if (*p > key) {
				*q = *p;
				flag = true;
				--p;
			}
			else {
				++q;
			}
			++cnt;
		}
	}
	*p = key;
	quick_sort(left, p + 1);
	quick_sort(p + 1, right);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, k;
	cin >> n >> k;

	for (int i = 0; i < n; ++i)
		cin >> val_data[i];

	if (k == 3) {
		quick_sort(val_data, val_data + n);
		for (int i = 0; i < n; ++i) {
			cout << val_data[i] << " ";
		}
		cout << endl;
		cout << cnt;
	}

	return 0;
}