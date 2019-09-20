#include <iostream>
#include <cstring>
using namespace std;

int map_data[109][109] = { 0 };

int dx[] = { 0,1,0,-1 },
dy[] = { 1,0,-1,0 };
int n;

bool visited[109][109] = { 0 };
int max_h = 0;

bool dfs(int posx, int posy, int cur_max, int cur_min) {
	visited[posx][posy] = true;
	if (cur_max == -1) {
		cur_max = cur_min = map_data[posx][posy];
	}
	else {
		cur_max = map_data[posx][posy] > cur_max ? map_data[posx][posy] : cur_max;
		cur_min = map_data[posx][posy] < cur_min ? map_data[posx][posy] : cur_min;
	}
	if (cur_max - cur_min > max_h) {
		visited[posx][posy] = false;
		return false;
	}
	if (posx == n - 1 && posy == n - 1)
		return true;

	for (int i = 0; i < 4; ++i) {
		int nx = posx + dx[i], ny = posy + dy[i];
		if (!visited[nx][ny] && nx >= 0 && nx < n && ny >= 0 && ny < n) {
			auto flag = dfs(nx, ny, cur_max, cur_min);
			if (flag) {
				visited[posx][posy] = false;
				return true;
			}
		}
	}
	visited[posx][posy] = false;
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;

	int h_min = 200, h_max = 0;

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			cin >> map_data[i][j];
			h_min = map_data[i][j] < h_min ? map_data[i][j] : h_min;
			h_max = map_data[i][j] > h_max ? map_data[i][j] : h_max;
		}
	
	int left = 0, right = h_max - h_min, right_ans = -1;
	
	while (left <= right) {
		auto mid = (left + right) >> 1;
		max_h = mid;
		
		memset(visited, 0, sizeof(visited));
		if (dfs(0, 0, -1, -1)) {
			right_ans = mid;
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	
	cout << right_ans;

	return 0;
}