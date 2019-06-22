#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

template <class T, class T_val = decltype(*declval<T>()),
	class Compare = bool (*)(T_val, T_val)>
	void quick_sort(T start, T end,
		Compare cmp = [](T_val a, T_val b) {return a < b; }) {
	if (start == end)
		return;
	auto i = start, j = end;
	--j;
	if (i == j)
		return;
	//交换
	auto key = *start;
	for (bool status = true; i != j;) {
		if (status) {
			if (cmp(*j, key)) {
				*i = *j;
				++i;
				status = false;
			}
			else
				--j;
		}
		else {
			if (cmp(key, *i)) {
				*j = *i;
				--j;
				status = true;
			}
			else
				++i;
		}
	}
	*i = key;
	//递归
	quick_sort(start, ++i, cmp);
	quick_sort(i, end, cmp);
}

class edge {
public:
	int from = 0, to = 0;
	int length = 0;
};

edge edges[100009];

//并查集
class disjointSet {
public:
	//数组
	int* parent;
	int length = 0;

	//构造函数
	disjointSet() = default;
	disjointSet(int size) :length(size) {
		parent = new int[size];
		memset(parent, -1, length * sizeof(int));
	}

	//析构函数
	~disjointSet() {
		length = 0;
		delete[] parent;
	}

	//寻找
	int find_root(int x) {
		int temp = x;
		for (; parent[temp] >= 0; temp = parent[temp]);
		//压缩路径
		for (int i = x; i != temp;) {
			int tempi = parent[i];
			parent[i] = temp;
			i = tempi;
		}
		return temp;
	}
	//合并
	void set_union(int root1, int root2) {
		if (root1 == root2)
			return;
		if (parent[root1] > parent[root2]) {
			parent[root2] += parent[root1];
			parent[root1] = root2;
		}
		else {
			parent[root1] += parent[root2];
			parent[root2] = root1;
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	disjointSet set_data(n + 1);

	for (int i = 0; i < m; ++i) {
		cin >> edges[i].from >> edges[i].to >> edges[i].length;
	}

	quick_sort(edges, edges + m, [](edge a, edge b) {return a.length < b.length; });

	int cnt = 0;
	long long ans = 0;
	int root_pos = edges[0].from;
	for (int i = 0; i < m; ++i) {
		if (set_data.find_root(edges[i].from) != set_data.find_root(edges[i].to)) {
			set_data.set_union(set_data.find_root(edges[i].from), set_data.find_root(edges[i].to));
			++cnt;
			ans += edges[i].length;
		}
		if (cnt == n - 1) {
			break;
		}
	}

	cout << ans;

	return 0;
}