#include "iostream"
#include "cmath"
#include "cstdio"
using namespace std;

constexpr double jd = 1e-7;

double pos[100009] = { 0 };

bool check(double r, int n, int limit) {
	int cnt = 1;
	for (int i = 0, cur_pos = 0; i < n; ++i) {
		if (r < pos[i] - pos[cur_pos]) {
			++cnt;
			cur_pos = i;
		}
		if (cnt > limit)
			return false;
	}
	return true;
}

int main() {
	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; ++i)
		scanf("%lf", &pos[i]);

	//¿ªÊ¼Ñ­»·
	double left = pos[0], right = pos[n - 1];
	double r;
	while (true) {
		auto mid = (right + left) / 2;
		r = mid - pos[0];
		if (check(r * 2, n, k)) {
			right = mid;
			if (right - left <= jd) {
				printf("%.6f", r);
				return 0;
			}
		}
		else {
			left = mid;
		}
	}
	return 0;
}