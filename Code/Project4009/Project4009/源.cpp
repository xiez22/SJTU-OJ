#include "iostream"
#include "cstring"
using namespace std;

int main() {
	char input[200], output[200];
	cin >> output >> input;

	int length = strlen(input);
	bool flag = false;

	//寻找最小a
	for (int a = 1; a <= length; a++) {
		//判断是否整除
		if (length%a)
			continue;
		int gap = length / a;
		char temp[200] = { 0 };
		//拼接
		for (int i = 0,n=0; i<gap; i++) {
			for (int j = 0; j*gap<length; j++,n++) {
				temp[n] = input[j*gap + i];
			}
		}
		//判断结果
		if (strcmp(temp, output) == 0) {
			flag = true;
			cout << a;
			break;
		}
	}

	if (!flag)
		cout << "No Solution";

	return 0;
}