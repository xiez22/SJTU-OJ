#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

int mmax(int a, int b) {
	return a > b ? a : b;
}

int mmin(int a, int b) {
	return a < b ? a : b;
}

//记录元素在优先队列里面的位置
int queue_pos[500009] = { 0 };

class type {
public:
	int pos = 0;
	int val = 0;
};

class mqueue {
public:
	type queue_data[500009];
	int _size = 0;

	void push_up(int pos) {
		for (; pos > 1 && queue_data[pos].val > queue_data[pos >> 1].val; pos >>= 1) {
			swap(queue_pos[queue_data[pos].pos], queue_pos[queue_data[pos >> 1].pos]);
			swap(queue_data[pos], queue_data[pos >> 1]);
		}
	}

	void push_down(int pos) {
		for (; pos * 2 <= _size;) {
			if (pos * 2 == _size) {
				if (queue_data[pos].val < queue_data[pos << 1].val) {
					swap(queue_pos[queue_data[pos].pos], queue_pos[queue_data[pos * 2].pos]);
					swap(queue_data[pos], queue_data[pos << 1]);
				}
				break;
			}
			else {
				if (queue_data[pos].val < mmax(queue_data[pos * 2].val, queue_data[pos * 2 + 1].val)) {
					if (queue_data[pos * 2].val < queue_data[pos * 2 + 1].val) {
						swap(queue_pos[queue_data[pos].pos], queue_pos[queue_data[pos * 2 + 1].pos]);
						swap(queue_data[pos], queue_data[pos * 2 + 1]);
						pos = pos * 2 + 1;
					}
					else {
						swap(queue_pos[queue_data[pos].pos], queue_pos[queue_data[pos * 2].pos]);
						swap(queue_data[pos], queue_data[pos * 2]);
						pos <<= 1;
					}
				}
				else
					break;
			}
		}
	}

	void push(const type& val) {
		queue_data[++_size] = val;
		queue_pos[val.pos] = _size;
		push_up(_size);
	}

	type pop() {
		auto temp = queue_data[1];
		queue_data[1] = queue_data[_size];
		queue_pos[queue_data[1].pos] = 1;
		--_size;
		push_down(1);
		queue_pos[temp.pos] = 0;
		return temp;
	}

	int size() {
		return _size;
	}

	void erase(int pos) {
		queue_pos[queue_data[pos].pos] = 0;
		queue_pos[queue_data[_size].pos] = pos;
		queue_data[pos] = queue_data[_size];
		--_size;
		push_up(pos);
		push_down(pos);
	}
};

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
	int find(int x) {
		if (parent[x] < 0)
			return x;
		return parent[x] = find(parent[x]);
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

	int size(int pos) {
		return -parent[find(pos)];
	}
};

bool cleared[500009] = { 0 };
mqueue queue_data;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	disjointSet set_data(n + 1);
	for (int i = 1; i <= n; ++i) {
		type temp;
		temp.pos = i;
		temp.val = 1;
		queue_data.push(temp);
	}

	for (; m > 0;) {
		char op;
		cin >> op;
		if (op == 'C') {
			--m;
			int x, y;
			cin >> x >> y;

			if (set_data.find(x) == set_data.find(y) || cleared[set_data.find(x)] || cleared[set_data.find(y)]) {
				continue;
			}
			queue_data.erase(queue_pos[set_data.find(x)]);
			queue_data.erase(queue_pos[set_data.find(y)]);
			set_data.set_union(set_data.find(x), set_data.find(y));
			type temp;
			temp.pos = set_data.find(x);
			temp.val = set_data.size(x);
			queue_data.push(temp);
		}
		else if (op == 'D') {
			--m;
			int x;
			cin >> x;
			if (cleared[set_data.find(x)]) {
				continue;
			}
			queue_data.erase(queue_pos[set_data.find(x)]);
			cleared[set_data.find(x)] = true;
		}
		else if (op == 'Q') {
			--m;
			int p;
			cin >> p;
			type temp[12];
			for (int i = 0; i < p - 1; ++i) {
				temp[i] = queue_data.pop();
			}
			type ans = queue_data.pop();
			cout << ans.val << "\n";
			queue_data.push(ans);
			for (int i = 0; i < p - 1; ++i) {
				queue_data.push(temp[i]);
			}
		}
	}

	return 0;
}