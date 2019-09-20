#include "iostream"
#include "cmath"
#include "cstdio"
using namespace std;

long long jc[100009] = { 0 };
constexpr long long mod = (long long)(1e9 + 7);

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

int main() {
	int t;
	scanf("%d", &t);
	//¼ÆËã½×³Ë
	jc[0] = 1;
	for (long long i = 1; i <= 100005; ++i) {
		jc[i] = (jc[i - 1] * i) % mod;
	}
	for (; t > 0; --t) {
		long long n, m;
		scanf("%lld %lld", &n, &m);
		long long temp = (jc[m] * jc[n - m]) % mod;
		temp = fast_pow(temp, mod - 2);
		temp = (jc[n] * temp) % mod;
		printf("%lld\n", temp);
	}

	return 0;
}