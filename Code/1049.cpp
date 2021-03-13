#include "iostream"
using namespace std;

class my_stack {
public:
	int stack_data[100000] = { 0 };
	int _size = 0;

	void push(int val) {
		stack_data[_size++] = val;
	}
	void pop() {
		--_size;
	}
	int top() {
		return stack_data[_size - 1];
	}
	bool empty() {
		return _size == 0;
	}
	int size() {
		return _size;
	}
};

int main() {
	int num;
	cin >> num;
	for (; num > 0; num--) {
		int n, m;
		cin >> n >> m;

		int data[2000];
		my_stack trainz;
		for (int i = 0; i < n; i++) {
			cin >> data[i];
			trainz.push(n - i - 1);
		}

		my_stack station;
		bool flag = false;

		//—≠ª∑≈–∂œ «∑Ò»Î’ª
		for (int i = 0; i < n; i++) {
			if (!station.empty() && station.top() == data[i])
				station.pop();
			else if (!trainz.empty() && trainz.top() == data[i])
				trainz.pop();
			else if (!trainz.empty() && station.size() < m) {
				station.push(trainz.top());
				trainz.pop();
				i--;
			}
			else
				flag = true;
		}

		if (flag)
			cout << "NO" << endl;
		else
			cout << "YES" << endl;

	}

	return 0;
}