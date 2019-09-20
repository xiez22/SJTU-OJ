#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

int stack_data[100009] = { 0 };
int tree_data[100009] = { 0 };
int child_num[100009] = { 0 };
bool visited[100009] = { 0 };

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
		delete vector_data[size - 1];
		vector_data[--size] = nullptr;
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

template <class T>
class myPriorityQueue {
public:
	mVector<T> queueData;
	unsigned int sizeOfQueue = 0;
	bool(*cmp)(T a, T b) = [](T a, T b) {return a < b; };

	//向下过滤
	void percolateDown(unsigned int pos) {
		while (pos * 2 <= sizeOfQueue) {
			if (pos * 2 + 1 > sizeOfQueue) {
				//交换
				if (cmp(queueData[pos * 2], queueData[pos])) {
					auto temp = queueData[pos * 2];
					queueData[pos * 2] = queueData[pos];
					queueData[pos] = temp;
				}
				break;
			}
			else {
				bool minNum = cmp(queueData[pos * 2 + 1], queueData[pos * 2]);
				if (cmp(queueData[pos * 2 + minNum], queueData[pos])) {
					auto temp = queueData[pos * 2 + minNum];
					queueData[pos * 2 + minNum] = queueData[pos];
					queueData[pos] = temp;
					pos = pos * 2 + minNum;
				}
				else break;
			}
		}
	}


	//构建
	myPriorityQueue() {
		queueData.clear();
		queueData.push_back((T)0);
		sizeOfQueue = 0;
	}

	//compare函数返回父结点a与孩子结点b的关系正确与否
	myPriorityQueue(bool(*compare)(T a, T b)) :cmp(compare) {
		queueData.clear();
		queueData.push_back(*new T);
		sizeOfQueue = 0;
	}

	//根据数组建立堆
	void buildHeap(T* eleData, unsigned int eleNum) {
		queueData.clear();
		sizeOfQueue = eleNum;
		queueData.push_back(*new T);
		for (unsigned int i = 1; i <= eleNum; i++)
			queueData.push_back(eleData[i - 1]);
		//向下过滤
		for (unsigned int pos = eleNum / 2; pos > 0; pos--)
			percolateDown(pos);
	}

	void refresh() {
		//向下过滤
		for (unsigned int pos = size() / 2; pos > 0; pos--)
			percolateDown(pos);
	}

	//判断是否空
	bool empty() {
		return sizeOfQueue == 0;
	}

	//返回队列大小
	auto size() {
		return sizeOfQueue;
	}

	//入队
	void push(const T & input) {
		sizeOfQueue++;
		queueData.push_back(input);

		//向上过滤
		for (auto i = sizeOfQueue; i > 1; i = i / 2) {
			//判断是否比父结点更小
			if (cmp(queueData[i], queueData[i / 2])) {
				//交换
				auto temp = queueData[i];
				queueData[i] = queueData[i / 2];
				queueData[i / 2] = temp;
			}
			else break;
		}
	}

	//队列最前
	T top() {
		return queueData[1];
	}

	//出队
	T pop() {
		auto temp = queueData[1];
		queueData[1] = queueData[sizeOfQueue--];
		queueData.pop_back();
		percolateDown(1);
		return temp;
	}
};

myPriorityQueue<int> leaves;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int stackn = 0;
	char ch_temp;
	cin >> ch_temp;
	int init_temp;
	cin >> init_temp;
	stack_data[stackn++] = init_temp;
	int n = 1;
	while (stackn) {
		char temp_ch;
		cin >> temp_ch;
		if (temp_ch == '(') {
			int temp;
			cin >> temp;
			++n;
			stack_data[stackn++] = temp;
		}
		else {
			//TODO
			if (stackn > 1)
				tree_data[stack_data[stackn - 1]] = stack_data[stackn - 2];
			stack_data[--stackn] = 0;
		}
	}

	//寻找根节点
	int root;
	for (int i = 1; i <= n; ++i) {
		if (tree_data[i] == 0) {
			root = i;
			break;
		}
	}
	//寻找叶子
	for (int i = 1; i <= n; ++i) {
		if (i != root)
			++child_num[tree_data[i]];
	}

	for (int i = 1; i <= n; ++i) {
		if (child_num[i] == 0 || (i == root && child_num[i] == 1))
			leaves.push(i);
	}

	for (int cnt = 0; cnt + 1 < n; ++cnt) {
		auto temp = leaves.pop();
		visited[temp] = true;
		--child_num[tree_data[temp]];
		if (temp != root) {
			cout << tree_data[temp] << " ";
			if (!visited[tree_data[temp]] && ((tree_data[temp] == root && 
				child_num[tree_data[temp]] == 1) || child_num[tree_data[temp]] == 0))
				leaves.push(tree_data[temp]);
		}
		else {
			for (int i = 1; i <= n; ++i) {
				if (!visited[i] && tree_data[i] == root) {
					cout << i << " ";
					root = i;
					//判断是否需要入队
					if (child_num[root] == 1)
						leaves.push(root);
					break;
				}
			}
		}
		
	}

	return 0;
}