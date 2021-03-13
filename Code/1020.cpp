#include "iostream"
#include "cmath"
using namespace std;

constexpr long long maxSize = 9999;

int main() {
	int num, maxNum;
	cin >> num;
	maxNum = sqrt(num) + 1;

	cout << num << "=";

	//质因数个数
	int ansNum = 0;

	//集合
	int ans[maxSize];
	int ansn[maxSize];

	//求解质因数
	for (int i = 2; i <= maxNum; i++) {
		if (num%i != 0)
			continue;

		//求解个数
		int j;
		for (j = 0; num%i == 0; j++) {
			num /= i;
		}

		//记录数据
		ans[ansNum] = i;
		ansn[ansNum] = j;
		ansNum++;
	}

	if (num != 1) {
		ans[ansNum] = num;
		ansn[ansNum] = 1;
		ansNum++;
	}

	//输出
	for (int i = 0; i < ansNum; i++) {
		cout << ans[i] << "(" << ansn[i] << ")";
	}

	return 0;
}