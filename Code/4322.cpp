#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
using ull = unsigned long long;
constexpr auto mod = 203ull;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, k;
	cin >> n >> k;

	unordered_map<ull, int> rdata, ldata;
	int zero_num = 0;

	for (int i = 0; i < n; ++i) {
		ull rcode = 0ull, lcode = 0ull;
		int fnum;
		cin >> fnum;
		for (int j = 1; j < k; ++j) {
			int tmp;
			cin >> tmp;
			rcode = rcode * mod + ull(100 + tmp - fnum);
			lcode = lcode * mod + ull(100 + fnum - tmp);
		}
		if (rcode == lcode) {
			zero_num++;
			continue;
		}

		if (rdata.find(rcode) == rdata.end()) {
			rdata[rcode] = 1;
		}
		else
		{
			rdata[rcode]++;
		}

		if (ldata.find(lcode) == ldata.end()) {
			ldata[lcode] = 1;
		}
		else
		{
			ldata[lcode]++;
		}
	}

	int ans = 0;
	for (auto p : rdata) {
		if (ldata.find(p.first) != ldata.end()) {
			ans += p.second * ldata[p.first];
		}
	}
	ans /= 2;
	ans += zero_num * (zero_num - 1) / 2;

	cout << ans;

	return 0;
}
