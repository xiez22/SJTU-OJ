#include "iostream"
#include "cstdio"
using namespace std;

constexpr int inf = 1000000009;

int a[1009][1009] = { 0 };
bool not_num[1009] = { 0 };
int n, m;
int f(int posx, int posy) {
	if (posx <= n && posy <= m)
		return a[posx][posy];
	else if (posx <= n)
		return a[posx][m];
	else if (posy <= m)
		return a[n][posy];
	else
		return a[n][m];
}

int main() {
	
	cin >> n >> m;

	for (int i = 1; i <= n; ++i) {
		a[i][0] = a[i - 1][1];
		for (int j = 1; j <= m; ++j) {
			int temp;
			scanf("%1d", &temp);
			a[i][j] = temp + a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
		}
	}

	//¼ÆËãÖÊÊý
	int max_k = n > m ? n : m;
	for (int i = 2; i <= max_k / 2 + 1; ++i) {
		if (not_num[i])
			continue;
		for (int j = i * 2; j <= max_k; j += i)
			not_num[j] = true;
	}

	int ans = inf;
	for (int k = 2; k <= max_k; ++k) {
		if (not_num[k])
			continue;
		int temp_ans = 0;
		for (int i = 1; i <= n; i += k) {
			for (int j = 1; j <= m; j += k) {
				int posx = i + k - 1, posy = j + k - 1;
				int temp = f(posx, posy) - f(posx - k, posy) - f(posx, posy - k) + f(posx - k, posy - k);
				temp_ans += temp < k * k - temp ? temp : k * k - temp;
			}
		}
		if (temp_ans < ans)
			ans = temp_ans;
	}

	printf("%d", ans);

	return 0;
}