#include "iostream"
#include "cstring"
#include "cstdio"
#include "cmath"
using namespace std;

int mmin(int a, int b) {
	return a < b ? a : b;
}

int mmin(int a, int b, int c, int d) {
	return mmin(mmin(a, b), mmin(c, d));
}

int map_data[109][109] = { 0 };
int water[109][109] = { 0 };

int main() {
	int m, n;
	scanf("%d %d", &m, &n);

	int max_height = 0;

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			scanf("%d", &map_data[i][j]);
			max_height = map_data[i][j] > max_height ? map_data[i][j] : max_height;
		}
	}

	//装水
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			water[i][j] = max_height - map_data[i][j];
		}
	}

	//漏水
	for (int leak = 0;;) {
		leak = 0;
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
				auto cur_min = mmin(map_data[i - 1][j] + water[i - 1][j], map_data[i][j - 1] + water[i][j - 1],
					map_data[i + 1][j] + water[i + 1][j], map_data[i][j + 1] + water[i][j + 1]);
				if (water[i][j] > 0 && cur_min < map_data[i][j] + water[i][j]) {
					if (map_data[i][j] >= cur_min) {
						leak += water[i][j];
						water[i][j] = 0;
					}
					else {
						leak += map_data[i][j] + water[i][j] - cur_min;
						water[i][j] = cur_min - map_data[i][j];
					}
				}
			}
		}
		if (leak == 0)
			break;
	}

	//统计
	int ans = 0;
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			ans += water[i][j];
		}
	}

	cout << ans;

	return 0;
}