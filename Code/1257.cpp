#include "iostream"
#include "queue"
#include "stack"
#include "cstdio"
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
};

int main() {
	int opNum;
	cin >> opNum;
	myBinaryTree<int> bTree;
	bTree.createTree(100000);
	bTree.createNode(1, 0, 0, 1);
	bTree.root = bTree.nodeList[1];

	for (; opNum > 0; opNum--) {
		int op;
		scanf("%d", &op);
		if (op == 1) {
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);

			//判断是否合法
			if (bTree.nodeList[a] == nullptr ||
				bTree.nodeList[a]->lchild != nullptr || bTree.nodeList[a]->rchild != nullptr ||
				bTree.nodeList[b] != nullptr || bTree.nodeList[c] != nullptr) {
				printf("Error!\n");
				continue;
			}
			else {
				bTree.createNode(a, b, c, a);
				bTree.nodeList[b]->data = b;
				bTree.nodeList[c]->data = c;
				printf("Ok!\n");
			}
		}
		else if (op == 2) {
			int a;
			scanf("%d", &a);
			//判断是否合法
			if (bTree.nodeList[a] == nullptr) {
				printf("Error!\n");
				continue;
			}
			else {
				printf("%d %d %d\n",
					bTree.nodeList[a]->parent == nullptr ? 0 : bTree.nodeList[a]->parent->data,
					bTree.nodeList[a]->lchild == nullptr ? 0 : bTree.nodeList[a]->lchild->data,
					bTree.nodeList[a]->rchild == nullptr ? 0 : bTree.nodeList[a]->rchild->data);
			}
		}
		else if (op == 3) {
			int a;
			scanf("%d", &a);
			//判断是否合法
			if (a == 1 || bTree.nodeList[a] == nullptr) {
				printf("Error!\n");
				continue;
			}
			else {
				auto father = bTree.nodeList[a]->parent;
				auto temp = father->lchild;
				father->lchild = father->rchild;
				father->rchild = temp;
				printf("%d\n", father->lchild == bTree.nodeList[a] ? father->rchild->data : father->lchild->data);
			}
		}
	}
	
	//输出
	bool firstWrite = true;
	for (auto p = bTree.preorderBegin(); !p.finish(); ++p) {
		if (firstWrite)
			firstWrite = false;
		else
			printf(" ");
		printf("%d", p.get());
	}

	return 0;
}