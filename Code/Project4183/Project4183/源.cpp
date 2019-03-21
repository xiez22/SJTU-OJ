#include "iostream"
#include "cstdio"
using namespace std;

void reverse_nums(int* from, int* end) {
	for (auto p = from, q = end - 1; p < q; ++p, --q) {
		auto temp = *p;
		*p = *q;
		*q = temp;
	}
}

void permutation_step(int* from, int* end) {
	//寻找逆序数
	auto p = end - 2;
	for (; p >= from && *p >= * (p + 1); --p);
	//判断是否完成
	if (p < from) {
		reverse_nums(from, end);
		return;
	}
	auto q = end - 1;
	for (; *p > * q; --q);
	//交换
	auto temp = *p;
	*p = *q;
	*q = temp;
	reverse_nums(p + 1, end);
}

int main() {
	int m;
	scanf("%d", &m);

	for (; m > 0; --m) {
		int a[1009] = { 0 };
		int n, k;
		scanf("%d %d", &n, &k);
		for (int i = 0; i < n; ++i)
			scanf("%d", &a[i]);
		for (int i = 0; i < k; ++i)
			permutation_step(a, a + n);
		printf("%d", a[0]);
		for (int i = 1; i < n; ++i)
			printf(" %d", a[i]);
		printf("\n");
	}

	return 0;
}