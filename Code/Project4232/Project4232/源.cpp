#include "iostream"
#include "cmath"
#include "cstdio"
#include "cstring"
using namespace std;

class node {
public:
	int val = 0;
	int left = 0, right = 0;
};

int mmax(int a, int b) {
	return a > b ? a : b;
}

node smt[800000];
int val_data[200009] = { 0 };

void build_tree(int l, int r, int pos) {
	smt[pos].left = l;
	smt[pos].right = r;
	if (l == r - 1) {
		smt[pos].val = val_data[l];
		return;
	}

	int mid = (l + r) >> 1;
	build_tree(l, mid, pos * 2);
	build_tree(mid, r, pos * 2 + 1);

	smt[pos].val = mmax(smt[pos * 2].val, smt[pos * 2 + 1].val);
}

void update(int val, int pos, int root) {
	if (smt[root].left == smt[root].right - 1) {
		smt[root].val = val;
		return;
	}
	int mid = (smt[root].left + smt[root].right) >> 1;
	if (pos < mid)
		update(val, pos, root * 2);
	else
		update(val, pos, root * 2 + 1);
	smt[root].val = mmax(smt[root * 2].val, smt[root * 2 + 1].val);
}

int query(int l, int r, int root) {
	if (l <= smt[root].left && smt[root].right <= r) {
		return smt[root].val;
	}
	int mid = (smt[root].left + smt[root].right) >> 1;
	int ans1 = 0, ans2 = 0;
	if (l < mid) {
		ans1 = query(l, r, root * 2);
	}
	if (r > mid) {
		ans2 = query(l, r, root * 2 + 1);
	}
	return ans1 > ans2 ? ans1 : ans2;
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		memset(smt, 0, sizeof(smt));
		memset(val_data, 0, sizeof(val_data));

		for (int i = 0; i < n; ++i) {
			scanf("%d", &val_data[i]);
		}
		build_tree(0, n, 1);
		for (; m > 0; --m) {
			char op;
			int a, b;
			scanf("\n%c %d %d", &op, &a, &b);
			if (op == 'Q') {
				printf("%d\n", query(a - 1, b, 1));
			}
			else {
				update(b, a - 1, 1);
			}
		}
	}

	return 0;
}