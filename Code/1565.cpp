#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

constexpr int max_size = 2000009;

class edge {
public:
	int to = 0;
	long long val = 0;
	long long money = 0;
	edge* next = nullptr;
};

edge* head[1009], * rear[1009];
int queue_data[max_size] = { 0 };
int queue_start = 0, queue_size = 0;

long long dis[1009] = { 0 }, cost[1009] = { 0 };

void SPFA(int from) {
	queue_data[(queue_start + queue_size) % max_size] = from;
	dis[from] = 0;
	cost[from] = 0;
	++queue_size;
	while (queue_size) {
		auto temp = queue_data[queue_start % max_size];
		++queue_start;
		--queue_size;
		for (auto p = head[temp]->next; p; p = p->next) {
			if (dis[temp] + p->val < dis[p->to]||
				(dis[temp] + p->val == dis[p->to] && cost[temp] + p->money < cost[p->to])) {
				dis[p->to] = dis[temp] + p->val;
				cost[p->to] = cost[temp] + p->money;
				queue_data[(queue_start + queue_size) % max_size] = p->to;
				++queue_size;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	for (int i = 1; i <= 1000; ++i) {
		rear[i] = head[i] = new edge;
		dis[i] = 999999999999;
		cost[i] = 999999999999;
	}
	for (int i = 0; i < m; ++i) {
		int u, v;
		long long c, money;
		cin >> u >> v >> c >> money;
		rear[u]->next = new edge;
		rear[u] = rear[u]->next;
		rear[u]->to = v;
		rear[u]->val = c;
		rear[u]->money = money;

		rear[v]->next = new edge;
		rear[v] = rear[v]->next;
		rear[v]->to = u;
		rear[v]->val = c;
		rear[v]->money = money;
	}

	int s, t;
	cin >> s >> t;

	SPFA(s);
	cout << dis[t] << " " << cost[t];

	return 0;
}