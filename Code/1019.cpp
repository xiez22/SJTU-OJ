#include "iostream"
#include "cstdio"
#include "cstring"
#include "stack"
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		stack<char> stack_data;
		char temp[109];
		cin >> temp;
		int length = strlen(temp);
		for (int j = 0; j < length; ++j) {
			if (temp[j] == '(')
				stack_data.push('(');
			else if (!stack_data.empty() && stack_data.top() == '(')
				stack_data.pop();
			else
				stack_data.push(')');
		}
		if (stack_data.empty())
			cout << "YES" << "\n";
		else
			cout << "NO" << "\n";
	}

	return 0;
}