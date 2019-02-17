#include "iostream"
#include "cstring"
#include "set"
#include "queue"
#include "vector"
using namespace std;

//存放答案
vector<int> ans;

//并查集
class disjointSet {
public:
	//数组
	int* parent;
	int length = 0;
	set<int>* edges;

	//构造函数
	disjointSet() = default;
	disjointSet(int size) :length(size) {
		parent = new int[size];
		edges = new set<int>[size];
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

	//BFS
	void bfs(int a, int b) {
		bool* visited = new bool[length]();
		int* last_visit = new int[length]();
		queue<int> mq;
		mq.push(a);
		while (!mq.empty()) {
			auto curPos = mq.front();
			visited[curPos] = true;
			mq.pop();
			if (curPos == b) {
				break;
			}
			for (auto p : edges[curPos]) {
				if (!visited[p]) {
					mq.push(p);
					last_visit[p] = curPos;
				}
			}
		}
		//反向搜索
		for (int i = b;; i = last_visit[i]) {
			ans.push_back(i);
			if (i == a)
				break;
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, A, B;
	cin >> N >> A >> B;
	disjointSet dset(N*(N+1)/2+1);
	int pi, qi;
	while (cin >> pi >> qi) {
		//求出层和位置
		int n, pos;
		for (n = 1; n * (n + 1) / 2 < pi; n++);
		pos = pi - n * (n - 1) / 2;

		//砸墙
		if (qi == 0) {
			if (pos > 1 && n > 1) {
				dset.set_union(dset.find(pi), dset.find(pi - n));
				dset.edges[pi].insert(pi - n);
				dset.edges[pi - n].insert(pi);
			}
		}
		else if (qi == 1) {
			if (pos < n && n>1) {
				dset.set_union(dset.find(pi), dset.find(pi - n + 1));
				dset.edges[pi].insert(pi - n + 1);
				dset.edges[pi - n + 1].insert(pi);
			}
		}
		else if (qi == 2) {
			if (n < N){
				dset.set_union(dset.find(pi), dset.find(pi + n)); 
				dset.edges[pi].insert(pi + n);
				dset.edges[pi + n].insert(pi);
			}
		}
		else if (qi == 3) {
			if (n < N) {
				dset.set_union(dset.find(pi), dset.find(pi + n + 1));
				dset.edges[pi].insert(pi + n + 1);
				dset.edges[pi + n + 1].insert(pi);
			}
		}

		//判断是否有出入口
		if (dset.find(A) == dset.find(B)) {
			dset.bfs(A, B);
			cout << ans[ans.size() - 1];
			for (int i = ans.size() - 2; i >= 0; i--)
				cout << " " << ans[i];
			break;
		}
	}

	return 0;
}