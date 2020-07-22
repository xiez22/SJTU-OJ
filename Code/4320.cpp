#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long sol(vector<long long> num) {
	int n = num.size();
	vector<long long> dp_data(n + 1, 0);

	long long ans = -1e9;
	for (int i = 0; i < n; ++i) {
		dp_data[i + 1] = max(dp_data[i] + num[i], num[i]);
		ans = max(ans, dp_data[i + 1]);
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<long long> num(n);
	for (int i = 0; i < n; ++i) {
		cin >> num[i];
	}

	vector<long long> num1, num2;
	for (int i = 0; i + 1 < n; i += 2) {
		num1.emplace_back(num[i] + num[i + 1]);
	}
	for (int i = 1; i + 1 < n; i += 2) {
		num2.emplace_back(num[i] + num[i + 1]);
	}

	cout << max(sol(num1), sol(num2));

	return 0;
}