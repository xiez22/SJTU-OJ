#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class node {
public:
	int code;
	vector<pair<int, int>> edges;
};

vector<node> nl, nlf;
vector<bool> visited;
vector<int> forest_num;

int dfs1(int pos, int k, int code) {
	nl[pos].code = code;
	visited[pos] = true;
	int ans = 1;
	for (auto edge : nl[pos].edges) {
		if (edge.second < k && !visited[edge.first]) {
			ans += dfs1(edge.first, k, code);
		}
	}
	return ans;
}

int dfs2(int pos, int& num) {
	visited[pos] = true;
	num += forest_num[pos];
	int ans = 0;
	for (auto edge : nlf[pos].edges) {
		if (!visited[edge.first]) {
			ans += forest_num[edge.first] * num;
			ans += dfs2(edge.first, num);
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m, k;
	cin >> n >> m >> k;

	nl.resize(n);
	vector<pair<int, int>> k_edge;
	for (int i = 0; i < m; ++i) {
		int x, y, v;
		cin >> x >> y >> v;
		--x, --y;
		nl[x].edges.emplace_back(make_pair(y, v));
		nl[y].edges.emplace_back(make_pair(x, v));
		if (v == k) {
			k_edge.emplace_back(make_pair(x, y));
		}
	}

	int code = 0;
	visited.resize(n, false);
	for (int i = 0; i < n; ++i) {
		if (visited[i]) {
			continue;
		}
		int ans = dfs1(i, k, code);
		forest_num.emplace_back(ans);
		++code;
	}

	nlf.resize(code);
	for (auto p : k_edge) {
		nlf[nl[p.first].code].edges.emplace_back(make_pair(nl[p.second].code, k));
		nlf[nl[p.second].code].edges.emplace_back(make_pair(nl[p.first].code, k));
	}

	visited.clear();
	visited.resize(code, false);
	int ans = 0;
	for (int i = 0; i < code; ++i) {
		if (visited[i]) {
			continue;
		}
		int num = 0;
		ans += dfs2(i, num);
	}
	cout << ans;

	return 0;
}