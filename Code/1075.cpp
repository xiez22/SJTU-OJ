#include "iostream"
#include "cstdio"
#include "cmath"
#include "cstring"
using namespace std;

constexpr long long mod = 19301;
long long tree_num[3350] = { 0 };

long long jc[3350] = { 0 };

long long fast_pow(long long a, long long b) {
	long long ans = 1, base = a;
	while (b) {
		if (b & 1)
			ans = (ans * base) % mod;
		base = (base * base) % mod;
		b >>= 1;
	}
	return ans;
}

long long get_zhs(int n, int m) {
	long long temp = (jc[m] * jc[n - m]) % mod;
	temp = fast_pow(temp, mod - 2);
	temp = (jc[n] * temp) % mod;
	return temp;
}

long long cal_tree(int n) {
	if (n == 0)
		return 1LL;
	if (tree_num[n] > 0)
		return tree_num[n];
	long long ans = 0;
	for (int i = 0; i < n; ++i) {
		ans = (ans + cal_tree(n - i - 1) * cal_tree(i)) % mod;
	}
	tree_num[n] = ans;
	return ans;
}

int main() {
	jc[0] = 1;
	for (long long i = 1LL; i <= 3350LL; ++i) {
		jc[i] = (jc[i - 1] * i) % mod;
	}
	long long n;
	cin >> n;
	
	long long ans = 0;
	for (int i = 0; i <= n; i += 2) {
		ans = (ans + get_zhs(n, i) * cal_tree(i / 2)) % mod;
	}

	cout << ans;

	return 0;
}