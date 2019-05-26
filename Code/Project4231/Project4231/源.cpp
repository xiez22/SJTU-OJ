#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

char color_data[400] = { 0 };
int red_maxl[400] = { 0 }, red_maxr[400] = { 0 },
blue_maxl[400] = { 0 }, blue_maxr[400] = { 0 };

int mmax(int a, int b) {
	return a > b ? a : b;
}

int main() {
	int n;
	scanf("%d", &n);
	scanf("%s", color_data);

	//统计初始位置
	if (color_data[n - 1] == 'w') {
		for (int i = 0; i < n && (color_data[i] == 'w' || color_data[i] == 'r'); ++i)
			++red_maxr[n - 1];
		for (int i = 0; i < n && (color_data[i] == 'w' || color_data[i] == 'b'); ++i)
			++blue_maxr[n - 1];
	}
	else if (color_data[n - 1] == 'r') {
		for (int i = 0; i < n && (color_data[i] == 'w' || color_data[i] == 'r'); ++i)
			++red_maxr[n - 1];
		blue_maxr[n - 1] = -1;
	}
	else {
		for (int i = 0; i < n && (color_data[i] == 'w' || color_data[i] == 'b'); ++i)
			++blue_maxr[n - 1];
		red_maxr[n - 1] = -1;
	}

	if (color_data[0] == 'w') {
		for (int i = n - 1; i >= 0 && (color_data[i] == 'w' || color_data[i] == 'r'); --i)
			++red_maxl[0];
		for (int i = n - 1; i >= 0 && (color_data[i] == 'w' || color_data[i] == 'b'); --i)
			++blue_maxl[0];
	}
	else if (color_data[0] == 'r') {
		for (int i = n - 1; i >= 0 && (color_data[i] == 'w' || color_data[i] == 'r'); --i)
			++red_maxl[0];
		blue_maxl[0] = -1;
	}
	else {
		for (int i = n - 1; i >= 0 && (color_data[i] == 'w' || color_data[i] == 'b'); --i)
			++blue_maxl[0];
		red_maxl[0] = -1;
	}
	
	//递归统计
	for (int i = 1; i < n; ++i) {
		if (color_data[i] == 'w') {
			red_maxl[i] = red_maxl[i - 1] + 1;
			blue_maxl[i] = blue_maxl[i - 1] + 1;
			
		}
		else if (color_data[i] == 'r') {
			red_maxl[i] = red_maxl[i - 1] + 1;
			blue_maxl[i] = -1;
		}
		else {
			blue_maxl[i] = blue_maxl[i - 1] + 1;
			red_maxl[i] = -1;
		}
	}
	for (int i = n - 2; i >= 0; --i) {
		if (color_data[i] == 'w') {
			red_maxr[i] = red_maxr[i + 1] + 1;
			blue_maxr[i] = blue_maxr[i + 1] + 1;
		}
		else if (color_data[i] == 'r') {
			red_maxr[i] = red_maxr[i + 1] + 1;
			blue_maxr[i] = -1;
		}
		else {
			blue_maxr[i] = blue_maxr[i + 1] + 1;
			red_maxr[i] = -1;
		}
	}

	int ans = mmax(red_maxl[n - 1], blue_maxl[n - 1]) + mmax(red_maxr[0], blue_maxr[0]) + 2;

	for (int i = 1; i < n; ++i) {
		auto cur_ans = mmax(red_maxl[i - 1], blue_maxl[i - 1]) + mmax(red_maxr[i], blue_maxr[i]) + 2;
		ans = cur_ans > ans ? cur_ans : ans;
	}

	printf("%d", ans > n ? n : ans);

	return 0;
}