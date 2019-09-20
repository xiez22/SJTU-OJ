#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

int n, m;
bool visited[20] = { 0 };
int groups[109][20] = { 0 };
int val_data[109] = { 0 };
int val_num[109] = { 0 };

double ans = 0.0;

void cal_max(int pos) {
	if (pos == n) {
		double cur_ans = 0.0;
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			if (visited[i]) {
				++cnt;
			}
		}
		for (int i = 0; i < m; ++i) {
			bool flag = true;
			for (int j = 0; j < val_num[i]; ++j) {
				if (!visited[groups[i][j]]) {
					flag = false;
					break;
				}
			}
			if (flag) {
				cur_ans += double(val_data[i]);
			}
		}
		if (cnt > 0)
			cur_ans /= double(cnt);
		ans = cur_ans > ans ? cur_ans : ans;
		return;
	}
	visited[pos] = true;
	cal_max(pos + 1);
	visited[pos] = false;
	cal_max(pos + 1);
}

int main() {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < m; ++i) {
		scanf("%d %d", &val_num[i], &val_data[i]);
		for (int j = 0; j < val_num[i]; ++j) {
			scanf("%d", &groups[i][j]);
		}
	}

	cal_max(0);
	printf("%.2f",ans);

	return 0;
}