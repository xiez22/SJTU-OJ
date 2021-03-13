#include "iostream"
#include "cstdio"
using namespace std;

constexpr long long mod = (long long)(1e9 + 7);

long long ans_data[1009] = { 0 };

int main() {
	ans_data[0] = 1;
	ans_data[1] = 1;
	long long num;
	cin >> num;
	for (long long i = 2; i <= num; ++i) {
		for (long long j = i; j >= 0; j -= 2)
			ans_data[i] = (ans_data[i] + ans_data[(i - j) / 2]) % mod;
	}
	cout << ans_data[num];

	return 0;
}