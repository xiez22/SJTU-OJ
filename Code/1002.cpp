#include "iostream"
#include "cstdio"
using namespace std;

int hs[1009][1009] = { 0 };

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int L, W;
	cin >> L >> W;

	for (int i = 1; i <= L; ++i) {
		for (int j = 1; j <= W; ++j) {
			int temp;
			cin >> temp;
			hs[i][j] = hs[i][j - 1] + hs[i - 1][j] - hs[i - 1][j - 1] + temp;
		}
	}
	int cur_ans = 0;
	int a, b;
	cin >> a >> b;
	for (int i = 0; i + a <= L; ++i) {
		for (int j = 0; j + b <= W; ++j) {
			if (hs[i + a][j + b] - hs[i][j + b] - hs[i + a][j] + hs[i][j] > cur_ans)
				cur_ans = hs[i + a][j + b] - hs[i][j + b] - hs[i + a][j] + hs[i][j];
		}
	}

	cout << cur_ans;

	return 0;
}