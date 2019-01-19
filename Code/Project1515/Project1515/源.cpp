//Written by LCK

#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

int m, n;
int ans = 1e6;
int map[1000][1000] = { 0 };
int sx, sy, ex, ey;
int step[1000][1000] = { 0 };
int a[1000000] = { 0 }, b[1000000] = { 0 };
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int cnt = -1;
class node {
public:
	int x;
	int y;
};
class shop {
public:
	int x;
	int y;
} sh[1000000] = { 0,0 };

void bfs(node s) {
	queue<node> que;
	que.push(s);
	node nw, nxt;
	while (!que.empty()) {
		nw = que.front();
		que.pop();
		for (int i = 0; i < 4; ++i) {
			nxt.x = nw.x + dx[i];
			nxt.y = nw.y + dy[i];

			if (nxt.x >= 0 && nxt.x < m&&nxt.y >= 0 && nxt.y < n&&step[nxt.x][nxt.y] == 0 && map[nxt.x][nxt.y] != 1) {
				step[nxt.x][nxt.y] = step[nw.x][nw.y] + 1;
				que.push(nxt);
			}
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j) {
			cin >> map[i][j];
			if (map[i][j] == 2) { sx = i; sy = j; }
			if (map[i][j] == 3) { ex = i; ey = j; }
			if (map[i][j] == 4) {
				cnt++;
				sh[cnt].x = i;
				sh[cnt].y = j;
			}
		}
	node s = { sx,sy };
	bfs(s);
	for (int i = 0; i <= cnt; ++i) {
		a[i] = step[sh[i].x][sh[i].y];
	}
	memset(step, 0, sizeof(step));
	node e = { ex,ey };
	bfs(e);
	for (int i = 0; i <= cnt; ++i) {
		b[i] = step[sh[i].x][sh[i].y];
	}
	int tmp;
	for (int i = 0; i <= cnt; ++i) {
		if (a[i] > 0 && b[i] > 0) {
			tmp = a[i] + b[i];
			ans = min(ans, tmp);
		}
	}
	cout << ans;
	return 0;
}
