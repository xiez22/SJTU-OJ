#include "iostream"
#include "cstdio"
using namespace std;

constexpr int max_num = 120000009;

long long a[max_num] = { 0 };
int N, M, Q;
long long f(int posx, int posy) {
	return a[posx * (M + 1) + posy];
}

int main() {
	
	scanf("%d %d %d", &N, &M, &Q);

	for (int i = 1; i <= N; ++i) {
		a[i * (M + 1)] = a[(i - 1) * (M + 1) + 1];
		for (int j = 1; j <= M; ++j) {
			long long temp;
			scanf("%lld", &temp);
			a[i * (M + 1) + j] = temp + a[(i - 1) * (M + 1) + j]
				+ a[i * (M + 1) + j - 1] - a[(i - 1) * (M + 1) + j - 1];
		}
	}

	for (; Q > 0; --Q) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		printf("%lld\n", f(x2, y2) - f(x2, y1 - 1) - f(x1 - 1, y2) + f(x1 - 1, y1 - 1));
	}

	return 0;
}