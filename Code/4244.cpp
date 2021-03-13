#include "iostream"
#include "vector"
using namespace std;

class node {
public:
	vector<int> child;
	long long s = 0;
	long long a = 0;
	int parent = 0;
};

long long ans = 0;

void update(int pos, vector<node>& node_list) {
	if (pos == 1) {
		node_list[pos].a = node_list[pos].s;
		ans += node_list[pos].a;
	}
	else if (node_list[pos].s >= 0) {
		node_list[pos].a = node_list[pos].s - node_list[node_list[pos].parent].s;
		ans += node_list[pos].a;
	}
	else {
		if (node_list[pos].child.empty()) {
			node_list[pos].a = 0;
			ans += node_list[pos].a;
			return;
		}
		node_list[pos].s = node_list[node_list[pos].child[0]].s;
		for (auto p : node_list[pos].child) {
			node_list[pos].s = node_list[p].s < node_list[pos].s ? node_list[p].s : node_list[pos].s;
		}
		node_list[pos].a = node_list[pos].s - node_list[node_list[pos].parent].s;
		ans += node_list[pos].a;
	}
	for (auto p : node_list[pos].child) {
		update(p, node_list);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	vector<node> node_list(n + 1);

	for (int i = 2; i <= n; ++i) {
		int temp;
		cin >> temp;
		node_list[i].parent = temp;
		node_list[temp].child.push_back(i);
	}
	for (int i = 1; i <= n; ++i) {
		cin >> node_list[i].s;
	}

	update(1, node_list);
	cout << ans;

	return 0;
}