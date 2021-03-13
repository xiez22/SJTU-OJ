#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using pii = pair<int, int>;

vector<pii> tdata;

void bfs() {
	queue<int> qdata;
	qdata.push(0);

	while (!qdata.empty()) {
		auto tmp = qdata.front();
		qdata.pop();

		cout << tmp << " ";
		if (tdata[tmp].first) {
			qdata.push(tdata[tmp].first);
		}
		if (tdata[tmp].second) {
			qdata.push(tdata[tmp].second);
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
	for (int i = 1; i <= n - 1; ++i) {
		int tmp;
		cin >> tmp;
		if (!tdata[tmp].first) {
			tdata[tmp].first = i;
		}
		else {
			tdata[tmp].second = i;
		}
	}

	bfs();

	return 0;
}