#include "iostream"
#include "cstdio"
#include "cmath"
using namespace std;

int st_data_min[50009][20] = { 0 },
st_data_max[50009][20] = { 0 };

int mmin(int a, int b) {
	return a < b ? a : b;
}

int mmax(int a, int b) {
	return a > b ? a : b;
}

int main() {
	int N, Q;
	scanf("%d %d", &N, &Q);

	for (int i = 0; i < N; ++i) {
		int temp;
		scanf("%d", &temp);
		st_data_min[i][0] = st_data_max[i][0] = temp;
	}

	for (int j = 1; j <= int(log(N) / log(2)); ++j) {
		for (int i = 0; i + (1 << j) <= N; ++i) {
			st_data_min[i][j] = mmin(st_data_min[i][j - 1], st_data_min[i + (1 << (j - 1))][j - 1]);
			st_data_max[i][j] = mmax(st_data_max[i][j - 1], st_data_max[i + (1 << (j - 1))][j - 1]);
		}
	}

	for (; Q > 0; --Q) {
		int a, b;
		scanf("%d %d", &a, &b);
		--a;
		int k = int(log(b - a) / log(2));

		int shortest = mmin(st_data_min[a][k], st_data_min[b - (1 << k)][k]),
			tallest = mmax(st_data_max[a][k], st_data_max[b - (1 << k)][k]);

		printf("%d\n", tallest - shortest);
	}

	return 0;
}