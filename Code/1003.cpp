#include <cstdio>
#include <iostream>

using namespace std;

//培养皿边长
int L = 0;
//模拟培养皿
int plate[101][101] = { 0 };
//上一轮结束时的繁殖结果
int _plate[101][101] = { 0 };
//空白格子数
int blank = 0;
//繁殖轮数
int turns = 0;
//判断该位置是否为空格
int judge(int i, int j) {
	if (i >= 0 && i < L && j >= 0 && j < L) {
		if (_plate[i][j] == 0 && plate[i][j] == 0) {
			plate[i][j] = 1;
			return 1;
		}
	}
	return 0;
}
//增殖
void multiply() {
	while (blank > 0) {
		for (int i = 0; i < L; ++i) {
			for (int j = 0; j < L; ++j) {
				if (_plate[i][j] == 1) {
					blank -= judge(i + 1, j);
					blank -= judge(i, j + 1);
					blank -= judge(i - 1, j);
					blank -= judge(i, j - 1);
				}
			}
		}
		for (int i = 0; i < L; ++i) {
			for (int j = 0; j < L; ++j) {
				_plate[i][j] = plate[i][j];
			}
		}
		turns++;
	}
	return;
}

int main() {
	scanf("%d", &L);
	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < L; ++j) {
			scanf("%d", &plate[i][j]);
			_plate[i][j] = plate[i][j];
			if (plate[i][j] == 0)
				blank++;
		}
	}

	multiply();
	printf("%d", turns);
	return 0;
}