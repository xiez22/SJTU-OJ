#include "iostream"
#include "cstdio"
#include "cmath"
#include "cstring"
using namespace std;


constexpr int mod = 500009;

class type {
public:
	int key = 0;
	long long val = 0;
};

type hash_map[mod];

int map_find(int key) {
	int ans = key % mod;
	for (; hash_map[ans].key != key; ans = (ans + 1) % mod) {
		if (hash_map[ans].key == 0) {
			hash_map[ans].key = key;
			break;
		}
	}
	return ans;
}

int st_data[100009][20] = { 0 };

int gcd(int a, int b) {
	if (a % b == 0)
		return b;
	else
		return gcd(b, a % b);
}

int get_gcd(int from, int to) {
	int k = int(log(to - from) / log(2));
	return gcd(st_data[from][k], st_data[to - (1 << k)][k]);
}

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; ++i)
		scanf("%d", &st_data[i][0]);

	for (int j = 1; j <= int(log(n) / log(2)); ++j) {
		for (int i = 0; i + (1 << j) <= n; ++i) {
			st_data[i][j] = gcd(st_data[i][j - 1], st_data[i + (1 << (j - 1))][j - 1]);
		}
	}

	//Ìî±í
	for (int i = 0; i < n; ++i) {
		//int cur_gcd = get_gcd(i, i + 1);
		for (int cur_pos = i; cur_pos < n;) {
			int cur_gcd = get_gcd(i, cur_pos + 1);
			//¶þ·Ö
			long long ans = 0;
			int left = cur_pos + 1, right = n;
			int right_ans = 0;
			while (left <= right) {
				int mid = (left + right) >> 1;
				int cur_ans = get_gcd(i, mid);
				if (cur_ans == cur_gcd) {
					left = mid + 1;
					right_ans = mid;
				}
				else
					right = mid - 1;
			}
			hash_map[map_find(cur_gcd)].val += (long long)(right_ans - cur_pos);
			cur_pos = right_ans;
		}
	}

	int q;
	scanf("%d", &q);

	for (; q > 0; --q) {
		int x;
		scanf("%d", &x);
		printf("%lld\n", hash_map[map_find(x)].val);
	}

	return 0;
}