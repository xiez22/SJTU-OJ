#include <iostream>
#include <vector>
using namespace std;

vector<int> vdata;
int n;

int find_k(int start, int end, int k) {
	int key = vdata[start], l = start, r = end - 1;
	bool status = true;
	while (l < r) {
		if (status)
			if (key > vdata[r]) {
				vdata[l] = vdata[r];
				status = false;
				++l;
			}
			else
				--r;
		else
			if (key < vdata[l]) {
				vdata[r] = vdata[l];
				status = true;
				--r;
			}
			else
				++l;
	}
	vdata[l] = key;
	if (k > l - start)
		return find_k(l + 1, end, k - l + start - 1);
	else if (k < l - start)
		return find_k(start, l, k);
	else
		return vdata[l];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int k;
	cin >> n >> k;
	vdata.resize(n);

	for (int i = 0; i < n; ++i)
		cin >> vdata[i];

	cout << find_k(0, n, k - 1);

	return 0;
}