#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
using namespace std;

char ans[100009] = { 0 };

class bst {
public:
	class node {
	public:
		int val = 0;
		node* lchild = nullptr, * rchild = nullptr;
		node* parent = nullptr;
	};
	node* root = nullptr;

	void find(const int& val) {
		memset(ans, 0, sizeof(ans));
		int length = 0;
		ans[length++] = '*';
		for (auto p = root; p;) {
			if (p->val == val) {
				printf("%s\n", ans);
				return;
			}
			else if (val < p->val) {
				ans[length++] = 'l';
				p = p->lchild;
			}
			else {
				ans[length++] = 'r';
				p = p->rchild;
			}
		}
		printf("Nothing.\n");
	}

	void insert(const int& val) {
		if (!root) {
			root = new node;
			root->val = val;
			return;
		}
		//寻找
		auto p = root;
		for (; p;) {
			if (p->val == val)
				return;
			if (val < p->val) {
				if (p->lchild)
					p = p->lchild;
				else {
					p->lchild = new node;
					p->lchild->parent = p;
					p = p->lchild;
					break;
				}
			}
			else {
				if (p->rchild)
					p = p->rchild;
				else {
					p->rchild = new node;
					p->rchild->parent = p;
					p = p->rchild;
					break;
				}
			}
		}
		//增加
		p->val = val;
	}

	void erase(const int& val) {
		auto p = root;
		for (; p;) {
			if (p->val == val) {
				//如果是叶子结点则直接删除
				if (!p->lchild && !p->rchild) {
					if (p == root)
						root = nullptr;
					else if (p->parent->lchild == p)
						p->parent->lchild = nullptr;
					else
						p->parent->rchild = nullptr;
					delete p;
				}
				//如果只有左孩子
				else if (p->lchild && !p->rchild) {
					if (p == root) {
						root = p->lchild;
						p->lchild->parent = nullptr;
					}
					else if (p->parent->lchild == p) {
						p->parent->lchild = p->lchild;
						p->lchild->parent = p->parent;
					}
					else {
						p->parent->rchild = p->lchild;
						p->lchild->parent = p->parent;
					}
					delete p;
				}
				//如果有右孩子
				else if (p->rchild) {
					auto q = p->rchild;
					for (; q->lchild; q = q->lchild);
					p->val = q->val;
					if (q->parent->lchild == q)
						q->parent->lchild = q->rchild;
					else
						q->parent->rchild = q->rchild;
					if (q->rchild)
						q->rchild->parent = q->parent;
					delete q;
				}
				return;
			}
			else if (val < p->val)
				p = p->lchild;
			else
				p = p->rchild;
		}
	}
};

bst my_bst;

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		char op;
		int temp;
		scanf("\n%c %d", &op, &temp);
		if (op == '+') {
			my_bst.insert(temp);
		}
		else if (op == '-') {
			my_bst.erase(temp);
		}
		else {
			my_bst.find(temp);
		}
	}

	return 0;
}