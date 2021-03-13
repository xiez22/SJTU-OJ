#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;
	int len = min(n, m);

	vector<int> lcp(len, 0);
	string A, B;
	cin >> A >> B;

	int cur_pos = 0;
	for (; cur_pos < len && A[cur_pos] == B[cur_pos]; ++cur_pos);
	lcp[0] = cur_pos;

	int q;
	cin >> q;

	for (; q > 0; --q) {
		int a, b;
		char c;
		cin >> a >> b;
		cin.get();
		cin >> c;
		if (b > len)
			continue;
		if (a == 0)
			A[b - 1] = c;
		else
			B[b - 1] = c;

		--b;
		for (cur_pos = 0; lcp[cur_pos] <= b; cur_pos = lcp[cur_pos]);
		if (A[b] != B[b]) {

		}
	}

	return 0;
}