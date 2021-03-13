#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;

class node {
public:
	int remain = 0;
	vector<int> child;
};

vector<node> nlist;

int bfs(const vector<int> rlist) {
	queue<pii> qdata;
	for(auto root:rlist)
		qdata.push(make_pair(root, 1));

	int ans = 0;
	while (!qdata.empty()) {
		auto temp = qdata.front();
		qdata.pop();
		ans = max(ans, temp.second);

		for (auto& p : nlist[temp.first].child) {
			--nlist[p].remain;
			if (!nlist[p].remain) {
				qdata.push(make_pair(p, temp.second + 1));
			}
		}
	}
	return ans;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;
	nlist.resize(n + 1);

	for (; m; --m) {
		int a, b;
		cin >> a >> b;
		++nlist[a].remain;
		nlist[b].child.emplace_back(a);
	}

	vector<int> rlist;
	for (int i = 1; i <= n; ++i) {
		if (nlist[i].remain == 0)
			rlist.emplace_back(i);
	}

	cout << bfs(rlist);

	return 0;
}