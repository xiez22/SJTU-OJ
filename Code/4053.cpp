#include "iostream"
#include "cstdio"
using namespace std;

bool not_num[50] = { 0 };
struct edge {
	int num = 0;
	int to[20] = { 0 };

	void add_edge(int pos) {
		to[num++] = pos;
	}
};
edge edges[20];
bool visited[20] = { 0 };
int route[20] = { 0 };
int n;
int cnt = 0;

void DFS(int num, int pos) {
	if (num == 0) {
		if (pos == 1) {
			++cnt;
			printf("%d", route[0]);
			for (int i = 1; i < n; ++i)
				printf(" %d", route[i]);
			printf("\n");
		}
		return;
	}
	if (visited[pos])
		return;
	visited[pos] = true;
	route[n - num] = pos;
	for (int i = 0; i < edges[pos].num; ++i) {
		DFS(num - 1, edges[pos].to[i]);
	}
	visited[pos] = false;
	route[n - num] = 0;
}

int main() {
	//计算质数
	int max_k = 40;
	for (int i = 2; i <= max_k / 2 + 1; ++i) {
		if (not_num[i])
			continue;
		for (int j = i * 2; j <= max_k; j += i)
			not_num[j] = true;
	}

	cin >> n;

	//计算质数路径
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (i == j)
				continue;
			if (!not_num[i + j])
				edges[i].add_edge(j);
		}
	}

	DFS(n, 1);
	if (cnt == 0)
		printf("None");

	return 0;
}