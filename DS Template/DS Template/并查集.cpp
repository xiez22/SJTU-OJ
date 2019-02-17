//并查集类 数据结构模板 By @ligongzzz
//更新时间：2019年2月14日


#include "iostream"
#include "cstring"
#include "set"
#include "queue"
#include "vector"
using namespace std;

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