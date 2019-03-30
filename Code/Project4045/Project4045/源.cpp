#include "iostream"
#include "cstdio"
using namespace std;

int origin[10009] = { 0 };
int num_data[10009] = { 0 };

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; ++i) {
		scanf("%d", &origin[i]);
		//num_data[i] = origin[i];
	}

	for (int i = 0; i < m; ++i) {
		int l, r, x;
		scanf("%d %d %d", &l, &r, &x);
		if (x<l || x>r) {
			printf("Yes\n");
		}
		else {
			int cnt = 0;
			for (int j = l; j <= r; ++j) {
				if (j == x)
					continue;
				if (origin[j] < origin[x])
					++cnt;
			}
			if (cnt == x - l)
				printf("Yes\n");
			else
				printf("No\n");
		}
	}

	return 0;
}