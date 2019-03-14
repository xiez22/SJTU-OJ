#include "iostream"
#include "cstdio"
using namespace std;

int xi[10009] = { 0 };

int main() {
	int n;
	scanf("%d\n[", &n);

	for (int i = 0; i < n - 1; ++i)
		scanf("%d,", &xi[i]);
	scanf("%d]", &xi[n - 1]);

	int lpos = 0, rpos = 1, stock_num = 0, ans = 0;
	for (; rpos < n; ++rpos) {
		if (xi[rpos] >= xi[lpos]) {
			ans += xi[lpos] * (rpos - lpos - 1) - stock_num;
			lpos = rpos;
			stock_num = 0;
		}
		else if (rpos == n - 1) {
			//µ¹Ðò
			stock_num = 0;
			for (int last_rpos = n - 1, last_lpos = n - 2; last_lpos >= lpos; --last_lpos) {
				if (xi[last_lpos] >= xi[last_rpos]) {
					ans += xi[last_rpos] * (last_rpos - last_lpos - 1) - stock_num;
					last_rpos = last_lpos;
					stock_num = 0;
				}
				else {
					stock_num += xi[last_lpos];
				}
			}
		}
		else {
			stock_num += xi[rpos];
		}
	}

	cout << ans;

	return 0;
}