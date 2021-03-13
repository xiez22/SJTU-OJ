#include "iostream"
#include "cmath"
#include "cstring"
using namespace std;

long long val_num[50] = { 0 };

int main() {
	long long n, k;
	cin >> n >> k;

	long long cnt = 0, num = 0;
	for (long long temp = n; temp; temp >>= 1, ++num) {
		if (temp & 1) {
			++cnt;
			val_num[num] = 1;
		}
	}
	num = 40;
	long long ans = 0;
	if (k >= n) {
		ans = k - n;
	}
	else if (k >= cnt) {
		ans = 0;
	}
	else {
		for (;;) {
			long long a = 0, b = 0;
			for (; a < num && val_num[a] == 0; ++a);
			val_num[a] = 0;
			for (; b < num && val_num[b] == 0; ++b);
			val_num[b] = 0;
			ans += (long long)(pow(2, b) - pow(2, a));
			for (++b, ++val_num[b]; b < num; ++b) {
				if (val_num[b] > 1) {
					val_num[b] = 0;
					++val_num[b + 1];
				}
				else
					break;
			}
			//统计个数
			int cur_cnt = 0;
			for (int i = 0; i < num; ++i)
				if (val_num[i])
					++cur_cnt;
			if (cur_cnt <= k) {
				//ans += k - cur_cnt;
				break;
			}
		}
	}

	cout << ans;

	return 0;
}