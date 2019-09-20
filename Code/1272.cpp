#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<int> vdata(n);
	unordered_map<int, bool> mdata;
	
	for (int i = 0; i < n; ++i) {
		cin >> vdata[i];
		mdata.insert(make_pair(vdata[i], true));
	}
	
	for (int i = 0; i < vdata.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			int ans = vdata[i] > vdata[j] ? vdata[i] / vdata[j] : vdata[j] / vdata[i];
			if (mdata.find(ans) == mdata.end()) {
				vdata.emplace_back(ans);
				mdata.insert(make_pair(ans, true));
			}
		}
	}

	cout << vdata.size();

	return 0;
}