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
	position(int dis, int x, int y) :distance(dis), pos_x(x), pos_y(y) {}
};

int map_data[49][49] = { 0 };

bool visited[49][49] = { 0 };
int dx[8], dy[8];
int n, m;

my_queue<position> queue_data;
int bfs(int start_x, int start_y, int end_x, int end_y) {
	queue_data.clear();
	memset(visited, 0, sizeof(visited));
	position start_point(0, start_x, start_y);
	queue_data.push(start_point);
	visited[start_x][start_y] = true;

	while (!queue_data.empty()) {
		auto temp = queue_data.front();
		queue_data.pop();

		if (temp.pos_x == end_x && temp.pos_y == end_y) {
			return temp.distance;
		}

		for (int i = 0; i < 8; ++i) {
			if (temp.pos_x + dx[i] >= 0 && temp.pos_x + dx[i] < m &&
				temp.pos_y + dy[i] >= 0 && temp.pos_y + dy[i] < n &&
				!visited[temp.pos_x + dx[i]][temp.pos_y + dy[i]]
				&& map_data[temp.pos_x + dx[i]][temp.pos_y + dy[i]] != 0
				&& map_data[temp.pos_x + dx[i]][temp.pos_y + dy[i]] != 2) {
				position next_point(temp.distance + 1, temp.pos_x + dx[i], temp.pos_y + dy[i]);
				queue_data.push(next_point);
				visited[next_point.pos_x][next_point.pos_y] = true;
			}
		}
	}
	return -1;
}


int main() {
	int m1, m2;
	scanf("%d %d %d %d", &m, &n, &m1, &m2);

	dx[0] = m1, dy[0] = m2;
	dx[1] = m1, dy[1] = -m2;
	dx[2] = -m1, dy[2] = m2;
	dx[3] = -m1, dy[3] = -m2;
	dx[4] = m2, dy[4] = m1;
	dx[5] = m2, dy[5] = -m1;
	dx[6] = -m2, dy[6] = m1;
	dx[7] = -m2, dy[7] = -m1;

	int start_x, start_y, end_x, end_y;

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf("%d", &map_data[i][j]);
			if (map_data[i][j] == 3) {
				start_x = i;
				start_y = j;
			}
			else if (map_data[i][j] == 4) {
				end_x = i;
				end_y = j;
			}
		}
	}

	cout << bfs(start_x, start_y, end_x, end_y);

	return 0;
}