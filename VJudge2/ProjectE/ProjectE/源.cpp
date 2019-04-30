#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

const long long mod = (long long)(1e9 + 7);
const long long max_num = (long long)(1000009);

class type {
public:
	long long key = -1;
	long long val = 0;
};

type hash_map[max_num];
char temp[1000009];

long long get_pos(long long key) {
	long long ans = key % max_num;
	for (; key != hash_map[ans].key; ans = (ans + 1LL) % max_num) {
		if (hash_map[ans].key == -1) {
			hash_map[ans].key = key;
			return ans;
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> temp;
		int length = strlen(temp);
		long long cnt = 0;
		long long ch_num[26] = { 0 };
		long long cur_hash = 0;
		for (int j = 0; j < length; ++j) {
			if (ch_num[temp[j] - 'a'] == 0) {
				ch_num[temp[j] - 'a'] = ++cnt;
			}
			cur_hash = (cur_hash * 31LL + ch_num[temp[j] - 'a']) % mod;
		}
		++hash_map[get_pos(cur_hash)].val;
	}

	long long ans = 0;
	for (int i = 0; i < max_num; ++i) {
		if (hash_map[i].key != -1) {
			auto val = hash_map[i].val;
			ans += val * (val - 1) / 2;
		}
	}

	cout << ans;

	return 0;
}