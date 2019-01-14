#include "iostream"
using namespace std;

int main() {
	int data[13] = { 0 };
	for (int i = 1; i <= 12; i++)
		cin >> data[i];

	double bank = 0.0;
	int pocket = 0;

	//开始循环计算
	for (int i = 1; i <= 12; i++) {
		//计算存入金额
		if (pocket + 300 - data[i] >= 100) {
			bank += int((pocket + 300 - data[i]) / 100) * 100;
		}
		if (pocket + 300 - data[i] < 0) {
			cout << "-" << i;
			return 0;
		}
		pocket = (pocket + 300 - data[i]) % 100;
	}
	cout << int(bank*1.2) + pocket;

	return 0;
}