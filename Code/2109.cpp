#include "iostream"
#include "cmath"
#include "cstdio"
using namespace std;

int ai[100009] = { 0 };

int mid_find(int left, int right, int val) {
	if (left == right) {
		if (ai[left] <= val)
			return left;
		else return left - 1;
	}
	int mid = (left + right) >> 1;
	if (ai[mid] == val)
		return mid;
	else if (ai[mid] < val) {
		return mid_find(mid + 1, right, val);
	}
	else {
		return mid_find(left, mid - 1, val);
	}
}

int main() {
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &ai[i]);

	int K;
	scanf("%d", &K);
	for (int i = 0; i < K; ++i) {
		int b, c;
		scanf("%d %d", &b, &c);

		printf("%d\n", mid_find(0, N - 1, b * b / (4 * c)) + 1);
	}

	return 0;
}