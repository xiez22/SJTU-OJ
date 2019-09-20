#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

bool a[1009][1009] = { 0 };
int b[1000009][2] = { 0 };
int b_num = 0;
int a_num[1009] = { 0 };

int main() {
	int T;
	cin >> T;

	for (; T > 0; ) {
		int m, n, p, q;
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		memset(a_num, 0, sizeof(a_num));
		b_num = 0;
		scanf("%d %d %d %d", &m, &n, &p, &q);
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j) {
				scanf("%d", &a[i][j]);
				if (a[i][j])
					a_num[i]++;
			}
		for (int i = 0; i < p; ++i)
			for (int j = 0; j < q; ++j) {
				int temp;
				scanf("%d", &temp);
				if (temp) {
					b[b_num][0] = i;
					b[b_num++][1] = j;
				}
			}
		//开始比较
		for (int i = 0; i <= m; ++i) {
			for (int j = 0; j <= n; ++j) {
				//判断位置是否匹配
				if (a[i][j]) {
					//循环
					for (int k = 0; k < b_num; ++k) {
						int bx = b[k][0] - b[0][0] + i, by = b[k][1] - b[0][1] + j;
						if (bx < m && by < n && bx >= 0 && by >= 0 && a[bx][by]) {
							a[bx][by] = false;
							--a_num[bx];
						}
						else {
							printf("No\n");
							goto start;
						}
					}
				}
			}
			if (a_num[i] > 0) {
				printf("No\n");
				goto start;
			}
		}
		//检查
		for(int i=0;i<m;++i)
			if (a_num[i] > 0) {
				printf("No\n");
				goto start;
			}
		printf("Yes\n");
	start:
		--T;
	}

	return 0;
}