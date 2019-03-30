#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"
#include <cmath>
#include <cstddef>

namespace sjtu {

	template<class T>
	class deque {
	private:
		class node {
		public:
			T** val = nullptr;
			node* next = nullptr;
			node* last = nullptr;
			size_t _size = 0;
			size_t _start = 0;
			size_t _capacity = 0;

			~node() {
				for (auto i = _start; i < _start + _size; ++i)
					delete val[i % _capacity];
				if (val)
					delete[] val;
			}
		};
		node* head = nullptr;
		node* rear = nullptr;
		size_t _size = 0;

		//扩大函数
		//扩大时，环形数组start变为0，并且capacity变成(capacity+1)*2，数据指针保持不变
		void double_space(node* origin) {
			//创建新的大数组
			auto temp = new T * [(origin->_capacity + 1) * 2];
			//复制
			for (size_t i = 0; i < origin->_size; ++i)
				temp[i] = origin->val[(origin->_start + i) % origin->_capacity];
			//如果原来得val指针不为空，则析构
			if (origin->val)
				delete[] origin->val;
			//将临时数组赋值给原数组
			origin->val = temp;
			origin->_start = 0;
			origin->_capacity = (origin->_capacity + 1) * 2;
		}

		//分割函数
		//将原来的block一分为二，保持每个块的capacity不变，数据指针保持不变
		//分割时，保持前半部分不变，后半部分会进行一次循环赋值过程，后半部分start从0开始
		//前半部分被移动的指针将会初始化为nullptr以确保安全
		void devide_space(node * origin) {
			//创建一个新的node
			auto new_node = new node;
			new_node->last = origin;
			new_node->next = origin->next;
			new_node->next->last = new_node;
			origin->next = new_node;

			new_node->_capacity = origin->_capacity;
			new_node->val = new T * [new_node->_capacity];
			new_node->_size = origin->_size - (origin->_size >> 1);
			origin->_size >>= 1;
			new_node->_start = 0;
			for (size_t i = 0; i < new_node->_size; ++i) {
				new_node->val[i] = origin->val[(origin->_start + origin->_size + i) % origin->_capacity];
				origin->val[(origin->_start + origin->_size + i) % origin->_capacity] = nullptr;
			}
		}

		//合并函数
		//将指针指向的块与右边的块进行合并，装入全新的块，capacity为原来size之和的两倍，数据指针保持不变
		void merge_space(node * left) {
			//创建一个新的数组
			auto new_val = new T * [(left->_size + left->next->_size) * 2];
			for (size_t i = 0; i < left->_size; ++i) {
				new_val[i] = left->val[(left->_start + i) % left->_capacity];
				left->val[(left->_start + i) % left->_capacity] = nullptr;
			}
			for (size_t i = 0; i < left->next->_size; ++i) {
				new_val[left->_size + i] = left->next->val[(left->next->_start + i) % left->next->_capacity];
				left->next->val[(left->next->_start + i) % left->next->_capacity] = nullptr;
			}
			//调整大小
			left->_start = 0;
			left->_size = left->_size + left->next->_size;
			left->_capacity = left->_size * 2;
			if (left->val)
				delete[] left->val;
			left->val = new_val;
			left->next = left->next->next;
			delete left->next->last;
			left->next->last = left;
		}

	public:
		class const_iterator;
		class iterator {
		private:
			/**
			 * TODO add data members
			 *   just add whatever you want.
			 */
			friend iterator sjtu::deque<T>::begin();
			friend iterator sjtu::deque<T>::end();
			friend iterator sjtu::deque<T>::insert(iterator pos, const T& value);
			friend iterator sjtu::deque<T>::erase(iterator pos);

			friend class sjtu::deque<T>::const_iterator;

			//保存当前的deque的head指针和rear指针
			node* cur_head = nullptr;
			node* cur_rear = nullptr;

			//保存当前结点指针
			node* cur_node = nullptr;

