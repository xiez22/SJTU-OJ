#include "iostream"
#include "cstdio"
using namespace std;

int val_data[1009] = { 0 };

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; ++i) {
		scanf("%d", &val_data[i]);
	}

	for (; m > 0; --m) {
		int opt, l, r;
		scanf("%d %d %d", &opt, &l, &r);

		if (opt == 0) {
			double ans = 0.0;
			for (int i = l; i <= r; ++i)
				ans += double(val_data[i]);
			printf("%.2f\n", ans / (r - l + 1));
		}
		else if (opt == 1) {
			int cur_max = 0;
			for (int i = l; i <= r; ++i) {
				cur_max = val_data[i] > cur_max ? val_data[i] : cur_max;
			}
			printf("%d\n", cur_max);
		}
		else if (opt == 2) {
			for (; l < r; ++l, --r) {
				swap(val_data[l], val_data[r]);
			}
		}
		else if (opt == 3) {
			printf("%d", val_data[l]);
			for (int i = l + 1; i <= r; ++i)
				printf(" %d", val_data[i]);
			printf("\n");
		}
		else if (opt == 4) {
			for (int i = l; i <= r; ++i) {
				if (val_data[i] > 0)
					--val_data[i];
			}
		}
	}

	return 0;
}