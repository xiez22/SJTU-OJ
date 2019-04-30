#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

int cnt[1000009] = { 0 };

int main() {
	int n, m;
	while (cin >> n >> m) {
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; ++i) {
			int temp;
			scanf("%d", &temp);
			++cnt[temp + 500000];
		}

		for (int i = 1000005, j = 0, k = 0; k < m; ++k) {
			if (j >= cnt[i]) {
				//я╟уробр╩╦Ж
				for (i = i - 1; cnt[i] == 0; --i);
				j = 0;
			}
			if (k)
				printf(" ");
			printf("%d", i - 500000);
			++j;
		}
		printf("\n");
	}

	return 0;
}