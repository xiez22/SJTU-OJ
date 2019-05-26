#include "iostream"
#include "cstdio"
#include "cstring"
#include "cstdio"
using namespace std;

class node {
public:
	//unsigned long long val=0;
	int left = 0, right = 0;
	unsigned long long tag = 0, tag_num = 0;
};

node smt[800009];
unsigned long long pnum[200009] = { 0 };

void build_tree(int l, int r, int root) {
	smt[root].left = l;
	smt[root].right = r;
	if (l == r - 1) {
		return;
	}
	int mid = (l + r) >> 1;
	build_tree(l, mid, root * 2);
	build_tree(mid, r, root * 2 + 1);
}

void push_down(int root) {
	smt[root * 2].tag = (smt[root * 2].tag * pnum[smt[root].tag_num] + smt[root].tag);
	smt[root * 2].tag_num += smt[root].tag_num;
	smt[root * 2 + 1].tag = (smt[root * 2 + 1].tag * pnum[smt[root].tag_num] + smt[root].tag);
	smt[root * 2 + 1].tag_num += smt[root].tag_num;
	smt[root].tag = 0;
	smt[root].tag_num = 0;
}

void update(int l, int r, unsigned long long val, int root) {
	if (l <= smt[root].left && smt[root].right <= r) {
		smt[root].tag = smt[root].tag * (unsigned long long)257 + val;
		smt[root].tag_num++;
		return;
	}
	int mid = (smt[root].left + smt[root].right) >> 1;
	push_down(root);
	if (l < mid) {
		update(l, r, val, root * 2);
	}
	if (r > mid) {
		update(l, r, val, root * 2 + 1);
	}
}

unsigned long long query(int l, int r, int root) {
	if (l <= smt[root].left && smt[root].right <= r) {
		return smt[root].tag;
	}
	int mid = (smt[root].left + smt[root].right) >> 1;
	push_down(root);
	if (l < mid) {
		return query(l, r, root * 2);
	}
	if (r > mid) {
		return query(l, r, root * 2 + 1);
	}
}

int get_pos(int pos, int root) {
	if (smt[root].right - smt[root].left == 1) {
		return root;
	}
	int mid = (smt[root].right + smt[root].left) >> 1;
	if (pos < mid)
		return get_pos(pos, root * 2);
	else
		return get_pos(pos, root * 2 + 1);
}

int main() {
	pnum[0] = 1;
	for (int i = 1; i < 200000; ++i)
		pnum[i] = pnum[i - 1] * (unsigned long long)257;
	int n, m;
	scanf("%d %d", &n, &m);
	build_tree(0, n, 1);

	for (; m > 0; --m) {
		int op;
		scanf("%d", &op);

		if (op == 0) {
			int L, R, K;
			scanf("%d %d %d", &L, &R, &K);
			update(L - 1, R, K, 1);
		}
		else {
			int X, Y;
			scanf("%d %d", &X, &Y);
			auto a = query(X - 1, X, 1), b = query(Y - 1, Y, 1);
			if (a == b) {
				printf("YES\n");
				auto pos1 = get_pos(X - 1, 1), pos2 = get_pos(Y - 1, 1);
				smt[pos1].tag = 0;
				smt[pos2].tag = 0;
				smt[pos1].tag_num = 0;
				smt[pos2].tag_num = 0;
			}
			else {
				printf("NO\n");
			}
		}
	}

	return 0;
}