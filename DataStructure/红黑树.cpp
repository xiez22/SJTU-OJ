//红黑树集合类 数据结构模板 By @ligongzzz
//更新时间：2019年2月2日


#include "iostream"
using namespace std;


//红黑树实现
template <class T>
class mSet {
	//颜色枚举类型
	enum colorT { RED, BLACK };

	//结点
	class node {
	public:
		T* data;
		node* lchild = nullptr;
		node* rchild = nullptr;
		node* parent = nullptr;

		colorT color = RED;
	};

	//根节点
	node* root = nullptr;

	//清空
	void clear(node* p) {
		if (p != nullptr) {
			clear(p->lchild);
			clear(p->rchild);
			delete p->data;
			delete p;
		}
		p = nullptr;
	}

	//旋转
	//LL旋转
	void LL(node* gp) {
		auto p = gp->lchild, t = p->lchild;
		if (gp->parent != nullptr) {
			if (gp->parent->lchild == gp)
				gp->parent->lchild = p;
			else
				gp->parent->rchild = p;
		}
		else
			root = p;
		p->parent = gp->parent;
		gp->lchild = p->rchild;
		if (p->rchild != nullptr)
			p->rchild->parent = gp;
		p->rchild = gp;
		gp->parent = p;
		//修改颜色
		auto tmp = gp->color;
		gp->color = p->color;
		p->color = tmp;
		//cout << "LL ";
	}

	//RR旋转
	void RR(node * gp) {
		auto p = gp->rchild, t = p->rchild;
		if (gp->parent != nullptr) {
			if (gp->parent->lchild == gp)
				gp->parent->lchild = p;
			else
				gp->parent->rchild = p;
		}
		else
			root = p;
		p->parent = gp->parent;
		gp->rchild = p->lchild;
		if (p->lchild != nullptr)
			p->lchild->parent = gp;
		p->lchild = gp;
		gp->parent = p;
		//修改颜色
		auto tmp = gp->color;
		gp->color = p->color;
		p->color = tmp;
		//cout << "RR ";
	}

	//LR旋转
	void LR(node * gp) {
		RR(gp->lchild);
		LL(gp);
		//cout << "LR ";
	}

	//RL旋转
	void RL(node * gp) {
		LL(gp->rchild);
		RR(gp);
		//cout << "RL ";
	}

	//插入调整
	void insertAdjust(node * &gp, node * &p, node * t) {
		if (p->color == BLACK) return;
		if (p == root) {
			p->color = BLACK;
			return;
		}
		if (gp->lchild == p) {
			if (p->lchild == t) {
				LL(gp);
				//交换次序
				auto tmp = gp;
				gp = p;
				p = tmp;

			}
			else {
				LR(gp);
				//交换次序
				auto tmp = gp;
				gp = t;
				t = tmp;
			}
		}
		else if (p->rchild == t) {
			RR(gp);
			//交换次序
			auto tmp = gp;
			gp = p;
			p = tmp;
		}
		else {
			RL(gp);
			//交换次序
			auto tmp = gp;
			gp = t;
			t = tmp;
		}
	}

	//删除调整
	void removeAdjust(node * &p, node * &c, node * &t, const T & del) {
		if (c->color == RED) return;
		if (c == root)
			if (c->lchild && c->rchild
				&& c->rchild->color == c->lchild->color) {
				c->color = RED;
				c->lchild->color = c->rchild->color = BLACK;
				return;
			}
		if ((c->lchild && c->lchild->color || c->lchild == nullptr) &&
			(c->rchild && c->rchild->color || c->rchild == nullptr))
			if ((t->lchild && t->lchild->color || t->lchild == nullptr) &&
				(t->rchild && t->rchild->color || t->rchild == nullptr)) {
				p->color = BLACK;
				t->color = c->color = RED;
			}
			else {
				if (p->lchild == t)
					if (t->lchild != nullptr && t->lchild->color == RED) {
						t->lchild->color = BLACK;
						LL(p);
						//交换次序
						t = p;
					}
					else {
						auto tmp = t->rchild;
						LR(p);
						p = tmp;
						p = p->rchild;
						p->color = BLACK;
						t->color = BLACK;
					}
				else if (t->rchild&& t->rchild->color == RED) {
					t->rchild->color = BLACK;
					RR(p);
					t = p;
				}
				else {
					auto tmp = t->lchild;
					RL(p);
					p = tmp;
					p = p->lchild;
					p->color = BLACK;
					t->color = BLACK;
				}
				c->color = RED;
			}
		else {
			if (*c->data == del) {
				if (c->lchild && c->rchild) {
					if (c->rchild->color == BLACK) {
						LL(c);
					}
					return;
				}
				if (c->lchild) {
					LL(c);
					p = c->parent;
				}
				else {
					RR(c);
					p = c->parent;
				}
			}
			else {
				p = c;
				c = del < *p->data ? p->lchild : p->rchild;
				t = c == p->lchild ? p->rchild : p->lchild;
				if (c->color == BLACK) {
					if (t == p->rchild)
						RR(p);
					else
						LL(p);
					t = p;
					t = c == p->lchild ? p->rchild : p->lchild;
					removeAdjust(p, c, t, del);
				}
			}
		}
	}

