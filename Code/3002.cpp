#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

bool val_num[1009] = { 0 };

int main() {
	int n;
	scanf("%d", &n);

	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		int temp;
		scanf("%d", &temp);
		if (!val_num[temp]) {
			++cnt;
			val_num[temp] = true;
		}
	}

	printf("%d\n", cnt);
	for (int i = 0; i < 1005; ++i) {
		if (val_num[i])
			printf("%d ", i);
	}

	return 0;
}