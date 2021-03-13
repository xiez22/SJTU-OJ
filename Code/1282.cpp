#include "iostream"
#include "cmath"
#include "algorithm"
using namespace std;

int n, ans = 1e9, a[2009], c[2009], 
f[2009][2009], g[2009][2009];

void sol()
{
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			f[i][j] = g[i - 1][j] + abs(a[i] - c[j]);
			if (j == 1) 
				g[i][j] = f[i][j];
			else 
				g[i][j] = min(f[i][j], g[i][j - 1]);
		}
	}
	for (int i = 1; i <= n; ++i)
		ans = min(ans, f[n][i]);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	//ÊäÈë²¢ÅÅÐò
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		c[i] = a[i];
	}
	sort(c + 1, c + n + 1);

	sol();
	//·´Ðò
	for (int i = 1; i <= n / 2; ++i)
		swap(c[i], c[n - i + 1]);

	sol();
	cout << ans;

	return 0;
}