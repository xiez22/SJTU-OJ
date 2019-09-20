#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	
	vector<int> val(n);

	for (int i = 0; i < n; ++i) {
		cin >> val[i];
		int cnt = 0;
		for (int j = 0; j < i; ++j)
			if (val[j] < val[i])
				++cnt;
		cout << cnt << " ";
	}

	return 0;
}