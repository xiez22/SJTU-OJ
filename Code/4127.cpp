#include "iostream"
#include "cstdio"
#include "cmath"
#include "cstring"
using namespace std;

class edge {
public:
	int to = 0;
	edge* next = nullptr;
};

class tree_node {
public:
	int parent = 0;
	int depth = 0;
	int parent_list[24] = { 0 };
	edge* head = nullptr, * rear = nullptr;
};

tree_node tree_data[100009];
int root_pos = 0;

void dfs(int pos) {
	if (pos == root_pos) {
		tree_data[pos].depth = 0;
	}
	else {
		tree_data[pos].depth = tree_data[tree_data[pos].parent].depth + 1;
		int k = (int)(log(tree_data[pos].depth) / log(2));
		tree_data[pos].parent_list[0] = tree_data[pos].parent;
		for (int i = 1; i <= k; ++i) {
			tree_data[pos].parent_list[i] = tree_data[tree_data[pos].parent_list[i - 1]].parent_list[i - 1];
		}
	}
	for (auto p = tree_data[pos].head->next; p; p = p->next) {
		if (p->to != tree_data[pos].parent) {
			tree_data[p->to].parent = pos;
			dfs(p->to);
		}
	}
}

int LCA(int pos1, int pos2) {
	while (tree_data[pos1].depth < tree_data[pos2].depth) {
		int k = int(log(tree_data[pos2].depth - tree_data[pos1].depth) / log(2));
		pos2 = tree_data[pos2].parent_list[k];
	}
	while (tree_data[pos2].depth < tree_data[pos1].depth) {
		int k = int(log(tree_data[pos1].depth - tree_data[pos2].depth) / log(2));
		pos1 = tree_data[pos1].parent_list[k];
	}
	while (pos1 != pos2) {
		int k = int(log(tree_data[pos1].depth) / log(2));
		for (int i = k; i >= 0; --i) {
			if (i == 0 || tree_data[pos1].parent_list[i] != tree_data[pos2].parent_list[i]) {
				pos1 = tree_data[pos1].parent_list[i];
				pos2 = tree_data[pos2].parent_list[i];
			}
		}
	}
	return pos1;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	for (int i = 1; i <= n; ++i) {
		tree_data[i].rear = tree_data[i].head = new edge;
	}

	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;

		tree_data[u].rear->next = new edge;
		tree_data[u].rear = tree_data[u].rear->next;
		tree_data[u].rear->to = v;

		tree_data[v].rear->next = new edge;
		tree_data[v].rear = tree_data[v].rear->next;
		tree_data[v].rear->to = u;
	}

	root_pos = 1;
	dfs(1);

	int q;
	cin >> q;

	for (; q > 0; --q) {
		int u, v, w;
		cin >> u >> v >> w;
		int lca1 = LCA(u, v), lca2 = LCA(u, w), lca3 = LCA(v, w);
		if (tree_data[lca1].depth < tree_data[lca2].depth) {
			if (tree_data[lca3].depth > tree_data[lca2].depth) {
				cout << lca3 << "\n";
			}
			else {
				cout << lca2 << "\n";
			}
		}
		else {
			if (tree_data[lca3].depth > tree_data[lca1].depth) {
				cout << lca3 << "\n";
			}
			else {
				cout << lca1 << "\n";
			}
		}
	}

	return 0;
}