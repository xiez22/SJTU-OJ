//栈类 By @ligongzzz
//更新时间：2019年2月15日


#include "iostream"
using namespace std;

template <class T>
class mStack {
	class node {
	public:
		T data;
		node* next = nullptr;
	};
	node* head = nullptr;
	size_t _size = 0;

public:
	//构造函数
	mStack() {
		head = new node;
	}
	//判断是否为空
	bool empty() {
		return head->next == nullptr;
	}
	//增加
	void push(const T& val) {
		head->data = val;
		auto temp = new node;
		temp->next = head;
		head = temp;
		++_size;
	}
	//删除
	void pop() {
		//安全措施
		if (head->next == nullptr)
			return;
		auto temp = head->next;
		delete head;
		head = temp;
		--_size;
	}
	//最前
	T & top() {
		//安全措施
		if (head->next == nullptr)
			return;
		return head->next->data;
	}
	//大小
	size_t size() {
		return _size;
	}

	//迭代器
	class iterator {
		node* val = nullptr;
		friend iterator mStack<T>::begin();
		friend iterator mStack<T>::end();
	public:
		iterator() = default;
		iterator(const iterator& other) {
			val = other.val;
		}

		iterator& operator++() {
			//安全措施
			if (val == nullptr)
				return *this;
			val = val->next;
			return *this;
		}
		iterator operator++(int) {
			//安全措施
			if (val == nullptr)
				return *this;
			auto temp = *this;
			val = val->next;
			return temp;
		}
		bool operator==(const iterator & other) const {
			return val == other.val;
		}
		bool operator!=(const iterator & other) const {
			return val != other.val;
		}
		T& operator*() {
			return val->data;
		}
	};
	iterator begin() {
		iterator temp;
		temp.val = head->next;
		return temp;
	}
	iterator end() {
		iterator temp;
		temp.val = nullptr;
		return temp;
	}
};