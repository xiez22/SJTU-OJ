//二叉树类 数据结构模板 By @ligongzzz
//更新时间：2019年1月25日


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
		node *lchild = nullptr, *rchild = nullptr, *parent = nullptr;
	};
	node *root = nullptr;
	node **nodeList = nullptr;
	long long sizeOfTree = 0;

	//创建一个相应大小的树
	void createTree(int num) {
		nodeList = new node*[num + 1]{ nullptr };
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
	void createTree(T* treeData, int num) {
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

	//迭代器
	class preorderIterator {
		stack<node*> myStack;
		node* currentData = nullptr;
		friend preorderIterator myBinaryTree::preorderBegin();
	public:
		T& get() {
			return currentData->data;
		}
		//遍历结束或内容为空
		bool finish() {
			return currentData == nullptr&&myStack.empty();
		}

		preorderIterator& operator++() {
			if (finish())
				return *this;
			if (myStack.empty()) {
				currentData = nullptr;
				return *this;
			}
			currentData = myStack.top();
			myStack.pop();
			if (currentData->rchild != nullptr)
				myStack.push(currentData->rchild);
			if (currentData->lchild != nullptr)
				myStack.push(currentData->lchild);
			return *this;
		}
	};

	preorderIterator preorderBegin() {
		preorderIterator result;
		result.myStack.push(root);
		++result;
		return result;
	}

	class inorderIterator {
		stack<node*> myStack;
		node* currentData = nullptr;
		friend inorderIterator myBinaryTree::inorderBegin();
	public:
		T& get() {
			return currentData->data;
		}
		//遍历结束或内容为空
		bool finish() {
			return currentData == nullptr&&myStack.empty();
		}

		inorderIterator& operator++() {
			if (finish())
				return *this;
			if (myStack.empty()) {
				currentData = nullptr;
				return *this;
			}
			currentData = myStack.top();
			myStack.pop();
			for (node* p = currentData->rchild; p != nullptr; p = p->lchild)
				myStack.push(p);
			return *this;
		}
	};

	inorderIterator inorderBegin() {
		inorderIterator result;
		for (node* p = root; p != nullptr; p = p->lchild)
			result.myStack.push(p);
		++result;
		return result;
	}

	class postorderIterator {
		stack<node*> myStack;
		node* currentData = nullptr;
		friend postorderIterator myBinaryTree::postorderBegin();
	public:
		T& get() {
			return currentData->data;
		}
		//遍历结束或内容为空
		bool finish() {
			return currentData == nullptr&&myStack.empty();
		}

		postorderIterator& operator++() {
			if (finish())
				return *this;
			if (myStack.empty()) {
				currentData = nullptr;
				return *this;
			}
			currentData = myStack.top();
			myStack.pop();
			if (myStack.empty() || myStack.top()->rchild == currentData)
				return *this;
			for (node* p = myStack.top()->rchild; p != nullptr;) {
				myStack.push(p);
				if (p->lchild != nullptr)
					p = p->lchild;
				else if (p->rchild != nullptr)
					p = p->rchild;
				else
					break;
			}
			return *this;
		}
	};

	postorderIterator postorderBegin() {
		postorderIterator result;
		for (node* p = root; p != nullptr;) {
			result.myStack.push(p);
			if (p->lchild != nullptr)
				p = p->lchild;
			else if (p->rchild != nullptr)
				p = p->rchild;
			else
				break;
		}
		++result;
		return result;
	}

	//层序遍历迭代器
	class levelIterator {
		queue<node*> myQueue;
		node* currentData = nullptr;
		friend levelIterator myBinaryTree::levelBegin();
	public:
		T& get() {
			return currentData->data;
		}
		//遍历结束或内容为空
		bool finish() {
			return currentData == nullptr&&myQueue.empty();
		}

		levelIterator& operator++() {
			if (finish())
				return *this;
			if (myQueue.empty()) {
				currentData = nullptr;
				return *this;
			}
			currentData = myQueue.front();
			myQueue.pop();
			if (currentData->lchild != nullptr)
				myQueue.push(currentData->lchild);
			if (currentData->rchild != nullptr)
				myQueue.push(currentData->rchild);
			return *this;
		}
	};

	levelIterator levelBegin() {
		levelIterator result;
		result.myQueue.push(root);
		++result;
		return result;
	}
};
