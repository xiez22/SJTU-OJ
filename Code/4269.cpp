#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

bool is_ans(int input) {
	string a = to_string(input);
	int length = a.length();
	for (int i = 0; i < length; ++i) {
		if (a[i] != a[length - i - 1])
			return false;
	}
	return true;
}

int next_n(int input) {
	string a = to_string(input);
	reverse(a.begin(), a.end());
	return stoi(a) + input;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;

	while (cin >> n) {
		int o_n = n;
		vector<int> nxt_ans;
		while (!is_ans(n)) {
			n = next_n(n);
			nxt_ans.emplace_back(n);
		}

		cout << nxt_ans.size() << endl << o_n;
		for (auto p : nxt_ans)
			cout << "--->" << p;
		cout << endl;
	}

	return 0;
}