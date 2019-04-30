#include "iostream"
#include "cmath"
#include "cstdio"

using namespace std;

int st_data_min[200009][20] = { 0 },
st_data_max[200009][20] = { 0 };

int mmin(int a, int b) {
	return a < b ? a : b;
}

int mmax(int a, int b) {
	return a > b ? a : b;
}

int main() {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; ++i) {
		scanf("%d", &st_data_max[i][0]);
	}

	for (int i = 0; i < N; ++i) {
		scanf("%d", &st_data_min[i][0]);
	}

	for (int j = 1; j <= int(log(N) / log(2)); ++j) {
		for (int i = 0; i + (1 << j) <= N; ++i) {
			st_data_min[i][j] = mmin(st_data_min[i][j - 1], st_data_min[i + (1 << (j - 1))][j - 1]);
			st_data_max[i][j] = mmax(st_data_max[i][j - 1], st_data_max[i + (1 << (j - 1))][j - 1]);
		}
	}

	long long ans = 0;
	for (int i = 0; i < N; ++i) {
		//二分查找最左边的最大值
		int left_ans = -1, right_ans = -1;
		int left = i + 1, right = N;
		while (left <= right) {
			int mid = (left + right) >> 1;
			int k = int(log(mid - i) / log(2));
			int cur_min = mmin(st_data_min[i][k], st_data_min[mid - (1 << k)][k]),
				cur_max = mmax(st_data_max[i][k], st_data_max[mid - (1 << k)][k]);
			if (cur_min < cur_max) {
				right = mid - 1;
			}
			else if (cur_min > cur_max) {
				left = mid + 1;
			}
			else {
				left_ans = mid;
				right = mid - 1;
			}
		}
		if (left_ans < 0)
			continue;
		left = i + 1, right = N;
		while (left <= right) {
			int mid = (left + right) >> 1;
			int k = int(log(mid - i) / log(2));
			int cur_min = mmin(st_data_min[i][k], st_data_min[mid - (1 << k)][k]),
				cur_max = mmax(st_data_max[i][k], st_data_max[mid - (1 << k)][k]);
			if (cur_min < cur_max) {
				right = mid - 1;
			}
			else if (cur_min > cur_max) {
				left = mid + 1;
			}
			else {
				right_ans = mid;
				left = mid + 1;
			}
		}
		ans += right_ans - left_ans + 1;
	}

	printf("%lld", ans);

	return 0;
}