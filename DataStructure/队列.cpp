//队列类 By @ligongzzz
//更新时间：2019年2月15日


#include "iostream"
#include "queue"
using namespace std;

template <class T>
class mQueue {
	class node {
	public:
		T data;
		node* next = nullptr;
	};
	node *head = nullptr,
		*rear = nullptr;
	size_t _size = 0;

public:
	//构造函数
	mQueue() {
		head = new node;
		rear = head;
	}
	//判断是否为空
	bool empty() {
		return head->next == nullptr;
	}
	//增加
	void push(const T& val) {
		rear->next = new node;
		rear = rear->next;
		rear->data = val;
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
	//大小
	size_t size() {
		return _size;
	}
	//最前
	T& front() {
		//安全措施
		if (head->next == nullptr)
			return;
		return head->next->data;
	}
	//最后
	T& back() {
		//安全措施
		if (head->next == nullptr)
			return;
		return rear->data;
	}
	//迭代器
	class iterator {
		node* val = nullptr;
		friend iterator mQueue<T>::begin();
		friend iterator mQueue<T>::end();
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
		bool operator==(const iterator& other) const{
			return val == other.val;
		}
		bool operator!=(const iterator& other) const {
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