#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

vector<vector<int>> map_data;
map<int,vector<pair<int,int>>> ele_data;
int n, sx, sy, tx, ty;

int dx[] = { 0,1,0,-1 },
dy[] = { 1,0,-1,0 };

int bfs() {
	queue <pair<pair<int, int>, int>> qdata;
	vector<vector<bool>> visited(n, vector<bool>(n, false));
	qdata.push(make_pair(make_pair(sx, sy), 0));
	visited[sx][sy] = true;

	while (!qdata.empty()) {
		auto temp = qdata.front();
		qdata.pop();
		if (temp.first.first == tx && temp.first.second == ty) {
			return temp.second;
		}
		int cx = temp.first.first, cy = temp.first.second;
		for (int i = 0; i < 4; ++i) {
			int nx = temp.first.first + dx[i], ny = temp.first.second + dy[i];
			if (nx < n && ny < n && nx >= 0 && ny >= 0 && !visited[nx][ny] && map_data[nx][ny] >= 0) {
				qdata.push(make_pair(make_pair(nx, ny), temp.second + 1));
				visited[nx][ny] = true;
			}
		}
		if (map_data[cx][cy] > 0) {
			int nx, ny;
			if (ele_data[map_data[cx][cy]][0].first == cx && ele_data[map_data[cx][cy]][0].second == cy) {
				nx = ele_data[map_data[cx][cy]][1].first;
				ny = ele_data[map_data[cx][cy]][1].second;
			}
			else {
				nx = ele_data[map_data[cx][cy]][0].first;
				ny = ele_data[map_data[cx][cy]][0].second;
			}
			if (!visited[nx][ny]) {
				qdata.push(make_pair(make_pair(nx, ny), temp.second + 1));
				visited[nx][ny] = true;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> sx >> sy >> tx >> ty;
	--sx, --sy, --tx, --ty;

	map_data.resize(n, vector<int>(n));

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> map_data[i][j];
			if (map_data[i][j] > 0) {
				if (ele_data.find(map_data[i][j]) == ele_data.end()) {
					ele_data.insert(make_pair(map_data[i][j], vector<pair<int, int>>(1, make_pair(i, j))));
				}
				else {
					ele_data[map_data[i][j]].emplace_back(make_pair(i, j));
				}
			}
		}
	}

	cout << bfs();

	return 0;
}