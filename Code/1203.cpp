#include "iostream"
#include "cstring"
using namespace std;

template <class T>
class myLink {
public:
	T data;
	myLink *next = nullptr;
};

template <class T>
class mySheet {
public:
	myLink<T> *head;
	myLink<T> *rear;
	mySheet() {
		head = new myLink<T>;
		rear = head;
	}
	mySheet(T data) {
		head = new myLink<T>;
		head->next = new myLink<T>;
		head->next->data = data;
		rear = head->next;
	}
	~mySheet() {
		for (auto p = head; p;) {
			auto temp = p->next;
			if (p == rear) {
				delete p;
				break;
			}
			delete p;
			p = temp;
		}
	}
	
	//复制构造函数
	mySheet(const mySheet<T> &b) {
		head = new myLink<T>;
		for (auto p1 = head, p2 = b.head; p2->next != nullptr;) {
			p1->next = new myLink<T>;
			p1->next->data = p2->next->data;
			p1 = p1->next;
			p2 = p2->next;
			rear = p1;
		}
	}

	//重载等号
	mySheet<T>& operator=(const mySheet<T> &b) {
		head = new myLink<T>;
		for (auto p1 = head, p2 = b.head; p2->next != nullptr;) {
			p1->next = new myLink<T>;
			p1->next->data = p2->next->data;
			p1 = p1->next;
			p2 = p2->next;
			rear = p1;
		}
		return *this;
	}

	void append(T b) {
		rear->next = new myLink<T>;
		rear = rear->next;
		rear->data = b;
	}

	//重载加号
	mySheet<T> operator+(const mySheet<T> &b) const {
		mySheet<T> temp = *this;
		mySheet<T> tempAdd = b;
		temp.rear->next = tempAdd.head->next;
		return temp;
	}

	//打印
	void print() {
		for (auto p = head;; ) {
			if (p->next == nullptr) break;
			if (p != head) cout << " ";
			cout << p->next->data;
			p = p->next;
		}
	}
};

int main() {
	char type[10];
	int num1, num2;
	cin >> type;
	cin >> num1 >> num2;
	if (strcmp(type, "int") == 0) {
		mySheet<int> a, b;
		for (int i = 0; i < num1; i++) {
			int temp;
			cin >> temp;
			a.append(temp);
		}
		for (int i = 0; i < num2; i++) {
			int temp;
			cin >> temp;
			b.append(temp);
		}
		mySheet<int> c;
		c = a + b;
		c.print();
	}
	if (strcmp(type, "char") == 0) {
		mySheet<char> a, b;
		for (int i = 0; i < num1; i++) {
			char temp;
			cin>>temp;
			a.append(temp);
		}
		for (int i = 0; i < num2; i++) {
			char temp;
			cin >> temp;
			b.append(temp);
		}
		mySheet<char> c;
		c = a + b;
		c.print();
	}
	if (strcmp(type, "double") == 0) {
		mySheet<double> a, b;
		for (int i = 0; i < num1; i++) {
			double temp;
			cin >> temp;
			a.append(temp);
		}
		for (int i = 0; i < num2; i++) {
			double temp;
			cin >> temp;
			b.append(temp);
		}
		mySheet<double> c;
		c = a + b;
		c.print();
	}
	return 0;
}