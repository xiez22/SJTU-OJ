#include "iostream"
#include "cstdio"
#include "cmath"
#include "cstring"
using namespace std;

class position {
public:
	int distance = 0;
	int posx = 0, posy = 0;
	int remain = 0;
};

template <class T>
class my_queue {
	T queue_[100000];
	int start = 0, end = 0;
	int mod = 100000;
public:
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

int map_data[309][309] = { 0 };
int dx[] = { 0,1,0,-1 },
dy[] = { 1,0,-1,0 };
int visited[309][309] = { 0 };

my_queue<position> queue_data;
int n, m;
int bfs(int startx, int starty, int endx, int endy) {
	//初始点位
	position start_point;
	start_point.posx = startx;
	start_point.posy = starty;
	start_point.distance = 0;
	start_point.remain = 6;
	queue_data.push(start_point);
	visited[startx][starty] = 6;

	while (!queue_data.empty()) {
		auto temp = queue_data.front();
		queue_data.pop();
		//判断是否到达
		if (temp.posx == endx && temp.posy == endy) {
			return temp.distance;
		}
		//补充能量
		if (map_data[temp.posx][temp.posy] == 4) {
			temp.remain = 6;
			map_data[temp.posx][temp.posy] = 0;
		}
		if (temp.remain > 1) {
			for (int i = 0; i < 4; ++i) {
				auto nextx = temp.posx + dx[i],
					nexty = temp.posy + dy[i];
				if (nextx >= 0 && nextx < n && nexty >= 0 && nexty < m &&
					map_data[nextx][nexty]!=0) {
					position next;
					next.distance = temp.distance + 1;
					next.posx = nextx;
					next.posy = nexty;
					next.remain = temp.remain - 1;
					if (next.remain > visited[next.posx][next.posy]) {
						queue_data.push(next);
						visited[next.posx][next.posy] = next.remain;
					}
				}
			}
		}
	}

	return -1;
}

int main() {
	scanf("%d %d", &n, &m);

	int startx = 0, starty = 0,
		endx = 0, endy = 0;
	
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			scanf("%d", &map_data[i][j]);
			if (map_data[i][j] == 2) {
				startx = i, starty = j;
			}
			else if (map_data[i][j] == 3) {
				endx = i, endy = j;
			}
		}

	cout << bfs(startx, starty, endx, endy);

	return 0;
}