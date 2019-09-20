#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
using namespace std;

char map_data[59][59] = { 0 };
bool visited[59][59] = { 0 };

int lx[2509] = { 0 }, ly[2509] = { 0 };

int dx[] = { 0,1,0,-1 },
dy[] = { 1,0,-1,0 };

int n, m;

int dfs(int start_x, int start_y) {
	visited[start_x][start_y] = true;
	int ans = 0;
	if (map_data[start_x][start_y] == '.')
		++ans;
	for (int i = 0; i < 4; ++i) {
		auto next_x = start_x + dx[i],
			next_y = start_y + dy[i];
		if (next_x >= 0 && next_x < n && next_y >= 0 && next_y < m &&
			map_data[next_x][next_y] != '#' && !visited[next_x][next_y]) {
			ans += dfs(next_x, next_y);
		}
	}
	return ans;
}

int main() {
	int land_cnt = 0, l_cnt = 0;
	int start_x = 0, start_y = 0;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("\n");
		for (int j = 0; j < m; ++j) {
			scanf("%c", &map_data[i][j]);
			if (map_data[i][j] == '.') {
				if (land_cnt == 0) {
					start_x = i;
					start_y = j;
				}
				++land_cnt;
			}
			else if (map_data[i][j] == '?') {
				lx[l_cnt] = i;
				ly[l_cnt] = j;
				++l_cnt;
			}
		}
	}

	auto visited_land = dfs(start_x, start_y);
	if (visited_land < land_cnt) {
		printf("Impossible");
		return 0;
	}
	for (int i = 0; i < l_cnt; ++i) {
		//判断是否未访问到
		if (!visited[lx[i]][ly[i]]) {
			map_data[lx[i]][ly[i]] = '#';
		}
	}
	for (int i = 0; i < l_cnt; ++i) {
		if (!visited[lx[i]][ly[i]])
			continue;
		//修改
		map_data[lx[i]][ly[i]] = '#';
		memset(visited, 0, sizeof(visited));
		visited_land = dfs(start_x, start_y);
		if (visited_land == land_cnt) {
			printf("Ambiguous");
			return 0;
		}
		map_data[lx[i]][ly[i]] = '?';
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (map_data[i][j] == '?')
				printf(".");
			else
				printf("%c", map_data[i][j]);
		}
		printf("\n");
	}

	return 0;
}