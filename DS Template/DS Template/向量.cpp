//向量类 By @ligongzzz
//更新时间：2019年2月14日


#include "iostream"
#include "vector"
using namespace std;


template <class T>
class mVector {
	T** vector_data = nullptr;
	unsigned int size = 0;
	unsigned int capacity = 0;

public:
	//构造函数
	mVector() = default;
	mVector(unsigned int _size) :size(_size) {
		capacity = _size * 2;
		vector_data = new T * [capacity] {nullptr};
	}
	mVector(unsigned int _size, const T& val) :size(_size) {
		capacity = _size * 2;
		vector_data = new T * [capacity] {nullptr};
		for (unsigned int i = 0; i < _size; ++i)
			vector_data[i] = new T(val);
	}
	mVector(const mVector<T>& _vector):size(_vector.size),capacity(_vector.capacity) {
		vector_data = new T * [capacity] {nullptr};
		for (int i = 0; i < size; ++i)
			vector_data[i] = new T(*_vector.vector_data[i]);
	}
	//析构函数
	~mVector() {
		for (unsigned int i = 0; i < size; ++i)
			delete vector_data[i];
		delete[] vector_data;
	}

	//迭代器
	class iterator {
		T** pos = nullptr;
		friend iterator mVector<T>::begin();
		friend iterator mVector<T>::end();
		friend void mVector<T>::erase(const iterator& val);
	public:
		iterator() = default;
		iterator(const iterator& other) {
			pos = other.pos;
		}
		iterator& operator++() {
			++pos;
			return *this;
		}
		iterator operator++(int) {
			iterator temp(*this);
			++pos;
			return temp;
		}
		iterator& operator--() {
			--pos;
			return *this;
		}
		iterator operator--(int) {
			iterator temp(*this);
			--pos;
			return temp;
		}
		bool operator==(const iterator& other) const{
			return pos == other.pos;
		}
		bool operator!=(const iterator& other) const{
			return pos != other.pos;
		}
		iterator& operator=(const iterator& other) {
			pos = other.pos;
			return *this;
		}
		T& operator*() const{
			return **pos;
		}
	};

	//反向迭代器
	template <class U>
	class reverse_iterator {
		U val;
		friend reverse_iterator<U> mVector<T>::rbegin();
		friend reverse_iterator<U> mVector<T>::rend();
	public:
		U& base() {
			return val;
		}
		reverse_iterator() = default;
		reverse_iterator(const reverse_iterator<U>& other) {
			val = other.val;
		}
		reverse_iterator(const U& other) {
			val = other;
		}
		reverse_iterator<U>& operator++() {
			--val;
			return *this;
		}
		reverse_iterator<U> operator++(int) {
			reverse_iterator<U> temp(*this);
			--val;
			return temp;
		}
		reverse_iterator<U>& operator--() {
			++val;
			return *this;
		}
		reverse_iterator<U> operator--(int) {
			reverse_iterator<U> temp(*this);
			++val;
			return temp;
		}
		bool operator==(const reverse_iterator<U>& other) const {
			return val == other.val;
		}
		bool operator!=(const reverse_iterator<U>& other) const {
			return val != other.val;
		}
		reverse_iterator<U>& operator=(const reverse_iterator<U>& other) {
			val = other.val;
			return *this;
		}
		T& operator*() const {
			return *val;
		}
	};

	reverse_iterator<iterator> rbegin() {
		auto temp = end();
		--temp;
		reverse_iterator<iterator> result;
		result.val = temp;
		return result;
	}

	reverse_iterator<iterator> rend() {
		auto temp = begin();
		--temp;
		reverse_iterator<iterator> result;
		result.val = temp;
		return result;
	}

	//增加元素
	void push_back(const T& val) {
		if (size < capacity)
			vector_data[size++] = new T(val);
		else {
			T** temp_data = new T * [(capacity + 1) * 2]{ nullptr };
			for (unsigned int i = 0; i < size; ++i) 
				temp_data[i] = vector_data[i];
			temp_data[size++] = new T(val);
			capacity = (capacity + 1) * 2;
			delete[] vector_data;
			vector_data = temp_data;
		}
	}

	//删除末尾
	void pop_back() {
		delete vector_data[size];
		vector_data[size--] = nullptr;
	}

	//清空
	void clear() {
		for (unsigned int i = 0; i < size; ++i) {
			delete vector_data[i];
			vector_data[i] = nullptr;
		}
		size = 0;
	}

	//删除
	void erase(const iterator& val) {
		delete* val.pos;
		for (auto p = val.pos; p != vector_data + size - 1; ++p)
			* p = *(p + 1);
		--size;
		vector_data[size] = nullptr;
	}

	//重载运算符
	T& operator[](const unsigned int& pos) {
		return *vector_data[pos];
	}

	iterator begin() {
		iterator temp;
		temp.pos = vector_data;
		return temp;
	}

	iterator end() {
		iterator temp;
		temp.pos = vector_data + size;
		return temp;
	}

};