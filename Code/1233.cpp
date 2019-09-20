#include "iostream"
#include "cstdio"
using namespace std;

bool dfs_visited[20] = { 0 };

class graph_point {
public:
	int next[20] = { 0 };
	int edge_num = 0;

	void add_edge(int to) {
		//≈–∂œ «∑Ò÷ÿ∏¥
		for (int i = 0; i < edge_num; ++i)
			if (next[i] == to)
				return;
		next[edge_num++] = to;
	}
};

graph_point graph[12];

int dfs(int start, int length) {
	if (dfs_visited[start])
		return 0;
	if (length == 0) {
		return 1;
	}
	dfs_visited[start] = true;
	int ans = 0;
	for (int i = 0; i < graph[start].edge_num; ++i)
		ans += dfs(graph[start].next[i], length - 1);
	dfs_visited[start] = false;
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m, start, M;
	cin >> n >> m >> start >> M;

	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		graph[a].add_edge(b);
	}

	cout << dfs(start, M);

	return 0;
}