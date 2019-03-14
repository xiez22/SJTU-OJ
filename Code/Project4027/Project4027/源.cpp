#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
int a1[100010], a2[100010];
int belong[100010];
int f[100010], b[100010], len;
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a1[i]);
		belong[a1[i]] = i;
	}
	for (int i = 1; i <= n; i++)
		scanf("%d", &a2[i]);
	for (int i = 1; i <= n; i++)
	{
		if (belong[a2[i]] > b[len])
		{
			b[++len] = belong[a2[i]];
			f[i] = len;
			continue;
		}
		int k = lower_bound(b + 1, b + len + 1, belong[a2[i]]) - b;
		b[k] = belong[a2[i]];
		f[i] = k;
	}
	printf("%d\n", len);
	return 0;
}