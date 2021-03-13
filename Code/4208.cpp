#include "iostream"
#include "cstdio"
#include "cmath"
using namespace std;

int main() {
	int n;
	cin >> n;

	for (; n > 0; --n) {
		int a, b, x1, y1, x2, y2;
		scanf("%d %d %d %d %d %d", &b, &a, &x1, &y1, &x2, &y2);
		a *= 2, b *= 2;
		int m1 = floor(double(x1 - y1) / a), n1 = floor(double(x1 + y1) / b),
			m2 = floor(double(x2 - y2) / a), n2 = floor(double(x2 + y2) / b);
		if (abs(m1 - m2) > abs(n1 - n2)) {
			printf("%d\n", abs(m1 - m2));
		}
		else {
			printf("%d\n", abs(n1 - n2));
		}
	}

	return 0;
}