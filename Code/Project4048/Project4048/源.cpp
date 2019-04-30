#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
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
	mVector(const mVector<T> & _vector) :size(_vector.size), capacity(_vector.capacity) {
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
		bool operator==(const iterator& other) const {
			return pos == other.pos;
		}
		bool operator!=(const iterator& other) const {
			return pos != other.pos;
		}
		iterator& operator=(const iterator& other) {
			pos = other.pos;
			return *this;
		}
		T& operator*() const {
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
	void push_back(const T & val) {
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
		delete vector_data[--size];
		vector_data[size] = nullptr;
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
	void erase(const iterator & val) {
		delete* val.pos;
		for (auto p = val.pos; p != vector_data + size - 1; ++p)
			* p = *(p + 1);
		--size;
		vector_data[size] = nullptr;
	}

	size_t get_size() {
		return size;
	}

	//重载运算符
	T & operator[](const unsigned int& pos) {
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

class leg {
public:
	int length = 0,
		times = 0;
};

leg table[100009];
int houzhui[100009] = { 0 };
int time_sum[209] = { 0 };

mVector<int> length_sum[100009];

int main() {
	int n;
	int max_length = 0;
	scanf("%d", &n);

	for (int i = 0; i < n; ++i)
		scanf("%d", &table[i].length);
	for (int i = 0; i < n; ++i)
		scanf("%d", &table[i].times);

	for (int i = 0; i < n; ++i) {
		length_sum[table[i].length].push_back(table[i].times);
		max_length = table[i].length > max_length ? table[i].length : max_length;
	}

	//计算后缀和
	for (int i = 100005; i >= 0; --i) {
		houzhui[i] = houzhui[i + 1];
		for (int j = 0; j < length_sum[i].get_size(); ++j)
			houzhui[i] += length_sum[i][j];
	}

	int ans = int(1e9 + 7);
	//遍历计算
	for (int i = 1, cur_remain = 0; i <= max_length; ++i) {
		if (length_sum[i].get_size() == 0)
			continue;
		int temp = houzhui[i + 1];
		//计算桶内的剩余
		for (int remain = cur_remain, pos = 0, step = 0; 
			remain >= length_sum[i].get_size(); --remain) {
			if (time_sum[pos] <= step) {
				for (++pos; time_sum[pos] == 0; ++pos);
				step = 0;
			}
			temp += pos;
			++step;
		}
		ans = temp < ans ? temp : ans;
		//将当前长度入桶
		for (int j=0;j<length_sum[i].get_size();++j)
			++time_sum[length_sum[i][j]];
		cur_remain += length_sum[i].get_size();
	}

	cout << ans;

	return 0;
}