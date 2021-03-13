#include "iostream"
#include "cstdio"
using namespace std;

bool map[509][509] = { 0 };
int dx[] = { 0,1,0,-1 },
dy[] = { 1,0,-1,0 };
int n, m;
void dfs(int x, int y) {
	map[x][y] = false;
	for (int i = 0; i < 4; ++i) {
		if (x + dx[i] >= 0 && x + dx[i] < n && y + dy[i] >= 0 && y + dy[i] < m && map[x + dx[i]][y + dy[i]])
			dfs(x + dx[i], y + dy[i]);
	}
}

int main() {
	scanf("%d %d", &n, &m);

	for(int i=0;i<n;++i)
		for (int j = 0; j < m; ++j) {
			int temp;
			scanf("%d", &temp);
			map[i][j] = (bool)(temp + 1);
		}

	int cnt = 0;
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
			if (map[i][j]) {
				++cnt;
				dfs(i, j);
			}

	cout << cnt;

	return 0;
}