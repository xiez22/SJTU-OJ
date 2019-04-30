#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

class node {
public:
	int val = 0;
	node* lchild = nullptr,
		* rchild = nullptr;
};
int pre[100009] = { 0 }, in[100009] = { 0 };

void create_tree(int pre_pos, int in_pos, int len, node* pos) {
	//写入
	pos->val = pre[pre_pos];
	int mid;
	for (mid = in_pos; in[mid] != pre[pre_pos]; ++mid);
	int llen = mid - in_pos, rlen = in_pos + len - mid - 1;
	if (llen) {
		pos->lchild = new node;
		create_tree(pre_pos + 1, in_pos, llen, pos->lchild);
	}
	if (rlen) {
		pos->rchild = new node;
		create_tree(pre_pos + 1 + llen, mid + 1, rlen, pos->rchild);
	}
}

//后续遍历
void post_order(node* pos){
	if (pos) {
		post_order(pos->lchild);
		post_order(pos->rchild);
		printf("%d ", pos->val);
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", &pre[i]);
	for (int i = 0; i < n; ++i)
		scanf("%d", &in[i]);

	node* root = new node;
	create_tree(0, 0, n, root);
	post_order(root);

	return 0;
}