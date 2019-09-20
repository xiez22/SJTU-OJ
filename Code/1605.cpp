#include "iostream"
#include "cstdio"
using namespace std;

constexpr auto maxNum = 1000000;

class myStack {
	int num = 0, acNum = 0;
	char data[maxNum] = { 0 };
	bool flag[maxNum] = { 0 };
	char ac[maxNum] = { 0 };
public:
	void push(char b) {
		if (b == '(' || b == '[' || b == '{')
			ac[acNum++] = b;
		else if (b == ')'&&acNum > 0 && ac[acNum - 1] == '(') {
			acNum--;
			flag[num] = true;
		}
		else if (b == ']'&&acNum > 0 && ac[acNum - 1] == '[') {
			acNum--;
			flag[num] = true;
		}
		else if (b == '}'&&acNum > 0 && ac[acNum - 1] == '{') {
			acNum--;
			flag[num] = true;
		}
		else
			ac[acNum++] = b;
		data[num++] = b;
	}
	bool empty() {
		return num == 0;
	}
	char pop() {
		if (num == 0)
			return  0;
		num--;
		char temp = data[num];
		data[num] = 0;

		//»ØÍË
		if (flag[num]) {
			if (temp == ')')
				ac[acNum++] = '(';
			else if (temp == ']')
				ac[acNum++] = '[';
			else if (temp == '}')
				ac[acNum++] = '{';
		}
		else
			acNum--;
		flag[num] = false;
		return temp;
	}
	char back() {
		if (num == 0)
			return 0;
		return data[num - 1];
	}
	bool match() {
		return acNum == 0;
	}
};

int main() {
	int num;
	myStack data;
	cin >> num;
	for (int i = 0; i < num; i++) {
		int temp;
		scanf("%d", &temp);
		if (temp == 1) {
			char c;
			scanf(" %c", &c);
			data.push(c);
		}
		else if (temp == 2) {
			data.pop();
		}
		else if (temp == 3) {
			if (!data.empty())
				printf("%c\n", data.back());
		}
		else if (temp == 4) {
			if (data.match())
				printf("YES\n");
			else
				printf("NO\n");
		}
	}

	return 0;
}