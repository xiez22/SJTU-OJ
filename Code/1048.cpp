#include <iostream>
#include <queue>
#include <vector>
using namespace std;

using pii = pair<int, int>;

vector<pii> tdata;

void bfs(int root) {
	queue<int> qdata;
	qdata.push(root);
	
	while (!qdata.empty()) {
		auto temp = qdata.front();
		qdata.pop();

		cout << temp << "\n";

		if (tdata[temp].first) {
			qdata.push(tdata[temp].first);
			qdata.push(tdata[temp].second);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	tdata.resize(n + 1, pii(0, 0));
	vector<bool> isroot(n + 1, true);

	int a, b, c;
	while (cin >> a) {
		cin >> b >> c;

		tdata[a].first = b;
		tdata[a].second = c;

		isroot[b] = isroot[c] = false;
	}

	int root = 0;

	for (int i = 1; i <= n; ++i) {
		if (isroot[i]) {
			root = i;
			break;
		}
	}

	bfs(root);

	return 0;
}