#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	map<int, set<int>> mdata;
	vector<int> vdata(n + 1);

	for (int i = 1; i <= n; ++i) {
		int temp;
		cin >> temp;

		if (mdata.find(temp) == mdata.end()) {
			set<int> stmp;
			stmp.insert(i);
			mdata.insert(make_pair(temp, stmp));
		}
		else {
			mdata[temp].insert(i);
		}
		vdata[i] = temp;
	}

	string op;
	while (cin >> op) {
		if (op == "findmin") {
			int val;
			cin >> val;
			
			auto p = mdata.upper_bound(val);
			cout << *(p->second.begin()) << "\n";
		}
		else if (op == "decrease") {
			int i, j;
			cin >> i >> j;
			mdata[vdata[i]].erase(i);
			vdata[i] -= j;
			mdata[vdata[i]].insert(i);
		}
	}

	return 0;
}