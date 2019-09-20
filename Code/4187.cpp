#include "iostream"
using namespace std;

int main() {
	int n = 0;
	unsigned int ans[100] = { 0 };
	cin >> n;
	if (n <= 0 || n > 50) {
		cout << "error!";
		return 0;
	}
	ans[1] = 0;
	ans[2] = 1;
	for (int i = 3; i <= n; i++) {
		ans[i] = ans[i - 2] + ans[i - 1];
	}
	cout << ans[n];

	return 0;
}