#include "iostream"
#include "cmath"
#include "cstdio"
using namespace std;

constexpr int NUM_SIZE = 100009;
constexpr int HASH_MAX = 500000;

//数据存放类
class data_type {
public:
	int x = -1, y = -1, val = 0;
};

//简易哈希表
class hash_map {
public:
	data_type hash_data[HASH_MAX]{};

	//哈希函数
	int hash_func(int key1, int key2) {
		return ((unsigned int)(key1 * key2)) % (unsigned int)HASH_MAX;
	}

	//寻找
	int find(int key1, int key2) {
		for (auto p = hash_func(key1, key2);; p = (p + 1) % HASH_MAX) {
			if (hash_data[p].x == key1 && hash_data[p].y == key2) {
				return hash_data[p].val;
			}
			else if (hash_data[p].x < 0) {
				return 0;
			}
		}
	}
	
	//插入
	void insert(int key1, int key2, int val) {
		for (auto p = hash_func(key1, key2);; p = (p + 1) % HASH_MAX) {
			if (hash_data[p].x < 0) {
				hash_data[p].x = key1;
				hash_data[p].y = key2;
				hash_data[p].val = val;
				break;
			}
		}
	}
};

//映射关系
int row[NUM_SIZE], col[NUM_SIZE];
hash_map map_data;

int main() {
	//初始化映射关系
	for (int i = 0; i < NUM_SIZE; ++i) {
		row[i] = i;
		col[i] = i;
	}

	int n, m;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		map_data.insert(x, y, z);
	}
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int op, x, y;
		scanf("%d %d %d", &op, &x, &y);
		if (op == 0) {
			auto temp = row[x];
			row[x] = row[y];
			row[y] = temp;
		}
		else if (op == 1) {
			auto temp = col[x];
			col[x] = col[y];
			col[y] = temp;
		}
		else {
			printf("%d\n", map_data.find(row[x], col[y]));
		}
	}

	return 0;
}