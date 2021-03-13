#include "iostream"
#include "cstdio"
using namespace std;

constexpr int inf = 1000000009;
constexpr double jd = 1e-4;

int height[509][509] = { 0 };

int main() {
	int M, N;
	cin >> M >> N;

	int minh = inf, maxh = 0;

	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &height[i][j]);
			if (height[i][j] < minh)
				minh = height[i][j];
			if (height[i][j] > maxh)
				maxh = height[i][j];
		}
	}
	double V;
	cin >> V;

	double left = minh, right = 1e10, mid;
	int cnt = 0;
	while (right - left > jd) {
		mid = (left + right) / 2;
		cnt = 0;
		double v = 0;
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				if (height[i][j] + jd < mid) {
					++cnt;
					v += (mid - height[i][j]);
				}
			}
		}
		if (v < V) {
			left = (left + right) / 2;
		}
		else if (v == V)
			break;
		else {
			right = (left + right) / 2;
		}
	}

	printf("%.2f\n%.2f", mid, double(cnt) / double(M * N) * 100);

	return 0;
}