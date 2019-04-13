#include "iostream"
#include "cstdio"
using namespace std;

class Position {
public:
	int x = 0, y = 0;
	int distance = 0;

	Position() = default;
	Position(int x,int y,int dis):x(x),y(y),distance(dis){}
};

template <class T>
class my_queue {
	T queue_[100000];
	int start = 0, end = 0;
	int mod = 100000;
public:
	bool empty() const{
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
};

bool map[1209][1209] = { 0 };


int dx[] = { 0,1,0,-1 },
dy[] = { 1,0,-1,0 };
my_queue<Position> queue_data;

int bfs(int destx,int desty) {
	Position init_pos(600, 600, 0);
	queue_data.push(init_pos);
	map[600][600] = true;
	while (!queue_data.empty()) {
		auto temp = queue_data.front();
		queue_data.pop();
		
		//≈–∂œ «∑ÒµΩ¥Ô
		if (temp.x == destx && temp.y == desty)
			return temp.distance;
		for (int i = 0; i < 4; ++i) {
			if (temp.x + dx[i] >= 0 && temp.y + dy[i] >= 0 && temp.x + dx[i] <= 1200
				&& temp.y + dy[i] <= 1200 && !map[temp.x + dx[i]][temp.y + dy[i]]) {
				Position next_pos(temp.x + dx[i], temp.y + dy[i], temp.distance + 1);
				queue_data.push(next_pos);
				map[next_pos.x][next_pos.y] = true;
			}
		}
	}
	return 0;
}

int main() {
	int X, Y, N;
	cin >> X >> Y >> N;
	X += 600;
	Y += 600;

	for (int i = 0; i < N; ++i) {
		int tempx, tempy;
		scanf("%d %d", &tempx, &tempy);
		map[tempx + 600][tempy + 600] = true;
	}

	cout << bfs(X, Y);

	return 0;
}