#include <iostream>
using namespace std;

class node {
public:
	int lchild = 0, rchild = 0;
	int num = 1;
	int red_num = 0;
	bool is_red = false;
	int parent = 0;
};

node node_list[100009];

int dfs(int root) {
	if (node_list[root].lchild)
		node_list[root].num += dfs(node_list[root].lchild);
	if (node_list[root].rchild)
		node_list[root].num += dfs(node_list[root].rchild);
	return node_list[root].num;
}

void paint_red(int root,int pos) {
	pos = pos % node_list[root].num;
	int this_pos = node_list[root].lchild ? node_list[node_list[root].lchild].num : 0;
	if (pos == this_pos) {
		if (!node_list[root].is_red) {
			node_list[root].is_red = true;
			for (auto p = root; p; p = node_list[p].parent)
				++node_list[p].red_num;
		}
		return;
	}
	else if (pos < this_pos) {
		paint_red(node_list[root].lchild, pos);
	}
	else {
		paint_red(node_list[root].rchild, pos - this_pos - 1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, p, q;
	cin >> n >> p >> q;

	for (int i = 0; i < n; ++i) {
		int x, l, r;
		cin >> x >> l >> r;

		node_list[x].lchild = l;
		node_list[x].rchild = r;
		if (l)
			node_list[l].parent = x;
		if (r)
			node_list[r].parent = x;
	}

	int root = 0;
	for(int i=1;i<=n;++i)
		if (node_list[i].parent == 0) {
			root = i;
			break;
		}

	dfs(root);

	for (int i = 0; i < p; ++i) {
		int t, x;
		cin >> t >> x;
		paint_red(t, x);
	}

	for (int i = 0; i < q; ++i) {
		int w;
		cin >> w;
		cout << node_list[w].red_num << "\n";
	}

	return 0;
}