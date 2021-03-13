#include "iostream"
#include "cstdio"
using namespace std;

int time_val[109], val[109];
int dp_data[109][1009] = { 0 };

int dp(int num, int v) {
	if (num == 0)
		return 0;
	if (dp_data[num][v] > 0)
		return dp_data[num][v];
	if (time_val[num - 1] > v) {
		dp_data[num][v] = dp(num - 1, v);
		return dp_data[num][v];
	}
	else {
		int ans1 = dp(num - 1, v), ans2 = dp(num - 1, v - time_val[num - 1]) + val[num - 1];
		dp_data[num][v] = ans1 > ans2 ? ans1 : ans2;
		return dp_data[num][v];
	}
}

int main() {
	int T, M;
	cin >> T >> M;

	for (int i = 0; i < M; ++i)
		scanf("%d %d", &time_val[i], &val[i]);

	cout << dp(M, T);

	return 0;
}