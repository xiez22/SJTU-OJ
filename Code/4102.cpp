#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	uint32_t n, k;
	cin >> k >> n;

	multiset<uint32_t> sdata;
	vector<uint32_t> vdata(n);
	uint32_t cur_ans = 0u;
	for (uint32_t i = 0u, cur_left = 0u; i < n; ++i) {
		cin >> vdata[i];
		sdata.insert(vdata[i]);
		for (; *sdata.rbegin() - *sdata.begin() > k; sdata.erase(sdata.find(vdata[cur_left++])));
		cur_ans = i - cur_left + 1u > cur_ans ? i - cur_left + 1u : cur_ans;
	}

	cout << cur_ans;

	return 0;
}