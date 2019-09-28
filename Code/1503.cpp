#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
	double x1, x2, y1, y2;
	cin >> x1 >> y1 >> x2 >> y2;

	auto c = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	c = int64_t(c * 100000.0 + 0.5) / 100000.0;
	cout << c;

	return 0;
}