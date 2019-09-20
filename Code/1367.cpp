#include "iostream"
#include "cstdio"
#include "algorithm"
using namespace std;

//二叉树
class special_tree {
public:
	class node {
	public:
		//左孩子代表0
		node* lchild = nullptr;
		//右孩子代表1
		node* rchild = nullptr;
	};
	node* root = nullptr;
	special_tree() {
		root = new node;
	}
};

int cur_ans = 0;

void dfs(special_tree::node* p1, special_tree::node* p2,int ans) {
	if (p1->lchild == nullptr && p1->rchild == nullptr) {
		if (ans > cur_ans)
			cur_ans = ans;
		return;
	}
	ans = ans << 1;
	if (p1->lchild && p2->rchild && p1->rchild && p2->lchild) {
		dfs(p1->lchild, p2->rchild, 1 + ans);
		dfs(p1->rchild, p2->lchild, 1 + ans);
	}
	else if (p1->lchild && p2->rchild) {
		dfs(p1->lchild, p2->rchild, 1 + ans);
	}
	else if (p1->rchild && p2->lchild) {
		dfs(p1->rchild, p2->lchild,1 + ans);
	}
	else if (p1->lchild && p2->lchild) {
		dfs(p1->lchild, p2->lchild, ans);
	}
	else if (p1->rchild && p2->rchild) {
		dfs(p1->rchild, p2->rchild, ans);
	}
}

int main() {
	int N, M;
	scanf("%d %d", &N, &M);

	special_tree tree_a, tree_b;

	for (; N > 0; --N) {
		int temp;
		scanf("%d", &temp);
		//化为2进制
		bool ans[32] = { 0 };
		for (int i = 31; i >= 0; temp = temp >> 1, --i)
			ans[i] = temp % 2;
		//写入二叉树
		auto p = tree_a.root;
		for (int i = 0; i < 32; ++i) {
			if (ans[i]) {
				if (p->rchild == nullptr)
					p->rchild = new special_tree::node;
				p = p->rchild;
			}
			else {
				if (p->lchild == nullptr)
					p->lchild = new special_tree::node;
				p = p->lchild;
			}
		}
	}

	for (; M > 0; --M) {
		int temp;
		scanf("%d", &temp);
		//化为2进制
		bool ans[32] = { 0 };
		for (int i = 31; i >= 0; temp = temp >> 1, --i)
			ans[i] = temp % 2;
		//写入二叉树
		auto p = tree_b.root;
		for (int i = 0; i < 32; ++i) {
			if (ans[i]) {
				if (p->rchild == nullptr)
					p->rchild = new special_tree::node;
				p = p->rchild;
			}
			else {
				if (p->lchild == nullptr)
					p->lchild = new special_tree::node;
				p = p->lchild;
			}
		}
	}

	//寻找最大值
	auto p1 = tree_a.root, p2 = tree_b.root;
	dfs(p1, p2, 0);
	printf("%d",cur_ans);

	return 0;
}