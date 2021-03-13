#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;
using pic = pair<int, char>;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	string ch;
	while (cin >> ch) {
		stack<pic> sdata;
		auto length = ch.length();
		vector<char> vdata(length, ' ');

		for (int i = 0; i < length; ++i) {
			if (ch[i] == '(') {
				sdata.push(make_pair(i, '('));
			}
			else if (ch[i] == ')') {
				if (!sdata.empty() && sdata.top().second == '(') {
					sdata.pop();
				}
				else{
					sdata.push(make_pair(i,')'));
				}
			}
		}

		while (!sdata.empty()) {
			vdata[sdata.top().first] = sdata.top().second == '(' ? '$' : '?';
			sdata.pop();
		}
		cout << ch << "\n";
		for (auto p : vdata)
			cout << p;
		cout << "\n";
	}

	return 0;
}