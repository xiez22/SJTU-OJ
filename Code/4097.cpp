#include "iostream"
#include "vector"
#include "cmath"
using namespace std;

template <class T>
class block_node {
public:
	vector<T> val;
	block_node<T>* next = nullptr;
	block_node<T>* last = nullptr;
	size_t len = 0;
};

template <class T>
class block_list {
public:
	block_node<T>* head = nullptr;
	block_node<T>* rear = nullptr;
	size_t _size = 0;

	block_list() {
		head = new block_node<T>;
		rear = new block_node<T>;
		head->next = rear;
		rear->last = head;
		_size = 0;
	}

	//从数组导入
	void from_array(T* array_data, size_t array_size) {
		_size = array_size;
		auto block_size = (size_t)sqrt(array_size);
		auto p = head;
		for (size_t i = 0; i < array_size; i += block_size) {
			p->next = new block_node<T>;
			p->next->last = p;
			p = p->next;
			for (size_t j = 0; j < block_size && i + j < array_size; ++j) {
				p->val.push_back(array_data[i + j]);
				++p->len;
			}
		}
		p->next = rear;
		rear->last = p;
	}

	//查找
	T& find(unsigned int pos) {
		auto p = head;
		unsigned int i = 0;
		for (; i + p->len <= pos; i += p->len, p = p->next);
		return p->val[pos - i];
	}

	//插入
	void insert(unsigned int pos, const T& val) {
		auto p = head;
		unsigned int i = 0;
		for (; i + p->len <= pos && p->next->next; i += p->len, p = p->next);
		++p->len;
		++_size;
		p->val.insert(p->val.begin() + (pos - i), val);
		//判断是否超限
		auto block_size = (size_t)sqrt(_size);
		if (p->len > 2 * block_size) {
			auto temp = new block_node<T>;
			temp->val.assign(p->val.begin() + p->len / 2, p->val.end());
			p->val.erase(p->val.begin() + p->len / 2, p->val.end());
			temp->len = p->len - p->len / 2;
			p->len /= 2;
			p->next->last = temp;
			temp->next = p->next;
			p->next = temp;
			temp->last = p;
		}
	}

	//删除
	void erase(unsigned int pos) {
		auto p = head;
		unsigned int i = 0;
		for (; i + p->len <= pos; i += p->len, p = p->next);
		--p->len;
		--_size;
		p->val.erase(p->val.begin() + (pos - i));
		//判断是否完全删除
		if (p->len <= 0) {
			p->last->next = p->next;
			p->next->last = p->last;
			delete p;
			return;
		}
		//判断是否太小
		auto block_size = (size_t)sqrt(_size);
		if (p->len + p->next->len < block_size && p->next != rear) {
			//合并
			p->val.insert(p->val.end(), p->next->val.begin(), p->next->val.end());
			p->len += p->next->len;
			auto temp = p->next;
			p->next = p->next->next;
			p->next->last = p;
			delete temp;
		}
	}

	//打印
	void println() {
		for (auto p = head; p->next->next; p = p->next)
			for (auto q : p->next->val)
				cout << q << " ";
	}
};

block_list<int> list_data;
int init_array[100009] = { 0 };

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M;
	cin >> N >> M;

	for (int i = 0; i < N; ++i)
		cin >> init_array[i];
	list_data.from_array(init_array, N);

	for (int i = 0; i < M; ++i) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int X, Y;
			cin >> X >> Y;
			list_data.insert(X, Y);
		}
		else {
			int X;
			cin >> X;
			list_data.erase(X - 1);
		}
	}
	list_data.println();
	return 0;
}