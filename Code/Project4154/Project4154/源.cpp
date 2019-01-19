#include "iostream"
#include "cmath"
using  namespace std;

int main() {
	int a = 0, b = 0;
	int result[10000];
	int count = 0;
	cin >> a >> b;
	if (a > b || a <= 0 || b <= 0 || a > 99999 || b > 99999) {
		cout << "error";
	}
	else {
		for (; a <= b; a++) {
			//计算位数
			int weishu = 0;
			int temp0 = a;
			for (; temp0 != 0;) {
				temp0 /= 10;
				weishu++;
			}

			int temp = a;
			int sum = 0;
			while (temp > 0) {
				sum += int(pow(double(temp % 10), double(weishu)));
				temp = (temp - (temp % 10)) / 10;
			}
			if (sum == a) {
				result[count++] = a;
			}
		}

		//输出
		if (count == 0)
			cout << "no";
		else {
			cout << result[0];
			for (int i = 1; i < count; i++)
				cout << endl << result[i];
		}
	}

	return 0;
}