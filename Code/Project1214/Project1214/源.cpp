#include "iostream"
#include "cstdio"
#include "queue"
#include "vector"
#include "cmath"
#include "cstring"
using namespace std;

//二叉树类
template <class T>
class myBinaryTree {
public:
	class node {
	public:
		T data;
		node *lchild = nullptr, *rchild = nullptr, *parent = nullptr;
	};
	node *root = nullptr;
	node **nodeList = nullptr;
	long long sizeOfTree = 0;

	//创建树
	void createTree(int num) {
		nodeList = new node*[num + 1]{ nullptr };
		sizeOfTree = num;
	}

	void creadNode(int nodeNum, int lchild, int rchild, int data) {
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

	void clear(node *p) {
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

	//判断是否为完全二叉树
	bool isCBT() {
		if (empty())
			return false;
		//层次遍历
		queue<node*> treeQueue;
		bool flag = false;
		//先入队
		treeQueue.push(root);

		//反复
		while (!treeQueue.empty()) {
			//先出队一个
			node* temp = treeQueue.front();
			treeQueue.pop();

			//右孩子有左孩子没有
			if (temp->lchild == nullptr&&temp->rchild != nullptr)
				return false;

			if (!flag) {
				//左孩子有右孩子没有
				if (temp->lchild != nullptr&&temp->rchild == nullptr) {
					flag = true;
					//左孩子入队
					treeQueue.push(temp->lchild);
				}
				//左右孩子都没有
				else if (temp->lchild == nullptr&&temp->rchild == nullptr) {
					flag = true;
				}
				//左右都有孩子
				else {
					treeQueue.push(temp->lchild);
					treeQueue.push(temp->rchild);
				}
			}
			else {
				//判断是否为叶子
				if (temp->lchild != nullptr || temp->rchild != nullptr)
					return false;
			}
		}

		return true;
	}

	//返回大小
	long long size() {
		return sizeOfTree;
	}

	//层次遍历
	vector<T> levelTraversal() {
		if (sizeOfTree == 0)
			return *new vector<T>;

		vector<T> result; 
		queue<node*> treeQueue;

		//根结点入队
		treeQueue.push(root);

		//层次遍历
		while (!treeQueue.empty()) {
			//出队
			node* temp = treeQueue.front();
			treeQueue.pop();

			//入队
			if (temp->lchild != nullptr)
				treeQueue.push(temp->lchild);
			if (temp->rchild != nullptr)
				treeQueue.push(temp->rchild);

			//写入
			result.push_back(temp->data);
		}

		//返回
		return result;
	}

	//前序遍历
	vector<T> preorderTraversal() {
		vector<T> result;
		preorderTraversal(root, result);
		return result;
	}

	void preorderTraversal(node* treeRoot,vector<T> &result) {
		//显示当前
		result.push_back(treeRoot->data);

		if (treeRoot->lchild != nullptr)
			preorderTraversal(treeRoot->lchild,result);
		if (treeRoot->rchild != nullptr)
			preorderTraversal(treeRoot->rchild,result);
	}

	//中序遍历
	vector<T> midorderTraversal() {
		vector<T> result;
		midorderTraversal(root, result);
		return result;
	}

	void midorderTraversal(node* treeRoot, vector<T> &result) {
		if (treeRoot->lchild != nullptr)
			midorderTraversal(treeRoot->lchild, result);
		//显示当前
		result.push_back(treeRoot->data);
		if (treeRoot->rchild != nullptr)
			midorderTraversal(treeRoot->rchild, result);
	}

	//后序遍历
	vector<T> lostorderTraversal() {
		vector<T> result;
		lostorderTraversal(root, result);
		return result;
	}

	void lostorderTraversal(node* treeRoot, vector<T> &result) {
		if (treeRoot->lchild != nullptr)
			lostorderTraversal(treeRoot->lchild, result);
		if (treeRoot->rchild != nullptr)
			lostorderTraversal(treeRoot->rchild, result);
		//显示当前
		result.push_back(treeRoot->data);
	}
};

//左孩子右兄弟二叉树类
template <class T>
class mySpecialBinaryTree {
public:
	class node {
	public:
		T data;
		node *lchild = nullptr, *rbrother = nullptr;
		bool isRoot = true;
	};
	node *root = nullptr;
	node **nodeList = nullptr;
	long long sizeOfTree = 0;

	//创建树
	void createTree(int num) {
		nodeList = new node*[num + 1]{ nullptr };
		sizeOfTree = num;
	}

	void creadNode(int nodeNum, int lchild, int rbrother, int data) {
		if (nodeList[nodeNum] == nullptr)
			nodeList[nodeNum] = new node;

		nodeList[nodeNum]->data = data;

		if (lchild != 0) {
			if (nodeList[lchild] == nullptr)
				nodeList[lchild] = new node;
			nodeList[lchild]->isRoot = false;
			nodeList[nodeNum]->lchild = nodeList[lchild];
		}

		if (rbrother != 0) {
			if (nodeList[rbrother] == nullptr)
				nodeList[rbrother] = new node;
			nodeList[rbrother]->isRoot = false;
			nodeList[nodeNum]->rbrother = nodeList[rbrother];
		}
	}

	void checkRoot() {
		for (int i = 1; i <= sizeOfTree; i++) {
			if (nodeList[i]->isRoot) {
				root = nodeList[i];
				break;
			}
		}
	}

	//清空
	void clear() {
		clear(root);
	}

	void clear(node *p) {
		if (p == nullptr)
			return;
		clear(p->lchild);
		clear(p->rbrother);
		delete p;
		p = nullptr;
	}

	//构造
	mySpecialBinaryTree() {}

	//析构
	~mySpecialBinaryTree() {
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

	//层次遍历
	vector<T> levelTraversal() {
		if (sizeOfTree == 0)
			return *new vector<T>;

		vector<T> result;
		queue<node*> treeQueue;

		//根结点入队
		treeQueue.push(root);

		//层次遍历
		while (!treeQueue.empty()) {
			//出队
			node* temp = treeQueue.front();
			treeQueue.pop();

			//入队
			for (auto p = temp->lchild; p!= nullptr; p = p->rbrother)
				treeQueue.push(p);
		
			//写入
			result.push_back(temp->data);
		}

		//返回
		return result;
	}

	//前序遍历
	vector<T> preorderTraversal() {
		vector<T> result;
		preorderTraversal(root, result);
		return result;
	}

	void preorderTraversal(node* treeRoot, vector<T> &result) {
		//显示当前
		result.push_back(treeRoot->data);

		if (treeRoot->lchild != nullptr)
			preorderTraversal(treeRoot->lchild, result);
		if (treeRoot->rbrother != nullptr)
			preorderTraversal(treeRoot->rbrother, result);
	}

	//后序遍历
	vector<T> lostorderTraversal() {
		vector<T> result;
		lostorderTraversal(root, result);
		return result;
	}

	void lostorderTraversal(node* treeRoot, vector<T> &result) {
		if (treeRoot->lchild != nullptr)
			lostorderTraversal(treeRoot->lchild, result);
		//显示当前
		result.push_back(treeRoot->data);
		if (treeRoot->rbrother != nullptr)
			lostorderTraversal(treeRoot->rbrother, result);
	}
};

int main() {
	int num;
	mySpecialBinaryTree<int> bTree;
	cin >> num;
	bTree.createTree(num);

	for (int i = 1; i <= num; i++) {
		int lchild, rchild, nodeData;
		scanf("%d %d %d", &lchild, &rchild, &nodeData);
		bTree.creadNode(i, lchild, rchild, nodeData);
	}

	bTree.checkRoot();
	auto ans = bTree.preorderTraversal();

	cout << ans[0];
	for (int i = 1; i < bTree.sizeOfTree; i++)
		printf(" %d", ans[i]);
	ans = bTree.lostorderTraversal();

	cout << endl;

	cout << ans[0];
	for (int i = 1; i < bTree.sizeOfTree; i++)
		printf(" %d", ans[i]);

	ans = bTree.levelTraversal();

	cout << endl;

	cout << ans[0];
	for (int i = 1; i < bTree.sizeOfTree; i++)
		printf(" %d", ans[i]);

	return 0;
}