			//保存当前的位置
			size_t cur_pos = 0;
		public:
			/**
			 * return a new iterator which pointer n-next elements
			 *   even if there are not enough elements, the behaviour is **undefined**.
			 * as well as operator-
			 */
			iterator operator+(const int& n) const {
				//TODO
				if (n == 0)
					return *this;
				if (n < 0)
					return *this - (-n);
				//判断是否越出本区块
				auto temp = *this;
				if (temp.cur_pos + (size_t)n < temp.cur_node->_size)
					temp.cur_pos += n;
				else {
					size_t pos = temp.cur_node->_size - temp.cur_pos;
					temp.cur_node = temp.cur_node->next;
					temp.cur_pos = 0;

					for (; temp.cur_node != temp.cur_rear && temp.cur_node->_size + pos <= (size_t)n;
						pos += temp.cur_node->_size, temp.cur_node = temp.cur_node->next);
					temp.cur_pos = n - pos;
				}
				return temp;
			}
			iterator operator-(const int& n) const {
				//TODO
				if (n == 0)
					return *this;
				if (n < 0)
					return *this + (-n);
				//判断是否越出本区块
				auto temp = *this;
				if (temp.cur_pos >= (size_t)n)
					temp.cur_pos -= n;
				else {
					size_t pos = temp.cur_pos;
					temp.cur_node = temp.cur_node->last;
					for (; temp.cur_node != temp.cur_head && temp.cur_node->_size + pos < (size_t)n;
						pos += temp.cur_node->_size, temp.cur_node = temp.cur_node->last);
					temp.cur_pos = temp.cur_node->_size + pos - n;
				}
				return temp;
			}
			// return th distance between two iterator,
			// if these two iterators points to different vectors, throw invaild_iterator.
			int operator-(const iterator & rhs) const {
				//TODO
				if (cur_head != rhs.cur_head)
					throw invalid_iterator();
				//回溯到head
				size_t this_pos = cur_pos, rhs_pos = rhs.cur_pos;
				for (auto p = cur_node->last; p != cur_head; this_pos += p->_size, p = p->last);
				for (auto p = rhs.cur_node->last; p != cur_head; rhs_pos += p->_size, p = p->last);
				return (int)this_pos - (int)rhs_pos;
			}
			iterator operator+=(const int& n) {
				//TODO
				*this = *this + n;
				return *this;
			}
			iterator operator-=(const int& n) {
				//TODO
				*this = *this - n;
				return *this;
			}
			/**
			 * TODO iter++
			 */
			iterator operator++(int) {
				if (cur_node == cur_rear)
					return *this;
				auto temp = *this;
				if (cur_pos < cur_node->_size - 1)
					++cur_pos;
				else {
					cur_node = cur_node->next;
					cur_pos = 0;
				}
				return temp;
			}
			/**
			 * TODO ++iter
			 */
			iterator& operator++() {
				if (cur_node == cur_rear)
					return *this;
				if (cur_pos < cur_node->_size - 1)
					++cur_pos;
				else {
					cur_node = cur_node->next;
					cur_pos = 0;
				}
				return *this;
			}
			/**
			 * TODO iter--
			 */
			iterator operator--(int) {
				auto temp = *this;
				if (cur_pos > 0)
					--cur_pos;
				else {
					cur_node = cur_node->last;
					if (cur_node == cur_head)
						cur_pos = 0;
					else
						cur_pos = cur_node->_size - 1;
				}
				return temp;
			}
			/**
			 * TODO --iter
			 */
			iterator& operator--() {
				if (cur_pos > 0)
					--cur_pos;
				else {
					cur_node = cur_node->last;
					if (cur_node == cur_head)
						cur_pos = 0;
					else
						cur_pos = cur_node->_size - 1;
				}
				return *this;
			}
			/**
			 * TODO *it
			 */
			T& operator*() const {
				if (cur_pos >= cur_node->_size)
					throw invalid_iterator();
				return *cur_node->val[(cur_node->_start + cur_pos) % cur_node->_capacity];
			}
			/**
			 * TODO it->field
			 */
			T* operator->() const noexcept {
				return cur_node->val[(cur_node->_start + cur_pos) % cur_node->_capacity];
			}
			/**
			 * a operator to check whether two iterators are same (pointing to the same memory).
			 */
			bool operator==(const iterator & rhs) const {
				return cur_node == rhs.cur_node && cur_pos == rhs.cur_pos;
			}
			bool operator==(const const_iterator & rhs) const {
				return cur_node == rhs.cur_node && cur_pos == rhs.cur_pos;
			}
			/**
			 * some other operator for iterator.
			 */
			bool operator!=(const iterator & rhs) const {
				return cur_node != rhs.cur_node || cur_pos != rhs.cur_pos;
			}
			bool operator!=(const const_iterator & rhs) const {
				return cur_node != rhs.cur_node || cur_pos != rhs.cur_pos;
			}
		};
		class const_iterator {
			// it should has similar member method as iterator.
			//  and it should be able to construct from an iterator.
			friend class sjtu::deque<T>::iterator;

