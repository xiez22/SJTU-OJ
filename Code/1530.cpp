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
		node *lchild = nullptr, *rchild = nullptr;
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
			nodeList[nodeNum]->lchild = nodeList[lchild];
		}

		if (rchild != 0) {
			if (nodeList[rchild] == nullptr)
				nodeList[rchild] = new node;
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
		root = nodeList[1];
	}
	//创建一个空的完全二叉树
	void createNullTree(int num) {
		createTree(num);
		nodeList[1] = new node;
		for (int i = 1; i <= num; i++) {
			if (i * 2 <= num) {
				nodeList[i * 2] = new node;
				nodeList[i]->lchild = nodeList[i * 2];
			}
			if (i * 2 + 1 <= num) {
				nodeList[i * 2 + 1] = new node;
				nodeList[i]->rchild = nodeList[i * 2 + 1];
			}
		}
		root = nodeList[1];
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


	//返回大小
	long long size() {
		return sizeOfTree;
	}

	//迭代器
	class preorderIterator {
	public:
		stack<node*> myStack;
		node* currentData = nullptr;
		friend preorderIterator myBinaryTree::preorderBegin();
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
	public:
		stack<node*> myStack;
		node* currentData = nullptr;
		friend inorderIterator myBinaryTree::inorderBegin();
	
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
	public:
		stack<node*> myStack;
		node* currentData = nullptr;
		friend postorderIterator myBinaryTree::postorderBegin();
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
	public:
		queue<node*> myQueue;
		node* currentData = nullptr;
		friend levelIterator myBinaryTree::levelBegin();
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



	//层次遍历
	vector<T*> levelTraversal() {
		if (sizeOfTree == 0)
			return *new vector<T*>;

		vector<T*> result;
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
			result.push_back(&temp->data);
		}

		//返回
		return result;
	}

	//前序遍历
	vector<T*> preorderTraversal() {
		vector<T*> result;
		preorderTraversal(root, result);
		return result;
	}

	void preorderTraversal(node* treeRoot, vector<T*> &result) {
		//显示当前
		result.push_back(&treeRoot->data);

		if (treeRoot->lchild != nullptr)
			preorderTraversal(treeRoot->lchild, result);
		if (treeRoot->rchild != nullptr)
			preorderTraversal(treeRoot->rchild, result);
	}

	//中序遍历
	vector<T*> inorderTraversal() {
		vector<T*> result;
		inorderTraversal(root, result);
		return result;
	}

	void inorderTraversal(node* treeRoot, vector<T*> &result) {
		if (treeRoot->lchild != nullptr)
			inorderTraversal(treeRoot->lchild, result);
		//显示当前
		result.push_back(&treeRoot->data);
		if (treeRoot->rchild != nullptr)
			inorderTraversal(treeRoot->rchild, result);
	}

	//后序遍历
	vector<T*> postorderTraversal() {
		vector<T*> result;
		postorderTraversal(root, result);
		return result;
	}

	void postorderTraversal(node* treeRoot, vector<T*> &result) {
		if (treeRoot->lchild != nullptr)
			postorderTraversal(treeRoot->lchild, result);
		if (treeRoot->rchild != nullptr)
			postorderTraversal(treeRoot->rchild, result);
		//显示当前
		result.push_back(&treeRoot->data);
	}
};

int main() {
	int num;
	cin >> num;

	for (; num > 0; num--) {
		int n;
		scanf("%d", &n);
		char order[100], op[100], *str = new char[n + 1];
		scanf("%s %s\n%s", order, op, str);
		//建树
		myBinaryTree<char> bTree;
		if (strcmp(op, "ENCODE") == 0) {
			bTree.createTree(str, n);
			delete str;
			if (strcmp(order, "PREORDER") == 0)
				for (auto p = bTree.preorderBegin(); !p.finish(); ++p)
					printf("%c", p.currentData->data);
			else if (strcmp(order, "INORDER") == 0)
				for (auto p = bTree.inorderBegin(); !p.finish(); ++p)
					printf("%c", p.currentData->data);
			else if (strcmp(order, "POSTORDER") == 0)
				for (auto p = bTree.postorderBegin(); !p.finish(); ++p)
					printf("%c", p.currentData->data);
		}
		else if (strcmp(op, "DECODE") == 0) {
			int i = 0;
			bTree.createTree(str, n);
			if (strcmp(order, "PREORDER") == 0)
				for (auto p = bTree.preorderBegin(); !p.finish(); ++p, ++i)
					p.currentData->data = str[i];
			else if (strcmp(order, "INORDER") == 0)
				for (auto p = bTree.inorderBegin(); !p.finish(); ++p, ++i)
					p.currentData->data = str[i];
			else if (strcmp(order, "POSTORDER") == 0)
				for (auto p = bTree.postorderBegin(); !p.finish(); ++p, ++i)
					p.currentData->data = str[i];
			delete str;
			for (auto p = bTree.levelBegin(); !p.finish(); ++p)
				printf("%c", p.currentData->data);
		}
		printf("\n");
	}

	return 0;
}