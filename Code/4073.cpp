#include "iostream"
#include "cmath"
#include "cstdio"
#include "cstring"
using namespace std;

constexpr long long max_size = 2000009LL;

class node {
public:
	bool visited = false;
	long long key = 0;
	long long value = 0;
};

long long val_data[200009] = { 0 };
node hash_map[max_size];

int get_pos(long long key) {
	long long ans = (key + (long long)(1e12)) % max_size;
	for (;; ans = (ans + 1) % max_size) {
		if (hash_map[ans].visited) {
			if (hash_map[ans].key == key) {
				return ans;
			}
		}
		else {
			hash_map[ans].visited = true;
			hash_map[ans].key = key;
			return ans;
		}
	}
}

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; ++i)
		scanf("%lld", &val_data[i]);

	long long ans = 0;
	//第一次循环
	long long cur_remain = val_data[0];
	for (int i = 0; i < n - 1; ++i) {
		++hash_map[get_pos(cur_remain)].value;
		if (cur_remain)
			++ans;
		cur_remain += val_data[i + 1];
	}

	//轮换
	long long cur_move = 0;
	for (int i = 0; i < n; ++i) {
		--hash_map[get_pos(val_data[i] + cur_move)].value;
		cur_move += val_data[i];
		++hash_map[get_pos(-val_data[i] + cur_move)].value;
		long long cur_ans = n - 1 - hash_map[get_pos(cur_move)].value;
		ans = cur_ans < ans ? cur_ans : ans;
	}

	cout << ans;

	return 0;
}