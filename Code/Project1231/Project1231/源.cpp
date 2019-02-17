#include "iostream"
#include "cstdio"
#include "queue"
#include "cmath"
#include "stack"
#include "cstring"
using namespace std;

//二叉树类
template <class T>
class myBinaryTree {
public:
	class node {
	public:
		T data;
		node* lchild = nullptr, * rchild = nullptr, * parent = nullptr;
	};
	node* root = nullptr;
	node** nodeList = nullptr;
	long long sizeOfTree = 0;

	//创建一个相应大小的树
	void createTree(int num) {
		nodeList = new node * [num + 1]{ nullptr };
		sizeOfTree = num;
	}
	//创建结点（全部完成后需要CheckRoot进行根节点识别）
	void createNode(int nodeNum, int lchild, int rchild, T data) {
		if (nodeList[nodeNum] == nullptr)
			nodeList[nodeNum] = new node;

		nodeList[nodeNum]->data = data;

		if (lchild != 0) {
			if (nodeList[lchild] == nullptr)
				nodeList[lchild] = new node;
			nodeList[lchild]->parent = nodeList[nodeNum];
			nodeList[nodeNum]->lchild = nodeList[lchild];
		}

		if (rchild != 0) {
			if (nodeList[rchild] == nullptr)
				nodeList[rchild] = new node;
			nodeList[rchild]->parent = nodeList[nodeNum];
			nodeList[nodeNum]->rchild = nodeList[rchild];
		}
	}
	//创建一个num大小的树，数据为treeData
	void createTree(T * treeData, int num) {
		createTree(num);
		for (int i = 1; i <= num; i++) {
			int lchild = i * 2 <= num ? i * 2 : 0,
				rchild = i * 2 + 1 <= num ? i * 2 + 1 : 0;
			createNode(i, lchild, rchild, treeData[i - 1]);
		}
		checkRoot();
	}

	void checkRoot() {
		for (int i = 1; i <= sizeOfTree; i++) {
			if (nodeList[i]->parent == nullptr) {
				root = nodeList[i];
				break;
			}
		}
	}

	//清空
	void clear() {
		clear(root);
	}

	void clear(node * p) {
		if (p == nullptr)
			return;
		clear(p->lchild);
		clear(p->rchild);
		delete p;
		p = nullptr;
	}

	//构造
	myBinaryTree() {}

	//析构
	~myBinaryTree() {
		clear(root);
	}

	//判断是否非空
	bool empty() {
		return root == nullptr;
	}

	//返回大小
	long long size() {
		return sizeOfTree;
	}
};

int ans = 0;
//lca(节点)
int lca(myBinaryTree<int>::node* curNode, int d1, int d2) {
	if (curNode == nullptr)
		return 0;
	auto l = lca(curNode->lchild, d1, d2), r = lca(curNode->rchild, d1, d2);
	if (ans > 0)
		return 2;
	else if (l + r + int(curNode->data == d1 || curNode->data == d2) >= 2) {
		ans = curNode->data;
		return 2;
	}
	else
		return l + r + int(curNode->data == d1 || curNode->data == d2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	myBinaryTree<int> bTree;
	int N, X, Y;
	cin >> N >> X >> Y;

	bTree.createTree(N);
	for (int i = 1; i <= N; i++) {
		int lchild, rchild;
		cin >> lchild >> rchild;
		bTree.createNode(i, lchild, rchild, i);
	}
	bTree.checkRoot();
	lca(bTree.root, X, Y);
	cout << ans;

	return 0;
}