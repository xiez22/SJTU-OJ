#include "iostream"
#include "cstdio"
using namespace std;

constexpr int inf = (int)(1e9 + 7);

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0, last = inf; i < n; ++i) {
		int wi, hi;
		scanf("%d %d", &wi, &hi);
		if (wi <= last && hi <= last) {
			last = wi > hi ? wi : hi;
		}
		else if (wi <= last) {
			last = wi;
		}
		else if (hi <= last) {
			last = hi;
		}
		else {
			cout << "NO";
			return 0;
		}
	}
	cout << "YES";

	return 0;
}