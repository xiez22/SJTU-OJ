#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	unordered_map<int, bool> mdata;
	for (; n; --n) {
		int temp;
		cin >> temp;
		mdata.insert(make_pair(temp, true));
	}

	int m;
	cin >> m;
	for (; m; --m) {
		int temp;
		cin >> temp;
		if (mdata.find(temp) != mdata.end())
			cout << "Y\n";
		else
			cout << "N\n";
	}

	return 0;
}