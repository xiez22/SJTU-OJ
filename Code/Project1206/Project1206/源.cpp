#include "iostream"
#include "cstring"
using namespace std;

class myList {
public:
	int data;
	myList* next = nullptr;
};

class myStack {
public:
	myList* head;

	myStack() {
		head = new myList;
	}

	void push(int b) {
		head->data = b;
		auto temp = head;
		head = new myList;
		head->next = temp;
	}

	int pop() {
		auto temp = head;
		int result = temp->next->data;
		head = head->next;
		delete temp;
		return result;
	}

	bool isEmpty() {
		return head->next == nullptr;
	}

	int getBack() {
		return head->next->data;
	}
};

int main() {
	myStack Stack;
	char op[10000][100] = { 0 };
	int num = 0;
	for (; cin >> op[num]; num++);


	//循环判断(begin 0,if then 1)
	for (int i = 0; i < num; i++) {
		if (strcmp(op[i], "begin") == 0) {
			//入栈0
			Stack.push(0);
		}
		else if (strcmp(op[i], "if") == 0) {
				Stack.push(2);
		}
		else if (strcmp(op[i], "then") == 0) {
			if (!Stack.isEmpty() && Stack.getBack() == 2) {
				Stack.pop();
				Stack.push(1);
			}
			else {
				cout << "Error!";
				return 0;
			}
		}
		else if (strcmp(op[i], "else") == 0) {
			if (!Stack.isEmpty() && Stack.getBack() == 1) {
				Stack.pop();
			}
			else {
				cout << "Error!";
				return 0;
			}
		}
		else if (strcmp(op[i], "end") == 0) {
			if (!Stack.isEmpty() && Stack.getBack() == 0) {
				Stack.pop();
				if (!Stack.isEmpty() && Stack.getBack() == 1 && strcmp(op[i + 1], "else") != 0)
					Stack.pop();
			}
			else {
				cout << "Error!";
				return 0;
			}
		}
		else if (!Stack.isEmpty() && Stack.getBack() == 1 &&op[i][strlen(op[i])-1]==';') {
			Stack.pop();
		}
	}

	//判断是否全部弹出
	if (Stack.isEmpty())
		cout << "Match!";
	else
		cout << "Error!";

	return 0;
}