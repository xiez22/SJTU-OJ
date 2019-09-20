#include "iostream"
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
		T *lchild=nullptr, *rchild=nullptr;
	};
	node *root=nullptr;

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
	myBinaryTree(){}

	//析构
	~myBinaryTree() {
		clear(root);
	}

	//判断是否非空
	bool empty() {
		return root == nullptr;
	}
};

char tdata[1009] = { 0 };
int dataSize = 0;

void createTree(int rootNum, char *tempData1,char *tempData2) {
	if (strlen(tempData1) == 0) return;
	char root = tempData1[0];
	tdata[rootNum] = root;
	dataSize = rootNum < dataSize ? dataSize : rootNum;
	char ldata1[50] = { 0 }, rdata1[50] = { 0 }, ldata2[50] = { 0 }, rdata2[50] = { 0 };
	int length = strlen(tempData1);
	bool flag = false;
	for (int i = 0,k=0; i < length; i++,k++) {
		if (tempData2[i] == root) {
			flag = true;
			k = -1;
		}
		else if (!flag) {
			ldata1[k] = tempData1[i + 1];
			ldata2[k] = tempData2[i];
		}
		else if (flag) {
			rdata1[k] = tempData1[i];
			rdata2[k] = tempData2[i];
		}
	}
	//递归
	createTree(rootNum * 2, ldata1, ldata2);
	createTree(rootNum * 2 + 1, rdata1, rdata2);
}

int main() {
	char preData[50], postData[50];
	cin >> preData >> postData;

	createTree(1, preData, postData);

	//输出
	cout << tdata[1];
	for (int i = 2; i <= dataSize; i++) {
		if (tdata[i] == 0)
			cout << " NULL";
		else
			cout << " " << tdata[i];
	}

	return 0;
}