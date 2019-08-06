#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<string> ans(n, "-1");
	stack<pair<int, pair<int, string>>> sdata;

	for (int i = 0; i < n; ++i) {
		int val;
		string name;
		cin >> val;
		cin.get();
		getline(cin, name);

		for (; !sdata.empty() && val > sdata.top().second.first;) {
			ans[sdata.top().first] = name;
			sdata.pop();
		}
		sdata.push(make_pair(i, make_pair(val, name)));
	}

	for (auto& p : ans)
		cout << p << "\n";
	return 0;
}