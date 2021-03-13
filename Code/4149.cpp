#include "iostream"
#include "cstdio"
using namespace std;

constexpr int max_num = 20000000;

bool remain[max_num] = { 0 };

int main() {
	long long n, m, k;
	cin >> n >> m >> k;

	long long cnt = n, cur_pos = 0;
	for (; k > 0; --k) {
		long long dis = m % cnt;
		if (dis == 0)
			dis = cnt;
		for (long long i = 0; i < dis;) {
			++cur_pos;
			if (cur_pos > n)
				cur_pos = 1;
			if (!remain[cur_pos]) {
				++i;
			}
		}
		remain[cur_pos] = true;
	}

	cout << cur_pos;

	return 0;
}