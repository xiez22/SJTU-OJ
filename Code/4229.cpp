#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

int val_num[50009] = { 0 };

int main() {
	int n;
	scanf("%d", &n);

	int cur_max = 0, max_n = 0;
	while (true) {
		char op[10];
		scanf("%s", op);
		if (strcmp(op, "add") == 0) {
			int a, b;
			scanf("%d %d", &a, &b);
			++val_num[b];
			if (val_num[b] == max_n) {
				if (b < cur_max) {
					cur_max = b;
				}
			}
			if (val_num[b] > max_n) {
				cur_max = b;
				max_n = val_num[b];
			}
		}
		else if (strcmp(op, "query") == 0) {
			printf("%d %d\n", cur_max, max_n);
		}
		else {
			break;
		}
	}

	return 0;
}