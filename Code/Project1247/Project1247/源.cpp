#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
using namespace std;

class node {
public:
	int left = 0, right = 0;
	int val = 0;
	bool flag = false;
};

node smt[100009];

void build_tree(int l, int r, int root) {
	smt[root].left = l;
	smt[root].right = r;
	if (l == r - 1) {
		smt[root].val = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build_tree(l, mid, root * 2);
	build_tree(mid, r, root * 2 + 1);

	smt[root].val = smt[root * 2].val + smt[root * 2 + 1].val;
}

void push_down(int root) {
	if (smt[root].flag) {
		smt[root].flag = false;
		smt[root * 2].val = 0;
		smt[root * 2 + 1].val = 0;
		smt[root * 2].flag = true;
		smt[root * 2 + 1].flag = true;
	}
}

void update(int l, int r, int root) {
	if (l <= smt[root].left && smt[root].right <= r) {
		smt[root].val = 0;
		smt[root].flag = true;
		return;
	}
	int mid = (smt[root].left + smt[root].right) >> 1;
	push_down(root);
	if (l < mid)
		update(l, r, root * 2);
	if (r > mid)
		update(l, r, root * 2 + 1);
	smt[root].val = smt[root * 2].val + smt[root * 2 + 1].val;
}

int query(int l, int r, int root) {
	if (l <= smt[root].val && smt[root].val <= r) {
		return smt[root].val;
	}
	int mid = (smt[root].left + smt[root].right) >> 1;
	push_down(root);
	int ans = 0;
	if (l < mid) {
		ans += query(l, r, root * 2);
	}
	if (r > mid) {
		ans += query(l, r, root * 2 + 1);
	}
	return ans;
}

int main() {
	int M, L;
	scanf("%d %d", &L, &M);

	build_tree(0, L + 1, 1);

	for (; M > 0; --M) {
		int a, b;
		scanf("%d %d", &a, &b);

		update(a, b + 1, 1);
	}

	printf("%d", query(0, L + 1, 1));

	return 0;
}