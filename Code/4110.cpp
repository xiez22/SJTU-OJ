#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	cin.get();

	vector<string> val_data(n);
	for (int i = 0; i < n; ++i) {
		getline(cin, val_data[i]);
	}

	sort(val_data.begin(), val_data.end());

	for (auto& p : val_data)
		cout << p << "\n";

	return 0;
}