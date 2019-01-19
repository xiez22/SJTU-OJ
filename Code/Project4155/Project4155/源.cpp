#include "iostream"
using namespace std;

int main() {
	int y = 0, m = 0, d = 0;
	cin >> y >> m >> d;

	int days[] = { 0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	//判断闰年
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
		days[2] += 1;
	}

	//排除错误
	if (y < 0 || y>9999 || m <= 0 || m > 12 || d <= 0 || d > days[m]) {
		cout << "error";
	}
	else {
		//计算前月天数
		int result = 0;
		for (int i = 1; i < m; i++) {
			result += days[i];
		}
		result += d;
		cout << result;
	}

	return 0;
}