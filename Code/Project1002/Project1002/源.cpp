#include "iostream"

using namespace std;

constexpr int maxnum = 1000;

int main() {
	int l = 0, w = 0;
	int a = 0, b = 0;
	cin >> l >> w;

	//声明数组
	short hs[maxnum][maxnum];

	//输入数组
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < w; j++) {
			cin >> hs[i][j];
		}
	}

	//范围
	cin >> a >> b;

	//记录数据
	int max = 0;

	//第一次计算
	int temp1 = 0;
	int inittemp = 0;
	for (int i1 = 0; i1 < a; i1++) {
		for (int j1 = 0; j1 < b; j1++) {
			inittemp += hs[i1][j1];
		}
	}
	temp1 = inittemp;
	max = max < inittemp ? inittemp : max;

	//移动
	for (int i = 0; i < l - a + 1; i++) {
		//行移动
		if (i > 0) {
			int tempa = 0, tempb = 0;
			for (int j1 = 0; j1 < b; j1++) {
				tempa += hs[i-1][j1];
			}
			for (int j1 = 0; j1 < b; j1++) {
				tempb+= hs[i+a-1][j1];
			}
			temp1 = temp1 - tempa + tempb;
			max = max < temp1 ? temp1 : max;
		}

		int temp2 = temp1;
		for (int j = 1; j < w - b + 1; j++) {
			int tempa = 0, tempb = 0;
			//列移动
			for (int i1 = 0;i1 <a; i1++) {
				tempa += hs[i + i1][j-1];
			}
			for (int i1 = 0; i1 < a; i1++) {
				tempb += hs[i + i1][j+b-1];
			}
			temp2 = temp2 - tempa + tempb;
			max = max < temp2 ? temp2 : max;
		}
	}

	//输出
	cout << max << endl;

	return 0;
}