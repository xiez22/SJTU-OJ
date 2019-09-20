#include "iostream"
#include "cstring"
#include "cstdio"
#include "cmath"
using namespace std;

int main() {
	double r, d;
	double ans = 0.0;
	while (cin >> r >> d) {
		double cur_ans = r * r * acos(d / r) - d * sqrt(r * r - d * d);
		ans = cur_ans > ans ? cur_ans : ans;
	}

	printf("%.2f", ans);

	return 0;
}