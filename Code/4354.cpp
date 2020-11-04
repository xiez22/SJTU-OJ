#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	string s;
	cin >> s;

	string output = "";
	vector<size_t> sp;

	auto length = s.length();
	for (size_t i = 0; i < length; ++i) {
		if (s[i] >= '0' && s[i] <= '9')
			continue;
		else if (s[i] == '(') {
			sp.emplace_back(output.length());
		}
		else if (s[i] == ')') {
			reverse(output.begin() + sp.back(), output.end());
			sp.pop_back();
		}
		else
		{
			output += s[i];
		}
	}

	cout << output;

	return 0;
}