#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <functional>
using namespace std;

typedef pair<int, int> pii;

class type {
public:
	int t, a, d;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int m, n;
	cin >> m;
	vector<type> buy_data(m);
	
	for (int i = 0; i < m; ++i) {
		cin >> buy_data[i].t >> buy_data[i].a >> buy_data[i].d;
	}

	cin >> n;
	vector<pair<int, int>> val_data(n);
	for (int i = 0; i < n; ++i)
		cin >> val_data[i].first >> val_data[i].second;

	function<bool(const pii&,const pii&)> cmp = [](const pair<int, int>& a,const pair<int, int>& b) {
		return a.first < b.first;
	};

	sort(buy_data.begin(), buy_data.end(), [](type& a, type& b) {return a.t < b.t; });
	sort(val_data.begin(), val_data.end(), cmp);

	double ans = 0.0;
	for (int i = 0, j = 0; i < m; ++i) {
		for (; j < n - 1 && buy_data[i].t >= val_data[j + 1].first; ++j);
		if (buy_data[i].d == 1) {
			double cur_num = 100.0 * buy_data[i].a * val_data[j].second;
			ans -= cur_num * 0.002 > 5.0 ? cur_num * 0.002 : 5.0;
			ans -= 1.0 * buy_data[i].a / 10;
			ans -= 1.0;
			ans -= cur_num;
		}
		else {
			double cur_num = 100.0 * buy_data[i].a * val_data[j].second;
			ans -= cur_num * 0.002 > 5.0 ? cur_num * 0.002 : 5.0;
			ans -= 1.0 * buy_data[i].a / 10;
			ans -= 1.0;
			ans += cur_num;
			ans -= cur_num * 0.001;
		}
	}

	cout << fixed << setprecision(2) << ans;

	return 0;
}