#include "iostream"
#include "vector"
#include "stack"
using namespace std;

class node {
public:
	long long val = 0;
	long long parent = 0;
	long long num = 0;
	long long tag = 0;
	vector<long long> edges;
};

long long n, m, r;

long long find_parent(long long pos,vector<node>& node_list) {
	long long ans = 1;
	for (auto p : node_list[pos].edges) {
		if (p != node_list[pos].parent) {
			node_list[p].parent = pos;
			ans += find_parent(p, node_list);
			node_list[pos].val += node_list[p].val;
		}
	}
	node_list[pos].num = ans;
	return ans;
}

void push_down(long long pos, vector<node>& node_list) {
	stack<long long> stack_data;
	for (auto p = node_list[pos].parent; p; p = node_list[p].parent) {
		stack_data.push(p);
	}
	while (!stack_data.empty()) {
		auto temp = stack_data.top();
		stack_data.pop();
		if (node_list[temp].tag) {
			for (auto p : node_list[temp].edges) {
				if (p != node_list[temp].parent) {
					node_list[p].val += node_list[temp].tag * node_list[p].num;
					node_list[p].tag += node_list[temp].tag;
				}
			}
			node_list[temp].tag = 0;
		}
	}
}

void push_up(long long pos, long long val, vector<node>& node_list) {
	for (pos = node_list[pos].parent; pos; pos = node_list[pos].parent) {
		node_list[pos].val += val;
	}
}

void update(long long pos, long long val,vector<node>& node_list) {
	push_down(pos, node_list);
	node_list[pos].tag += val;
	node_list[pos].val += node_list[pos].num * val;
	push_up(pos, node_list[pos].num * val, node_list);
}

long long query(long long pos, vector<node>& node_list) {
	push_down(pos, node_list);
	return node_list[pos].val;
}

int main() {
	scanf("%lld %lld %lld", &n, &m, &r);

	vector<node> node_list(n + 1);
	for (long long i = 1; i <= n; ++i) {
		scanf("%lld", &node_list[i].val);
	}

	for (long long i = 1; i <= n - 1; ++i) {
		long long a, b;
		scanf("%lld %lld", &a, &b);
		node_list[a].edges.push_back(b);
		node_list[b].edges.push_back(a);
	}

	find_parent(r, node_list);

	for (; m > 0; --m) {
		long long op;
		scanf("%lld", &op);
		if (op == 1) {
			long long a, x;
			scanf("%lld %lld", &a, &x);
			update(a, x, node_list);
		}
		else {
			long long a;
			scanf("%lld", &a);
			cout << query(a, node_list) << "\n";
		}
	}

	return 0;
}