#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

template <class T>
class my_queue {
public:
	T queue_[50000];
	int start = 0, end = 0;
	int mod = 50000;
	void clear() {
		start = 0;
		end = 0;
		memset(queue_, 0, sizeof(queue_));
	}
	bool empty() const {
		return end - start == 0;
	}
	T front() const {
		return queue_[start % mod];
	}
	void pop() {
		++start;
	}

	void push(const T& val) {
		queue_[(end++) % mod] = val;
	}
	int size() {
		return end - start;
	}
};

class position {
public:
	int distance = 0;
	int pos_x = 0, pos_y = 0;
	
	position() = default;
	position(int dis,int x,int y):distance(dis),pos_x(x),pos_y(y){}
};

int map_data[109][109] = { 0 };

bool visited[109][109] = { 0 };
int distance_data[8][109][109] = { 0 };

int dx[] = { 0,1,0,-1 },
dy[] = { 1,0,-1,0 };

int n, m;

my_queue<position> queue_data;
void bfs(int start_x, int start_y, int step) {
	queue_data.clear();
	memset(visited, 0, sizeof(visited));
	position start_point(0, start_x, start_y);
	queue_data.push(start_point);
	visited[start_x][start_y] = true;
	
	while (!queue_data.empty()) {
		auto temp = queue_data.front();
		queue_data.pop();
		distance_data[step][temp.pos_x][temp.pos_y] = temp.distance;
		for (int i = 0; i < 4; ++i) {
			if (temp.pos_x + dx[i] >= 0 && temp.pos_x + dx[i] < n &&
				temp.pos_y + dy[i] >= 0 && temp.pos_y + dy[i] < m &&
				!visited[temp.pos_x + dx[i]][temp.pos_y + dy[i]]
				&& map_data[temp.pos_x + dx[i]][temp.pos_y + dy[i]] != -1) {
				position next_point(temp.distance + 1, temp.pos_x + dx[i], temp.pos_y + dy[i]);
				queue_data.push(next_point);
				visited[next_point.pos_x][next_point.pos_y] = true;
			}
		}
	}
}

bool dfs_visited[10] = { 0 };
int box[8][2] = { 0 };
int box_num = 0;
int dfs(int step, int cur_num) {
	if (cur_num == box_num)
		return 0;
	dfs_visited[step] = true;
	int ans = 10000009;
	for (int i = 1; i <= box_num; ++i) {
		if (!dfs_visited[i]) {
			if (distance_data[step][box[i][0]][box[i][1]] == 0) {
				return -1;
			}
			int cur_ans = dfs(i, cur_num + 1);
			if (cur_ans < 0)
				return -1;
			cur_ans += distance_data[step][box[i][0]][box[i][1]];
			ans = cur_ans < ans ? cur_ans : ans;
		}
	}
	dfs_visited[step] = false;
	return ans;
}

int main() {
	scanf("%d %d", &n, &m);

	int start_x = 0, start_y = 0;
	

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			scanf("%d", &map_data[i][j]);
			if (map_data[i][j] == 2) {
				start_x = i;
				start_y = j;
			}
			else if (map_data[i][j] == 1) {
				box[box_num + 1][0] = i;
				box[box_num + 1][1] = j;
				++box_num;
			}
		}
	}

	bfs(start_x, start_y, 0);
	for (int i = 1; i <= box_num; ++i)
		bfs(box[i][0], box[i][1], i);

	cout << dfs(0, 0);

	return 0;
}