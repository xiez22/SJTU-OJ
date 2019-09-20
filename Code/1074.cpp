#include "iostream"
#include "cstdio"
using namespace std;

bool ground[1240][1240] = { 0 };
int sum[1240][1240] = { 0 };

int main() {
	int N, M;
	cin >> N >> M;

	for (int i = 1; i <= N; ++i) {
		sum[i][0] = sum[i - 1][1];
		for (int j = 1; j <= M; ++j) {
			while (true) {
				char c;
				scanf("%c", &c);
				if (c == 'X') {
					ground[i][j] = true;
					sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + 1;
					break;
				}
				else if (c == '-') {
					sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
					break;
				}
			}
		}
	}

	int cur_max = 0;
	for (int i = 1; i <= N; ++i) {
		for (int j = cur_max * 2; j <= M; ++j) {
			for (int k = cur_max; j >= k * 2 && i >= k; ++k) {
				if (sum[i][j] - sum[i][j - k * 2] - sum[i - k][j] + sum[i - k][j - k * 2] == 0) {
					cur_max = k;
				}
				else
					break;
			}
		}
	}

	cout << cur_max * cur_max * 2;

	return 0;
}