	//复制
	void copy(node * posDes, node * posSource) {
		posDes->data = new T(*posSource->data);
		posDes->color = posSource->color;
		if (posSource->lchild) {
			posDes->lchild = new node;
			posDes->lchild->parent = posDes;
			copy(posDes->lchild, posSource->lchild);
		}
		if (posSource->rchild) {
			posDes->rchild = new node;
			posDes->rchild->parent = posDes;
			copy(posDes->rchild, posSource->rchild);
		}
	}

public:
	//迭代器
	class iterator {
		node* currentData = nullptr;
		friend iterator mSet::begin();
		friend iterator mSet::find(const T&);
		friend void mSet::erase(const iterator&);

	public:
		iterator() = default;

		iterator(const iterator& b) {
			currentData = new node;
			currentData = b.currentData;
		}

		T& get() {
			return *currentData->data;
		}
		//遍历结束或内容为空
		bool finish() {
			return currentData == nullptr;
		}

		//重载++i
		iterator& operator++() {
			if (currentData == nullptr)
				return *this;
			//假如有右孩子
			if (currentData->rchild != nullptr) {
				for (currentData = currentData->rchild; currentData->lchild != nullptr;)
					currentData = currentData->lchild;
			}
			//假如是落单的根节点
			else if (currentData->parent == nullptr) {
				currentData = nullptr;
			}
			//假如是左叶子
			else if (currentData->parent->lchild == currentData)
				currentData = currentData->parent;
			//假如是右叶子
			else {
				auto last = currentData;
				for (currentData = currentData->parent;
					currentData != nullptr && currentData->rchild == last;
					currentData = currentData->parent)
					last = currentData;
			}
			return *this;
		}

		//重载i++
		iterator operator++(int) {
			auto temp = *this;
			if (currentData == nullptr)
				return temp;
			//假如有右孩子
			if (currentData->rchild != nullptr) {
				for (currentData = currentData->rchild; currentData->lchild != nullptr;)
					currentData = currentData->lchild;
			}
			//假如是落单的根节点
			else if (currentData->parent == nullptr) {
				currentData = nullptr;
			}
			//假如是左叶子
			else if (currentData->parent->lchild == currentData)
				currentData = currentData->parent;
			//假如是右叶子
			else {
				auto last = currentData;
				for (currentData = currentData->parent;
					currentData != nullptr && currentData->rchild == last;
					currentData = currentData->parent)
					last = currentData;
			}
			return temp;
		}

		//重载取值符号
		T& operator*() const {
			if (currentData == nullptr)
				return *new T;
			else
				return *currentData->data;
		}

		//重载==符号
		bool operator==(const iterator & b) const {
			return currentData == b.currentData;
		}

		//重载!=符号
		bool operator!=(const iterator & b) const {
			return currentData != b.currentData;
		}
	};

	//查找
	iterator find(const T & num) {
		iterator ans;
		auto p = root;
		while (p != nullptr && *p->data != num)
			if (*p->data > num)
				p = p->lchild;
			else
				p = p->rchild;

		ans.currentData = p;
		return ans;
	}

	//清空
	void clear() {
		clear(root);
	}

	//插入
	void insert(const T & x) {
		node* t, * parent, * grandp;

		//在空树上插入
		if (root == nullptr) {
			root = new node;
			root->color = BLACK;
			root->data = new T(x);
			return;
		}

		parent = grandp = t = root;
		while (true) {
			if (t != nullptr) {
				if (t->lchild&& t->lchild->color == RED &&
					t->rchild && t->rchild->color == RED) {
					t->lchild->color = t->rchild->color = BLACK;
					t->color = RED;
					insertAdjust(grandp, parent, t);
				}
				grandp = parent;
				parent = t;
				t = *t->data > x ? t->lchild : t->rchild;
			}
			else {
				t = new node;
				t->data = new T(x);
				t->parent = parent;
				if (x < *parent->data)
					parent->lchild = t;
				else
					parent->rchild = t;
				insertAdjust(grandp, parent, t);
				root->color = BLACK;
				return;
			}
		}
	}

