#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

struct my_type {
	int key = 0;
	long long val = 0;
};


const int mod = 300009;
my_type hash_map[mod];
int insert(int key) {
	int ans = key % mod;
	for (; hash_map[ans].key != key; ans = (ans + 1) % mod) {
		if (hash_map[ans].key == 0) {
			hash_map[ans].key = key;
			break;
		}
	}
	return ans;
}

int gcd(int a, int b) {
	if (a % b == 0)
		return b;
	else
		return gcd(b, a % b);
}

int st_data[100009][20] = { 0 };

int getgcd(int from, int to) {
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

	for (int i = 0; i < n; ++i) {
		for (int cur_pos = i; cur_pos < n;) {

			int cur_gcd = getgcd(i, cur_pos + 1);
			long long ans = 0;
			int left = cur_pos + 1, right = n;
			int right_ans = 0;
			while (left <= right) {
				int mid = (left + right) /2;
				int cur_ans = getgcd(i, mid);
				if (cur_ans == cur_gcd) {
					left = mid + 1;
					right_ans = mid;
				}
				else
					right = mid - 1;
			}
			hash_map[insert(cur_gcd)].val += (long long)(right_ans - cur_pos);
			cur_pos = right_ans;
		}
	}

	int q;
	scanf("%d", &q);

	for (; q > 0; --q) {
		int x;
		scanf("%d", &x);
		printf("%lld\n", hash_map[insert(x)].val);
	}

	return 0;
}