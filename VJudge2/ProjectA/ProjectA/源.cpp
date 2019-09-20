#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

int val[3009] = { 0 };
int cnt[10009] = { 0 };

int main() {
	int n, m;
	while (cin >> n >> m) {
		memset(val, 0, sizeof(val));
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; ++i) {
			scanf("%d", &val[i]);
		}
		for (int i = 0; i < n - 1; ++i) {
			for (int j = i + 1; j < n; ++j) {
				++cnt[val[i] + val[j]];
			}
		}
		for (int i = 10000, j = 0, k = 0; k < m; ++k) {
			if (j >= cnt[i]) {
				//я╟уробр╩╦Ж
				for (i = i - 1; cnt[i] == 0; --i);
				j = 0;
			}
			if (k)
				printf(" ");
			printf("%d", i);
			++j;
		}
		printf("\n");
	}

	return 0;
}