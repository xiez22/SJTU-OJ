#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;

long long dp_data[500009] = { 0 };
long long cal_num[500009] = { 0 };

long long dp(long long num, long long T) {
	if (dp_data[num] > 0)
		return dp_data[num];
	if (num > T) {
		return 0;
	}

	long long ans = 0;
	for (long long i = 1; i <= 100; ++i) {
		if (num * i % 100 == 0) {
			long long cur_ans = dp(num * i / 100 + num, T) + 1;
			ans = cur_ans > ans ? cur_ans : ans;
		}
	}
	for (long long i = 1; i <= 100; ++i) {
		if (num * i % 100 == 0) {
			if (dp_data[num + num * i / 100] + 1 == ans) {
				cal_num[num] += cal_num[num + num * i / 100];
			}
		}
	}
	if (ans == 1)
		cal_num[num] = 1;
	dp_data[num] = ans;
	return ans;
}

int main() {
	long long S, T;
	cin >> S >> T;

	long long ans = 0;
	for (long long i = S; i <= T; ++i) {
		long long cur_ans = dp(i, T);
		ans = cur_ans > ans ? cur_ans : ans;
	}

	long long cnt = 0;
	for (long long i = S; i <= T; ++i) {
		if (dp(i, T) == ans) {
			cnt += cal_num[i];
		}
	}

	cout << ans << endl << cnt;

	return 0;
}