			friend const_iterator sjtu::deque<T>::cbegin() const;
			friend const_iterator sjtu::deque<T>::cend() const;
		private:
			// data members.
			//保存当前的deque的head指针和rear指针
			node* cur_head = nullptr;
			node* cur_rear = nullptr;

			//保存当前结点指针
			node* cur_node = nullptr;

			//保存当前的位置
			size_t cur_pos = 0;

		public:
			const_iterator() {
				// TODO
			}
			const_iterator(const const_iterator& other) {
				// TODO
				cur_head = other.cur_head;
				cur_node = other.cur_node;
				cur_pos = other.cur_pos;
				cur_rear = other.cur_rear;
			}
			const_iterator(const iterator& other) {
				// TODO
				cur_head = other.cur_head;
				cur_node = other.cur_node;
				cur_pos = other.cur_pos;
				cur_rear = other.cur_rear;
			}
			// And other methods in iterator.
			// And other methods in iterator.
			// And other methods in iterator.
			const_iterator operator+(const int& n) const {
				//TODO
				if (n == 0)
					return *this;
				if (n < 0)
					return *this - (-n);
				//判断是否越出本区块
				auto temp = *this;
				if (temp.cur_pos + (size_t)n < temp.cur_node->_size)
					temp.cur_pos += n;
				else {
					size_t pos = temp.cur_node->_size - temp.cur_pos;
					temp.cur_node = temp.cur_node->next;
					temp.cur_pos = 0;

					for (; temp.cur_node != temp.cur_rear && temp.cur_node->_size + pos <= (size_t)n;
						pos += temp.cur_node->_size, temp.cur_node = temp.cur_node->next);
					temp.cur_pos = n - pos;
				}
				return temp;
			}
			const_iterator operator-(const int& n) const {
				//TODO
				if (n == 0)
					return *this;
				if (n < 0)
					return *this + (-n);
				//判断是否越出本区块
				auto temp = *this;
				if (temp.cur_pos >= (size_t)n)
					temp.cur_pos -= n;
				else {
					size_t pos = temp.cur_pos;
					temp.cur_node = temp.cur_node->last;
					for (; temp.cur_node != temp.cur_head && temp.cur_node->_size + pos < (size_t)n;
						pos += temp.cur_node->_size, temp.cur_node = temp.cur_node->last);
					temp.cur_pos = temp.cur_node->_size + pos - n;
				}
				return temp;
			}
			// return th distance between two iterator,
			// if these two iterators points to different vectors, throw invaild_iterator.
			int operator-(const const_iterator & rhs) const {
				//TODO
				if (cur_head != rhs.cur_head)
					throw invalid_iterator();
				//回溯到head
				size_t this_pos = cur_pos, rhs_pos = rhs.cur_pos;
				for (auto p = cur_node->last; p != cur_head; this_pos += p->_size, p = p->last);
				for (auto p = rhs.cur_node->last; p != cur_head; rhs_pos += p->_size, p = p->last);
				return (int)this_pos - (int)rhs_pos;
			}
			const_iterator operator+=(const int& n) {
				//TODO
				*this = *this + n;
				return *this;
			}
			const_iterator operator-=(const int& n) {
				//TODO
				*this = *this - n;
				return *this;
			}
			/**
			 * TODO iter++
			 */
			const_iterator operator++(int) {
				if (cur_node == cur_rear)
					return *this;
				auto temp = *this;
				if (cur_pos < cur_node->_size - 1)
					++cur_pos;
				else {
					cur_node = cur_node->next;
					cur_pos = 0;
				}
				return temp;
			}
			/**
			 * TODO ++iter
			 */
			const_iterator& operator++() {
				if (cur_node == cur_rear)
					return *this;
				if (cur_pos < cur_node->_size - 1)
					++cur_pos;
				else {
					cur_node = cur_node->next;
					cur_pos = 0;
				}
				return *this;
			}
			/**
			 * TODO iter--
			 */
			const_iterator operator--(int) {
				auto temp = *this;
				if (cur_pos > 0)
					--cur_pos;
				else {
					cur_node = cur_node->last;
					if (cur_node == cur_head)
						cur_pos = 0;
					else
						cur_pos = cur_node->_size - 1;
				}
				return temp;
			}
			/**
			 * TODO --iter
			 */
			const_iterator& operator--() {
				if (cur_pos > 0)
					--cur_pos;
				else {
					cur_node = cur_node->last;
					if (cur_node == cur_head)
						cur_pos = 0;
					else
						cur_pos = cur_node->_size - 1;
				}
				return *this;
			}
			/**
			 * TODO *it
			 */
			T& operator*() const {
				if (cur_pos >= cur_node->_size)
					throw invalid_iterator();
				return *cur_node->val[(cur_node->_start + cur_pos) % cur_node->_capacity];
			}
			/**
			 * TODO it->field
			 */
			T* operator->() const noexcept {
				return cur_node->val[(cur_node->_start + cur_pos) % cur_node->_capacity];
			}
			/**
			 * a operator to check whether two iterators are same (pointing to the same memory).
			 */
			bool operator==(const iterator & rhs) const {
				return cur_node == rhs.cur_node && cur_pos == rhs.cur_pos;
			}
			bool operator==(const const_iterator & rhs) const {
				return cur_node == rhs.cur_node && cur_pos == rhs.cur_pos;
			}
			/**
			 * some other operator for iterator.
			 */
			bool operator!=(const iterator & rhs) const {
				return cur_node != rhs.cur_node || cur_pos != rhs.cur_pos;
			}
			bool operator!=(const const_iterator & rhs) const {
				return cur_node != rhs.cur_node || cur_pos != rhs.cur_pos;
			}
		};
		/**
		 * TODO Constructors
		 */
		deque() :_size(0) {
			head = new node;
			head->next = rear = new node;
			rear->last = head;
		}
		deque(const deque & other) {
			if (head == other.head)
				return;
			clear();
			auto p1 = head;
			for (auto p2 = other.head; p2->next != other.rear; p1 = p1->next, p2 = p2->next) {
				p1->next = new node;
				p1->next->last = p1;
				p1->next->val = new T * [p2->next->_capacity];
				p1->next->_size = p2->next->_size;
				p1->next->_capacity = p2->next->_capacity;
				p1->next->_start = p2->next->_start;
				for (size_t i = p1->next->_start; i < p1->next->_start + p1->next->_size; ++i)
					p1->next->val[i % p1->next->_capacity] = new T(*p2->next->val[i % p2->next->_capacity]);
			}
			_size = other._size;
			p1->next = rear;
			rear->last = p1;
		}
		/**
		 * TODO Deconstructor
		 */
		~deque() {
			for (auto p = head; p; ) {
				auto temp = p;
				p = p->next;
				delete temp;
			}
		}
		/**
		 * TODO assignment operator
		 */
		deque& operator=(const deque & other) {
			if (head == other.head)
				return *this;
			clear();
			auto p1 = head;
			for (auto p2 = other.head; p2->next != other.rear; p1 = p1->next, p2 = p2->next) {
				p1->next = new node;
				p1->next->last = p1;
				p1->next->val = new T * [p2->next->_capacity];
				p1->next->_size = p2->next->_size;
				p1->next->_capacity = p2->next->_capacity;
				p1->next->_start = p2->next->_start;
				for (size_t i = p1->next->_start; i < p1->next->_start + p1->next->_size; ++i)
					p1->next->val[i % p1->next->_capacity] = new T(*p2->next->val[i % p2->next->_capacity]);
			}
			_size = other._size;
			p1->next = rear;
			rear->last = p1;
			return *this;
		}
		/**
		 * access specified element with bounds checking
		 * throw index_out_of_bound if out of bound.
		 */
		T& at(const size_t & pos) {
			if (pos < 0 || pos >= _size)
				throw index_out_of_bound();
			//遍历
			size_t cur_pos = 0;
			auto p = head->next;
			for (; cur_pos + p->_size <= pos; cur_pos += p->_size, p = p->next);
			return *p->val[(p->_start + pos - cur_pos) % p->_capacity];
		}
		const T & at(const size_t & pos) const {
			if (pos < 0 || pos >= _size)
				throw index_out_of_bound();
			//遍历
			size_t cur_pos = 0;
			auto p = head->next;
			for (; cur_pos + p->_size <= pos; cur_pos += p->_size, p = p->next);
			return *p->val[(p->_start + pos - cur_pos) % p->_capacity];
		}
		T & operator[](const size_t & pos) {
			if (pos < 0 || pos >= _size)
				throw index_out_of_bound();
			//遍历
			size_t cur_pos = 0;
			auto p = head->next;
			for (; cur_pos + p->_size <= pos; cur_pos += p->_size, p = p->next);
			return *p->val[(p->_start + pos - cur_pos) % p->_capacity];
		}
		const T & operator[](const size_t & pos) const {
			if (pos < 0 || pos >= _size)
				throw index_out_of_bound();
			//遍历
			size_t cur_pos = 0;
			auto p = head->next;
			for (; cur_pos + p->_size <= pos; cur_pos += p->_size, p = p->next);
			return *p->val[(p->_start + pos - cur_pos) % p->_capacity];
		}
		/**
		 * access the first element
		 * throw container_is_empty when the container is empty.
		 */
		const T & front() const {
			if (_size == 0)
				throw container_is_empty();
			return *head->next->val[head->next->_start];
		}
		/**
		 * access the last element
		 * throw container_is_empty when the container is empty.
		 */
		const T& back() const {
			if (_size == 0)
				throw container_is_empty();
			return *rear->last->val[(rear->last->_start + rear->last->_size - 1) % rear->last->_capacity];
		}
		/**
		 * returns an iterator to the beginning.
		 */
		iterator begin() {
			iterator temp;
			temp.cur_head = head;
			temp.cur_rear = rear;
			temp.cur_node = head->next;
			temp.cur_pos = 0;
			return temp;
		}
		const_iterator cbegin() const {
			const_iterator temp;
			temp.cur_head = head;
			temp.cur_rear = rear;
			temp.cur_node = head->next;
			temp.cur_pos = 0;
			return temp;
		}
		/**
		 * returns an iterator to the end.
		 */
		iterator end() {
			iterator temp;
			temp.cur_head = head;
			temp.cur_rear = rear;
			temp.cur_node = rear;
			temp.cur_pos = 0;
			return temp;
		}
		const_iterator cend() const {
			const_iterator temp;
			temp.cur_head = head;
			temp.cur_rear = rear;
			temp.cur_node = rear;
			temp.cur_pos = 0;
			return temp;
		}
		/**
		 * checks whether the container is empty.
		 */
		bool empty() const {
			return _size == 0;
		}
		/**
		 * returns the number of elements
		 */
		size_t size() const {
			return _size;
		}
		/**
		 * clears the contents
		 */
		void clear() {
			if (!head) {
				head = new node;
				rear = new node;
				head->next = rear;
				rear->last = head;
				_size = 0;
			}
			else {
				for (auto p = head->next; p != rear;) {
					auto temp = p;
					p = p->next;
					delete temp;
				}
				_size = 0;
				head->next = rear;
				rear->last = head;
			}
		}
		/**
		 * inserts elements at the specified locat on in the container.
		 * inserts value before pos
		 * returns an iterator pointing to the inserted value
		 *     throw if the iterator is invalid or it point to a wrong place.
		 */
		iterator insert(iterator pos, const T & value) {
			//特殊情况（在end添加时调用push_back)
			if (pos == end()) {
				push_back(value);
				pos.cur_node = pos.cur_node->last;
				pos.cur_pos = pos.cur_node->_size - 1;
				return pos;
			}
			if (pos.cur_head != head || pos.cur_pos >= pos.cur_node->_size)
				throw invalid_iterator();
			//判断是否需要扩大
			if (pos.cur_node->_size >= pos.cur_node->_capacity) {
				double_space(pos.cur_node);
			}
			iterator temp;
			temp.cur_head = head;
			temp.cur_node = pos.cur_node;
			temp.cur_pos = pos.cur_pos;
			temp.cur_rear = temp.cur_rear;
			//复制
			for (size_t i = pos.cur_node->_size + pos.cur_node->_start; i > pos.cur_pos + pos.cur_node->_start; --i)
				pos.cur_node->val[i % pos.cur_node->_capacity] = pos.cur_node->val[(i - 1) % pos.cur_node->_capacity];
			temp.cur_node->val[(temp.cur_pos + temp.cur_node->_start) % pos.cur_node->_capacity] = new T(value);
			++temp.cur_node->_size;
			++_size;
			//判断是否需要分裂
			if (temp.cur_node->_size > 2 * (size_t)sqrt(_size)) {
				devide_space(temp.cur_node);
			}
			if (temp.cur_pos >= temp.cur_node->_size) {
				temp.cur_pos -= temp.cur_node->_size;
				temp.cur_node = temp.cur_node->next;
			}
			return temp;
		}
		/**
		 * removes specified element at pos.
		 * removes the element at pos.
		 * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
		 * throw if the container is empty, the iterator is invalid or it points to a wrong place.
		 */
		iterator erase(iterator pos) {
			if (_size == 0)
				throw container_is_empty();
			if (pos.cur_head != head || pos.cur_pos >= pos.cur_node->_size)
				throw invalid_iterator();

			//删除
			delete pos.cur_node->val[(pos.cur_pos + pos.cur_node->_start) % pos.cur_node->_capacity];
			//复制
			for (size_t i = pos.cur_pos + pos.cur_node->_start + 1;
				i < pos.cur_node->_size + pos.cur_node->_start; ++i)
				pos.cur_node->val[(i - 1) % pos.cur_node->_capacity] = pos.cur_node->val[i % pos.cur_node->_capacity];

			--pos.cur_node->_size;
			--_size;
			if (pos.cur_node->_size == 0) {
				//清空该节点
				auto temp = pos.cur_node->next;
				pos.cur_node->next->last = pos.cur_node->last;
				pos.cur_node->last->next = pos.cur_node->next;
				delete pos.cur_node;
				pos.cur_node = temp;
				pos.cur_pos = 0;
			}
			//合并结点
			else if (pos.cur_node->next != rear && pos.cur_node->_size + pos.cur_node->next->_size < (size_t)sqrt(_size)) {
				merge_space(pos.cur_node);
			}
			//移动迭代器
			else if (pos.cur_pos == pos.cur_node->_size) {
				pos.cur_node = pos.cur_node->next;
				pos.cur_pos = 0;
			}
			return pos;
		}
		/**
		 * adds an element to the end
		 */
		void push_back(const T & value) {
			//判断是否为空
			if (_size == 0) {
				//新建一个块
				auto new_block = new node;
				new_block->next = rear;
				rear->last = new_block;
				head->next = new_block;
				new_block->last = head;
			}
			//判断是否可在当前块插入
			auto p = rear->last;
			if (p->_size < p->_capacity) {
				//直接插入
				p->val[(p->_start + p->_size) % p->_capacity] = new T(value);
				++p->_size;
			}
			else {
				//扩大
				double_space(p);
				//插入
				p->val[(p->_start + p->_size) % p->_capacity] = new T(value);
				++p->_size;
			}
			++_size;
			//判断是否需要分割
			if (p->_size > 2 * (size_t)sqrt(_size))
				devide_space(p);
		}
		/**
		 * removes the last element
		 *     throw when the container is empty.
		 */
		void pop_back() {
			if (_size == 0)
				throw container_is_empty();
			//弹出最后一个元素
			--_size;
			delete rear->last->val[(rear->last->_start + rear->last->_size - 1) % rear->last->_capacity];
			--rear->last->_size;
			//判断是否为空
			if (rear->last->_size == 0) {
				rear->last = rear->last->last;
				delete rear->last->next;
				rear->last->next = rear;
			}
			//判断是否需要合并
			else if (rear->last->_size + rear->last->last->_size < (size_t)sqrt(_size))
				merge_space(rear->last->last);
		}
		/**
		 * inserts an element to the beginning.
		 */
		void push_front(const T & value) {
			//判断是否为空
			if (_size == 0) {
				//新建一个块
				auto new_block = new node;
				new_block->next = rear;
				rear->last = new_block;
				head->next = new_block;
				new_block->last = head;
			}
			//判断是否可在当前块插入
			auto p = head->next;
			if (p->_size < p->_capacity) {
				//直接插入
				p->_start = (p->_capacity + p->_start - 1) % p->_capacity;
				p->val[p->_start] = new T(value);
				++p->_size;
			}
			else {
				//扩大
				double_space(p);
				//插入
				p->_start = (p->_capacity + p->_start - 1) % p->_capacity;
				p->val[p->_start] = new T(value);
				++p->_size;
			}
			++_size;
			//判断是否需要分割
			if (p->_size > 2 * (size_t)sqrt(_size))
				devide_space(p);
		}
		/**
		 * removes the first element.
		 *     throw when the container is empty.
		 */
		void pop_front() {
			if (_size == 0)
				throw container_is_empty();
			//弹出第一个元素
			--_size;
			delete head->next->val[head->next->_start];
			head->next->_start = (head->next->_start + 1) % head->next->_capacity;
			--head->next->_size;
			//判断是否为空
			if (head->next->_size == 0) {
				head->next = head->next->next;
				delete head->next->last;
				head->next->last = head;
			}
			//判断是否需要合并
			else if (head->next->_size + head->next->next->_size < (size_t)sqrt(_size))
				merge_space(head->next);
		}
	};

}

#endif