	//查找删除
	void remove(const T & x) {
		T del = x;
		node* t, * p, * c;

		if (root == nullptr) return;
		if (*root->data == x && root->lchild == nullptr && root->rchild == nullptr) {
			delete root;
			root = nullptr;
			return;
		}

		p = c = t = root;
		while (true) {
			removeAdjust(p, c, t, del);
			if (*c->data == del && c->lchild && c->rchild) {
				auto tmp = c->rchild;
				while (tmp->lchild)
					tmp = tmp->lchild;
				c->data = tmp->data;
				del = *tmp->data;
				p = c;
				c = c->rchild;
				t = p->lchild;
				continue;
			}

			if (*c->data == del) {
				if (p->lchild == c)
					p->lchild = nullptr;
				else
					p->rchild = nullptr;
				delete c;
				root->color = BLACK;
				return;
			}
			p = c;
			c = del < *p->data ? p->lchild : p->rchild;
			t = c == p->lchild ? p->rchild : p->lchild;
		}
	}

	//迭代器擦除
	void erase(const iterator & x) {
		//判断是否为空
		if (x.currentData == nullptr)
			return;

		T * del = x.currentData->data;
		node * t, *p, *c;

		if (root == nullptr) return;
		if (root->data == del && root->lchild == nullptr && root->rchild == nullptr) {
			delete root;
			root = nullptr;
			return;
		}

		p = c = t = root;
		while (true) {
			removeAdjust(p, c, t, *del);
			if (c->data == del && c->lchild && c->rchild) {
				auto tmp = c->rchild;
				while (tmp->lchild)
					tmp = tmp->lchild;
				if (tmp->parent != c) {
					auto temp = *tmp;
					tmp->parent = c->parent;
					if (tmp->parent)
						if (tmp->parent->lchild == c)
							tmp->parent->lchild = tmp;
						else tmp->parent->rchild = tmp;
					else root = tmp;
					tmp->lchild = c->lchild;
					if (c->lchild) c->lchild->parent = tmp;
					tmp->rchild = c->rchild;
					if (c->rchild) c->rchild->parent = tmp;
					tmp->color = c->color;

					c->parent = temp.parent;
					if (temp.parent->lchild == tmp)
						temp.parent->lchild = c;
					else temp.parent->rchild = c;
					c->lchild = temp.lchild;
					if (c->lchild) c->lchild->parent = c;
					c->rchild = temp.rchild;
					if (c->rchild) c->rchild->parent = c;
					c->color = temp.color;
				}
				else {
					auto temp = *tmp;
					tmp->parent = c->parent;
					if (tmp->parent)
						if (tmp->parent->lchild == c)
							tmp->parent->lchild = tmp;
						else tmp->parent->rchild = tmp;
					else root = tmp;
					if (c->lchild == tmp) {
						tmp->lchild = c;
						tmp->rchild = c->rchild;
						if (c->rchild) tmp->rchild->parent = tmp;
					}
					else {
						tmp->rchild = c;
						tmp->lchild = c->lchild;
						if (c->lchild) tmp->lchild->parent = tmp;
					}
					c->parent = tmp;
					c->lchild = temp.lchild;
					c->rchild = temp.rchild;
					if (c->lchild) c->lchild->parent = c;
					if (c->rchild) c->rchild->parent = c;
					tmp->color = c->color;
					c->color = temp.color;
				}

				p = c = tmp;
				c = c->rchild;
				t = p->lchild;
				continue;
			}

			if (c->data == del) {
				if (p->lchild == c)
					p->lchild = nullptr;
				else
					p->rchild = nullptr;
				delete c;
				root->color = BLACK;
				return;
			}
			p = c;
			c = *del < *p->data ? p->lchild : p->rchild;
			t = c == p->lchild ? p->rchild : p->lchild;
		}
	}

	void erase(const iterator & from, const iterator & to) {
		if (from == end()) return;
		for (auto p = from; p != to;)
			erase(p++);
	}

	//迭代器起始
	iterator begin() {
		iterator result;
		auto p = root;
		if (p != nullptr)
			for (; p->lchild != nullptr;) {
				p = p->lchild;
			}
		result.currentData = p;
		return result;
	}

	//迭代器结束
	iterator end() {
		return *new iterator;
	}

	//重载赋值符号
	mSet<T> operator=(const mSet<T> & b) {
		clear();
		root = nullptr;
		if (b.root == nullptr)
			return *this;
		root = new node;
		copy(root, b.root);
		return *this;
	}

	//检查是否合法
	int check(node * pos) {
		int left = 0, right = 0;
		if (pos->lchild != nullptr)
			left = check(pos->lchild);
		if (pos->rchild != nullptr)
			right = check(pos->rchild);
		if (left < 0 || right < 0 || left != right)
			return -1;
		if (pos->color == BLACK)
			return 1 + left;
		else return left;
	}

	void check() {
		if (root == nullptr || check(root) > 0)
			cout << "检查合格！" << endl;
		else
			cout << "检查不合格！" << endl;
	}
};