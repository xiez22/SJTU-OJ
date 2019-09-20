#include "iostream"
using namespace std;
int weight[1009] = { 0 }, value[1009] = { 0 },dp_data[10009] = { 0 };
int dp(int v, int n) {
	if (dp_data[v] > 0) return dp_data[v];
	int ans = 0;
	for (int i = 0; i < n; ++i) 
		if (weight[i] <= v) {
			auto temp = dp(v - weight[i], n) + value[i];
			ans = temp > ans ? temp : ans;
		}
	dp_data[v] = ans;
	return ans;
}
int main() {
	int v, n;
	cin >> v >> n;
	for (int i = 0; i < n; ++i)
		cin >> weight[i] >> value[i];
	cout << dp(v, n);
	return 0;
}