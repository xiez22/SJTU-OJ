#include "iostream"
#include "cstdio"
using namespace std;

int main() {
	int num;
	cin >> num;

	long long ans = 0;

	for (int i = 0; i < num; ++i) {
		int temp;
		scanf("%d", &temp);
		//转二进制
		for (; temp > 0; temp = temp >> 1)
			if (temp % 2 == 1)
				++ans;
	}

	cout << ans;

	return 0;
}