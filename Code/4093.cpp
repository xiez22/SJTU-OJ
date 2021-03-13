#include <iostream>
using namespace std;

const int MAX = 200001;
int n, m;
struct candy {
	int ai = 0;
	int bi = 0;
}c[MAX];

long long nums[MAX] = { 0 };

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		cin >> c[i].ai;
		cin >> c[i].bi;
		nums[c[i].bi] += c[i].ai;
	}
	long long ans = 0;

	for (long long i = MAX - 1; i >= 0; --i) {
		if (n > nums[i]) {
			ans += nums[i] * i;
			n -= nums[i];
		}
		else {
			ans += n * i;
			break;
		}
	}
	cout << ans;
	return 0;
}