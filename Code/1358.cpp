#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

class edge {
public:
	int val = 0;
	edge* next = nullptr;
};

edge* edges_start[10009];
edge* edges_end[10009];

int nums[10009] = { 0 };
bool visited[10009] = { 0 };

int dfs(int pos) {
	visited[pos] = true;
	nums[pos] = 1;

	for (auto p = edges_start[pos]->next; p; p = p->next) {
		if (!visited[p->val]) {
			nums[pos] += dfs(p->val);
		}
	}

	return nums[pos];
}

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; ++i) {
		edges_start[i] = edges_end[i] = new edge;
	}

	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);

		edges_end[a]->next = new edge;
		edges_end[a] = edges_end[a]->next;
		edges_end[a]->val = b;

		edges_end[b]->next = new edge;
		edges_end[b] = edges_end[b]->next;
		edges_end[b]->val = a;
	}

	dfs(1);

	for (int i = 1; i <= n; ++i) {
		if (n - nums[i] > n / 2)
			continue;
		bool flag = true;
		for (auto p = edges_start[i]->next; p; p = p->next) {
			if (nums[p->val]<nums[i] && nums[p->val]>n / 2) {
				flag = false;
				break;
			}
		}
		if (flag) {
			printf("%d\n", i);
		}
	}

	return 0;
}
