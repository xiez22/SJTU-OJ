#include "iostream"
#include "cstdio"
#include "cmath"
#include "cstring"
using namespace std;

int st_data_max[1009][12] = { 0 };

int mmax(int a, int b) {
	return a > b ? a : b;
}

int main(){
	int T;
	scanf("%d", &T);
	for (; T > 0; --T) {
		memset(st_data_max, 0, sizeof(st_data_max));

		int N, Q;
		scanf("%d", &N);

		for (int i = 0; i < N; ++i) {
			scanf("%d", &st_data_max[i][0]);
		}
		scanf("%d", &Q);

		for (int j = 1; j <= int(log(N) / log(2)); ++j) {
			for (int i = 0; i + (1 << j) <= N; ++i) {
				st_data_max[i][j] = mmax(st_data_max[i][j - 1], st_data_max[i + (1 << (j - 1))][j - 1]);
			}
		}

		for (; Q > 0; --Q) {
			int a, b;
			scanf("%d %d", &a, &b);
			--a;
			int k = int(log(b - a) / log(2));
			printf("%d\n", mmax(st_data_max[a][k], st_data_max[b - (1 << k)][k]));
		}
	}
	return 0;
}