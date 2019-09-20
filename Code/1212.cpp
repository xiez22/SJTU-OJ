#include "iostream"
#include "cstdio"
#include "cmath"
#include "cstring"
using namespace std;

template <class T>
class mQueue {
	class node {
	public:
		T data;
		node* next = nullptr;
	};
	node* head = nullptr,
		* rear = nullptr;
	size_t _size = 0;

public:
	//构造函数
	mQueue() {
		head = new node;
		rear = head;
	}
	//判断是否为空
	bool empty() {
		return head->next == nullptr;
	}
	//增加
	void push(const T& val) {
		rear->next = new node;
		rear = rear->next;
		rear->data = val;
		++_size;
	}
	//删除
	void pop() {
		//安全措施
		if (head->next == nullptr)
			return;
		auto temp = head->next;
		delete head;
		head = temp;
		--_size;
	}
	//大小
	size_t size() {
		return _size;
	}
	//最前
	T& front() {
		return head->next->data;
	}
	//最后
	T& back() {
		return rear->data;
	}
};

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
	long long sizeOfTree= 0;

	//创建树
	void createTree(int num) {
		nodeList = new node*[num + 1]{ nullptr };
		sizeOfTree = num;
	}

	void creadNode(int nodeNum, int lchild, int rchild,int data) {
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
		mQueue<node*> treeQueue;
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
	T* levelTraversal(){
		if (sizeOfTree == 0)
			return NULL;

		T *result = new T[sizeOfTree];
		mQueue<node*> treeQueue;
		long long pos = 0;
		//根结点入队
		treeQueue.push(root);

		//层次遍历
		while (!treeQueue.empty()) {
			//出队
			node* temp= treeQueue.front();
			treeQueue.pop();

			//入队
			if (temp->lchild != nullptr)
				treeQueue.push(temp->lchild);
			if (temp->rchild != nullptr)
				treeQueue.push(temp->rchild);

			//写入
			result[pos++] = temp->data;
		}

		//返回
		return result;
	}
};

int main() {
	int num;
	myBinaryTree<int> bTree;
	cin >> num;
	bTree.createTree(num);

	for (int i = 1; i <= num; i++) {
		int lchild, rchild, nodeData;
		scanf("%d %d %d", &lchild, &rchild, &nodeData);
		bTree.creadNode(i, lchild, rchild, nodeData);
	}

	bTree.checkRoot();
	auto ans = bTree.levelTraversal();

	cout << ans[0];
	for (int i = 1; i < bTree.sizeOfTree; i++)
		printf(" %d", ans[i]);

	return 0;
}