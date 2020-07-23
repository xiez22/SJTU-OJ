//列表类 By @ligongzzz
//更新时间：2019年3月8日


#include "iostream"
#include "list"
using namespace std;

template <class T>
class mList {
	class node {
	public:
		T val;
		node* next = nullptr;//ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccx
		node* last = nullptr;
	};
	node* head = nullptr;
	node* rear = nullptr;
	size_t _size = 0;

	//清空
	void clear() {
		for (auto p = head; p;) {
			auto temp = p->next;
			delete p;
			p = temp;
		}
		_size = 0;
	}
	//创建
	void create_new() {
		head = new node;
		rear = new node;
		head->next = rear;
		rear->last = head;
		_size = 0;
	}

public:
	//构造函数
	mList() {
		create_new();
	}
	~mList() {
		clear();
	}
	mList(const mList<T>& other) {
		if (&other == this)
			return;

		clear();
		head = new node;

		auto p1 = head;
		for (auto p2 = other.head; p2->next; p1 = p1->next, p2 = p2->next) {
			p1->next = new node;
			p1->next->val = p2->next->val;
			p1->next->last = p1;
		}
		rear = p1;
	}

	//压入与弹出
	void push_back(const T& val) {
		rear->val = val;
		rear->next = new node;
		rear->next->last = rear;
		rear = rear->next;
		++_size;
	}

	void pop_back() {
		//保护
		if (_size <= 0)
			return;
		rear->last = rear->last->last;
		delete rear->last->next;
		rear->last->next = rear;
		--_size;
	}

	void push_front(const T& val) {
		head->val = val;
		head->last = new node;
		head->last->next = head;
		head = head->last;
		++_size;
	}

	void pop_front() {
		//保护
		if (_size <= 0)
			return;
		head->next = head->next->next;
		delete head->next->last;
		head->next->last = head;
		--_size;
	}

	size_t size() {
		return _size;
	}

	bool empty() {
		return _size <= 0;
	}

	//迭代器
	class iterator {
	public:
		node* pos = nullptr;
		iterator& operator++() {
			if (pos->next)
				pos = pos->next;
			return *this;
		}
		iterator operator++(int) {
			auto temp = *this;
			if (pos->next)
				pos = pos->next;
			return temp;
		}
		iterator& operator--() {
			if (pos->last)
				pos = pos->last;
			return *this;
		}
		iterator operator--(int) {
			auto temp = *this;
			if (pos->last)
				pos = pos->last;
			return temp;
		}
		T& operator*() {
			return pos->val;
		}
		bool operator==(const iterator& other) {
			return pos == other.pos;
		}
		bool operator!=(const iterator& other) {
			return pos != other.pos;
		}
	};

	iterator begin() {
		iterator result;
		result.pos = head->next;
		return result;
	}

	iterator end() {
		iterator result;
		result.pos = rear;
		return result;
	}

	//反向迭代器
	class reverse_iterator {
	public:
		node* pos = nullptr;

		iterator base() {
			iterator result;
			result.pos = pos;
			return result;
		}
		reverse_iterator& operator++() {
			if (pos->last)
				pos = pos->last;
			return *this;
		}
		reverse_iterator operator++(int) {
			auto temp = *this;
			if (pos->last)
				pos = pos->last;
			return temp;
		}
		reverse_iterator& operator--() {
			if (pos->next)
				pos = pos->next;
			return *this;
		}
		reverse_iterator operator--(int) {
			auto temp = *this;
			if (pos->next)
				pos = pos->next;
			return temp;
		}
		T& operator*() {
			return pos->val;
		}
		bool operator==(const reverse_iterator& other) {
			return pos == other.pos;
		}
		bool operator!=(const reverse_iterator& other) {
			return pos != other.pos;
		}
	};

	reverse_iterator rbegin() {
		reverse_iterator result;
		result.pos = rear->last;
		return result;
	}

	reverse_iterator rend() {
		reverse_iterator result;
		result.pos = head;
		return result;
	}

	//插入
	void insert(const iterator& pos, const T& val) {
		auto temp = new node;
		temp->val = val;
		temp->next = pos.pos->next;
		temp->next->last = temp;
		pos.pos->next = temp;
		temp->last = pos.pos;
		++_size;
	}

	//删除
	void erase(const iterator& pos) {
		pos.pos->next->last = pos.pos->last;
		pos.pos->last->next = pos.pos->next;
		delete pos.pos;
		--_size;
	}
	void erase(const iterator& from, const iterator& to) {
		from.pos->last->next = to.pos;
		to.pos->last = from.pos;
		for (auto p = from.pos; p != to.pos;) {
			auto temp = p->next;
			delete p;
			p = temp;
		}
	}
};

