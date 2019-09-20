#include "iostream"
#include "cstring"
using namespace std;

constexpr int mod = 1000009;

class type {
public:
	int key = -99999999;
	int val = 0;
};

int val_data[509][4] = { 0 };
type hash_map[mod];

int get_pos(int key) {
	int ans = (key + 2000009) % mod;
	for (; hash_map[ans].key != key; ans = (ans + 1) % mod) {
		if (hash_map[ans].key <= -99999999) {
			hash_map[ans].key = key;
			break;
		}
	}
	return ans;
}

int main() {
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 4; ++j)
			scanf("%d", &val_data[i][j]);
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			++hash_map[get_pos(val_data[i][0] + val_data[j][1])].val;
		}
	}

	int ans = 0;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			ans += hash_map[get_pos(-val_data[i][2] - val_data[j][3])].val;
		}
	}

	cout << ans;

	return 0;
}