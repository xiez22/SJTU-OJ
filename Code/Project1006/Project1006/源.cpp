#include "iostream"

using namespace std;

constexpr auto maxnum = 1000000;

//求解
template <class T>
T bilibili(T *input,int num) {
	if (num == 1) return -100;
	else if (num == 2) return input[0] + input[1];
	//分成两块
	int center = num / 2;
	T a = bilibili(input, num / 2), b = bilibili(input + num / 2, num-num/2);
	//寻找左右的最大值
	T maxl = -100, maxr = -100, templ = 0, tempr = 0,count=0;
	for (int i = num / 2 - 1; i >= 0; i--) {
		templ += input[i];
		maxl = maxl < templ ? templ : maxl;
	}
	for (int i = num / 2; i < num; i++) {
		tempr += input[i];
		maxr = maxr < tempr ? tempr : maxr;
	}
	maxl += maxr;
	T max = a > b ? a : b;
	max = max > maxl ? max : maxl;
	return max;
}

int main() {
	int n;
	short input[maxnum];
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> input[i];
	}
	short ans = bilibili(input, n);
	if (ans > 0) {
		cout << ans << endl;
	}
	else {
		cout << "Game Over" << endl;
	}

	return 0;
}