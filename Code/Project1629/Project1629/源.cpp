#include <iostream>
#include <vector>
using namespace std;

class node {
public:
	int parent = 0;
	int num = 1;
	vector<int> child;
};

node tree_data[10009];

int dfs(int root) {
	for (auto p : tree_data[root].child) {
		if (p != tree_data[root].parent) {
			tree_data[p].parent = root;
			tree_data[root].num += dfs(p);
		}
	}
	return tree_data[root].num;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		tree_data[v].child.push_back(u);
		tree_data[u].child.push_back(v);
	}

	dfs(1);

	int ans = 999999999, ans_i = 0;;
	for (int i = 1; i <= n; ++i) {
		int cur_ans = n - tree_data[i].num;
		for (auto p : tree_data[i].child) {
			if (p != tree_data[i].parent) {
				cur_ans = tree_data[p].num > cur_ans ? tree_data[p].num : cur_ans;
			}
		}
		if (cur_ans < ans) {
			ans_i = i;
			ans = cur_ans;
		}
	}

	cout << ans_i << " " << ans;

	return 0;
}