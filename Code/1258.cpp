#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
using namespace std;

class node {
public:
	int val = 0;
	int left = 0, right = 0;
};

int val_data[100009] = { 0 };
node smt[400009];

void build_tree(int l, int r, int root) {
	smt[root].left = l;
	smt[root].right = r;
	if (l == r - 1) {
		smt[root].val = val_data[l];
		return;
	}

	int mid = (l + r) >> 1;
	build_tree(l, mid, root * 2);
	build_tree(mid, r, root * 2 + 1);

	smt[root].val = smt[root * 2].val + smt[root * 2 + 1].val;
}

int query(int l, int r, int root) {
	if (l <= smt[root].left && smt[root].right <= r) {
		return smt[root].val;
	}

	auto mid = (smt[root].left + smt[root].right) >> 1;
	int ans = 0;
	if (l < mid) {
		ans += query(l, r, root * 2);
	}
	if (r > mid) {
		ans += query(l, r, root * 2 + 1);
	}
	return ans;
}

void update(int val,int pos, int root) {
	if (smt[root].right - smt[root].left == 1) {
		smt[root].val += val;
		return;
	}

	auto mid = (smt[root].left + smt[root].right) >> 1;
	if (pos < mid) {
		update(val, pos, root * 2);
	}
	else {
		update(val, pos, root * 2 + 1);
	}
	smt[root].val = smt[root * 2].val + smt[root * 2 + 1].val;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	build_tree(0, 100009, 1);

	long long cnt = 0;
	for (int i = 0; i < n; ++i) {
		cin >> val_data[i];

		update(1, val_data[i], 1);
		cnt += (long long)query(val_data[i] + 1, 100009, 1);
	}

	cout << cnt;

	return 0;
}