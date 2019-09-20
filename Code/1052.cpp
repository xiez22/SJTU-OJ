#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<set<int>> vdata(n);
	vector<int> vsize(n);

	for (int i = 0; i < n; ++i)
		cin >> vsize[i];

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < vsize[i]; ++j) {
			int temp;
			cin >> temp;
			vdata[i].insert(temp);
		}
	}

	int m;
	cin >> m;
	for (; m; --m) {
		char op;
		int a, b;
		cin.get();
		cin >> op >> a >> b;
		--a;
		--b;
		if (op == '+') {
			vdata[a].insert(vdata[b].begin(), vdata[b].end());
		}
		else if (op == '-') {
			for (auto p = vdata[a].begin(); p != vdata[a].end();) {
				if (vdata[b].find(*p) != vdata[b].end()) {
					vdata[a].erase(p++);
				}
				else
					++p;
			}
		}
		else {
			for (auto p = vdata[a].begin(); p != vdata[a].end();) {
				if (vdata[b].find(*p) == vdata[b].end()) {
					vdata[a].erase(p++);
				}
				else
					++p;
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		for (auto p : vdata[i]) {
			cout << p << " ";
		}
		cout << "\n";
	}

	return 0;
}