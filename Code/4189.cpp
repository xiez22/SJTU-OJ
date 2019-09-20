#include <iostream>
#include <vector>
using namespace std;

class node {
public:
	int parent = 0, child_num = 0;
	vector<int> child;
};

vector<node> tree_data;

int dfs(int root) {
	tree_data[root].child_num = 1;
	for (auto p : tree_data[root].child) {
		if (p != tree_data[root].parent) {
			tree_data[p].parent = root;
			tree_data[root].child_num += dfs(p);
		}
	}
	return tree_data[root].child_num;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	
	tree_data.resize(n + 1);

	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		tree_data[u].child.push_back(v);
		tree_data[v].child.push_back(u);
	}

	dfs(1);

	for (int i = 1; i <= n; ++i) {
		if (n - tree_data[i].child_num > n / 2) {
			continue;
		}
		bool flag = true;
		for (auto p : tree_data[i].child) {
			if (p != tree_data[i].parent) {
				if (tree_data[p].child_num > n / 2) {
					flag = false;
					break;
				}
			}
		}
		if (flag) {
			cout << i << " ";
		}
	}

	return 0;
}