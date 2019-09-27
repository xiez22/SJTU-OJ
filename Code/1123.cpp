//TLE - 30

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;
constexpr int mod = 100007;

vector<pii> pdata;
vector<vector<vi>> dp_data;

int n;

int dp(int pos, int k, bool dir, bool isfirst = false) {
	if (k < 0)
		return 0;
	if (dp_data[pos][k][dir])
		return dp_data[pos][k][dir];
	

	int ans = 0;
	if (k == 0)
		ans = 1;
	for (int nxt = pos + 1; nxt < n; ++nxt) {
		if (pdata[nxt].second < pdata[pos].second) {
			if (dir || isfirst)
				ans = (ans + dp(nxt, k - 1, false)) % mod;
			else
				ans = (ans + dp(nxt, k, false)) % mod;
		}
		else {
			if (!dir || isfirst)
				ans = (ans + dp(nxt, k - 1, true)) % mod;
			else
				ans = (ans + dp(nxt, k, true)) % mod;
		}
	}
	return dp_data[pos][k][dir] = ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int k;
	cin >> n >> k;

	pdata.resize(n);
	dp_data.resize(n, vector<vi>(k + 1, vi(2, 0)));

	for (int i = 0; i < n; ++i)
		cin >> pdata[i].first >> pdata[i].second;

	sort(pdata.begin(), pdata.end(), [](pii a, pii b) {return a.first < b.first; });
	cout << dp(0, k, false, true);

	return 0;
}