#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

class type {
public:
	int val = 0;
	int pos = 0;
};

int dist[10009] = { 0 };
int position[10009] = { 0 };

class pqueue {
	type queue_data[10009];
	int _size = 0;
public:
	bool empty() {
		return _size == 0;
	}

	void push_up(int pos) {
		for (; pos > 1 && queue_data[pos].val < queue_data[pos >> 1].val; pos >>= 1) {
			swap(position[queue_data[pos].pos], position[queue_data[pos >> 1].pos]);
			swap(queue_data[pos], queue_data[pos >> 1]);
		}
	}

	void push_down(int pos) {
		for (pos <<= 1; pos <= _size; pos <<= 1) {
			if (pos < _size && queue_data[pos + 1].val < queue_data[pos].val)
				++pos;
			if (queue_data[pos].val < queue_data[pos >> 1].val) {
				swap(position[queue_data[pos].pos], position[queue_data[pos >> 1].pos]);
				swap(queue_data[pos], queue_data[pos >> 1]);
			}
		}
	}

	int size() {
		return _size;
	}

	void push(int val, int pos) {
		++_size;
		position[pos] = _size;
		queue_data[_size].val = val;
		queue_data[_size].pos = pos;
		push_up(_size);
	}

	type pop() {
		swap(position[queue_data[1].pos], position[queue_data[_size].pos]);
		swap(queue_data[1], queue_data[_size]);
		--_size;
		push_down(1);
		return queue_data[_size + 1];
	}

	void change(int val, int pos) {
		queue_data[position[pos]].val = val;
		push_up(position[pos]);
	}
};

int to[200009] = { 0 }, nxt[200009] = { 0 }, cost[200009] = { 0 };
int edge[10009] = { 0 }, edge_cnt = 0;
int total_num[10009] = { 0 }, pre[10009] = { 0 };
bool visited[10009] = { 0 };

void add(int u, int v, int c) {
	++edge_cnt;
	nxt[edge_cnt] = edge[u];
	edge[u] = edge_cnt;
	to[edge_cnt] = v;
	cost[edge_cnt] = c;
}

pqueue queue_data;

int n, m, s, e;
int ans_data[10009] = { 0 };

int dijkstra(int a, int b) {
	int cur_pos = a;
	dist[cur_pos] = 0;
	total_num[cur_pos] = 1;
	visited[cur_pos] = true;
	while (true) {
		//先找到点来入队
		for (int p = edge[cur_pos]; p; p = nxt[p]) {
			if (!visited[to[p]]) {
				dist[to[p]] = dist[cur_pos] + cost[p];
				queue_data.push(dist[cur_pos] + cost[p], to[p]);
				total_num[to[p]] = total_num[cur_pos] + 1;
				pre[to[p]] = cur_pos;
				visited[to[p]] = true;
			}
			else if (dist[cur_pos] + cost[p] < dist[to[p]] ||
				(dist[cur_pos] + cost[p] == dist[to[p]] && total_num[cur_pos] + 1 < total_num[to[p]])) {
				dist[to[p]] = dist[cur_pos] + cost[p];
				queue_data.change(dist[cur_pos] + cost[p], to[p]);
				total_num[to[p]] = total_num[cur_pos] + 1;
				pre[to[p]] = cur_pos;
			}
		}
		//弹出
		if (queue_data.empty()) {
			return -1;
		}
		auto temp = queue_data.pop();
		if (temp.pos == b) {
			return dist[b];
		}
		cur_pos = temp.pos;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> m >> s >> e;

	for (int i = 0; i < m; ++i) {
		int u, v, c;
		cin >> u >> v >> c;
		add(u, v, c);
	}

	cout << dijkstra(s, e) << "\n";
	for (int p = e, i = 0; p; p = pre[p], ++i)
		ans_data[i] = p;

	for (int i = total_num[e] - 1; i >= 0; --i)
		cout << ans_data[i] << " ";

	return 0;
}