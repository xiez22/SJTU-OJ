#include "iostream"
#include "cstring"
using namespace std;

constexpr auto maxNum = 1000001;

class myList {
public:
	short data=0;
	myList *next = nullptr;
};

class bigNum {
public:
	myList *head;
	bigNum(const char* ch) {
		head = new myList;
		auto p = head;
		for (int i = strlen(ch) - 1; i >= 0; i--) {
			//添加元素
			p->next = new myList;
			p = p->next;
			p->data = ch[i] - '0';
		}
	}
	void add(bigNum num) {
		//开始运算
		int temp = 0;
		auto p1 = head, p2 = num.head;
		while (p1->next != nullptr || p2->next != nullptr || temp != 0) {
			//判断是否需要添加
			if (p1->next == nullptr)
				p1->next = new myList;
			short addNum = p2->next == nullptr ? 0 : p2->next->data;
			if (p1->next->data + addNum + temp < 10) {
				p1->next->data = p1->next->data + addNum + temp;
				temp = 0;
			}
			else {
				p1->next->data = p1->next->data + addNum + temp - 10;
				temp = 1;
			}
			p1 = p1->next;
			p2 = p2->next == nullptr ? p2 : p2->next;
		}
	}
	void print() {
		char printString[maxNum] = { 0 }, reverseString[maxNum] = { 0 };
		int n = 0;
		for (auto p = head; p->next != nullptr; p = p->next) {
			printString[n] = p->next->data + '0';
			n++;
		}
		//倒序
		int stringSize = strlen(printString);
		for (int i = 0; i < stringSize; i++)
			reverseString[i] = printString[stringSize - i - 1];
		cout << reverseString;
	}
};

int main() {
	char num1[maxNum];
	cin >> num1;
	bigNum n1(num1);
	cin >> num1;
	bigNum n2(num1);
	n2.add(n1);
	n2.print();

	return 0;
}