#include "iostream"
#include "cstring"
using namespace std;

class bst {
public:
	class node {
	public:
		int val = 0;
		node* lchild = nullptr, * rchild = nullptr;
		node* parent = nullptr;
	};

	class iterator {
	public:
		node* cur_pos = nullptr;
		
		//重载++i
		iterator& operator++() {
			if (cur_pos == nullptr)
				return *this;
			//假如有右孩子
			if (cur_pos->rchild != nullptr) {
				for (cur_pos = cur_pos->rchild; cur_pos->lchild != nullptr;)
					cur_pos = cur_pos->lchild;
			}
			//假如是落单的根节点
			else if (cur_pos->parent == nullptr) {
				cur_pos = nullptr;
			}
			//假如是左叶子
			else if (cur_pos->parent->lchild == cur_pos)
				cur_pos = cur_pos->parent;
			//假如是右叶子
			else {
				auto last = cur_pos;
				for (cur_pos = cur_pos->parent;
					cur_pos != nullptr && cur_pos->rchild == last;
					cur_pos = cur_pos->parent)
					last = cur_pos;
			}
			return *this;
		}

		//重载i++
		iterator operator++(int) {
			auto temp = *this;
			if (cur_pos == nullptr)
				return temp;
			//假如有右孩子
			if (cur_pos->rchild != nullptr) {
				for (cur_pos = cur_pos->rchild; cur_pos->lchild != nullptr;)
					cur_pos = cur_pos->lchild;
			}
			//假如是落单的根节点
			else if (cur_pos->parent == nullptr) {
				cur_pos = nullptr;
			}
			//假如是左叶子
			else if (cur_pos->parent->lchild == cur_pos)
				cur_pos = cur_pos->parent;
			//假如是右叶子
			else {
				auto last = cur_pos;
				for (cur_pos = cur_pos->parent;
					cur_pos != nullptr && cur_pos->rchild == last;
					cur_pos = cur_pos->parent)
					last = cur_pos;
			}
			return temp;
		}

		bool operator==(const iterator& other) {
			return cur_pos == other.cur_pos;
		}

		bool operator!=(const iterator& other) {
			return cur_pos != other.cur_pos;
		}

		int& operator*() {
			return cur_pos->val;
		}
	};

	node* root = nullptr;

	iterator begin() {
		iterator temp;
		auto p = root;
		for (; p->lchild; p = p->lchild);
		temp.cur_pos = p;
		return temp;
	}

	iterator end() {
		iterator temp;
		temp.cur_pos = nullptr;
		return temp;
	}

	iterator find(const int& val) {
		iterator ans;
		int length = 0;
		for (auto p = root; p;) {
			if (p->val == val) {
				ans.cur_pos = p;
				return ans;
			}
			else if (val < p->val) {
				p = p->lchild;
			}
			else {
				p = p->rchild;
			}
		}
		ans.cur_pos = nullptr;
		return ans;
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
			if (p->val == val) {
				//统一插入右子树
				if (p->rchild) {
					p->rchild->parent = new node;
					p->rchild->parent->val = val;
					p->rchild->parent->rchild = p->rchild;
					p->rchild = p->rchild->parent;
					p->rchild->parent = p;
				}
				else {
					p->rchild = new node;
					p->rchild->val = val;
					p->rchild->parent = p;
				}
				return;
			}
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

	iterator erase(const iterator& pos) {
		iterator ans = pos;
		auto p = pos.cur_pos;
		//如果是叶子结点则直接删除
		if (!p->lchild && !p->rchild) {
			++ans;
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
			++ans;
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
		return ans;
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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	bst setData;

	int num;
	cin >> num;
	for (; num > 0; num--) {
		char op[100];
		cin >> op;
		if (strcmp(op, "insert") == 0) {
			int temp;
			cin >> temp;
			setData.insert(temp);
		}
		else if (strcmp(op, "delete") == 0) {
			int temp;
			cin >> temp;
			if(auto iter=setData.find(temp);iter!=setData.end())
				setData.erase(iter);
		}
		else if (strcmp(op, "delete_less_than") == 0) {
			int temp;
			cin >> temp;
			for (auto p = setData.begin(); p != setData.end(); ) {
				if (*p < temp) {
					p = setData.erase(p);
				}
				else break;
			}
		}
		else if (strcmp(op, "delete_greater_than") == 0) {
			int temp;
			cin >> temp;
			for (auto p = setData.begin();p!=setData.end(); ) {
				if (*p > temp) {
					p = setData.erase(p);
				}
				else ++p;
			}
		}
		else if (strcmp(op, "delete_interval") == 0) {
			int l, r;
			cin >> l >> r;
			for (auto p = setData.begin(); p != setData.end();) {
				if (*p > l && (*p) < r)
					p = setData.erase(p);
				else if (*p >= r)
					break;
				else ++p;
			}
		}
		else if (strcmp(op, "find") == 0) {
			int temp;
			cin >> temp;
			if (setData.find(temp) != setData.end())
				cout << "Y" << endl;
			else cout << "N" << endl;
		}
		else if (strcmp(op, "find_ith") == 0) {
			int temp;
			bool flag = false;
			cin >> temp;
			int i = 1;
			for (auto p = setData.begin(); p != setData.end(); ++p, ++i) {
				if (i == temp) {
					flag = true;
					cout << *p << endl;
					break;
				}
			}
			if (!flag)
				cout << "N" << endl;
		}
	}


	return 0;
}