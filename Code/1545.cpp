#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
using namespace std;

int n, m, k;
bool visited[1009][1009] = { 0 };
int ops[10009][4] = { 0 };

int cx, cy, r;

int dx[] = { 0,1,0,-1 },
dy[] = { 1,0,-1,0 };

bool check_av(int x, int y) {
	return (x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m >> k;

	for (int i = 0; i < k; ++i) {
		cin >> cx >> cy >> r;
		--cx;
		--cy;
		ops[i][0] = cx;
		ops[i][1] = cy;
		ops[i][2] = r;
		char temp[10];
		cin >> temp;
		if (temp[0] == 'R') {
			ops[i][3] = 1;
		}
		else if (temp[0] == 'G') {
			ops[i][3] = 2;
		}
		else {
			ops[i][3] = 3;
		}
	}

	int cnt[4] = { 0 };
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int color = 0;
			for (int a = k - 1; a >= 0; --a) {
				cx = ops[a][0], cy = ops[a][1], r = ops[a][2];
				if (check_av(i, j)) {
					color = ops[a][3];
					break;
				}
			}
			++cnt[color];
		}
	}

	cout << "Red:" << cnt[1] << endl << "Green:" << cnt[2] << endl << "Blue:" << cnt[3];

	return 0;
}