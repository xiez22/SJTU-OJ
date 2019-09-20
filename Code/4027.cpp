#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

int n;
int a1[100009] = { 0 }, a2[100009] = { 0 };
int belong[100009] = { 0 };
int f[100009], b[100009], len;

int mid_find(int left, int right, int val) {
	int right_ans = right;
	--right;
	while (left <= right) {
		int mid = (left + right) >> 1;
		if (val > b[mid]) {
			left = mid + 1;
		}
		else if (val <= b[mid]) {
			right_ans = mid;
			right = mid - 1;
		}
	}
	return right_ans;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &a1[i]);
		belong[a1[i]] = i;
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a2[i]);
	}

	for (int i = 1; i <= n; ++i)
	{
		if (belong[a2[i]] > b[len])
		{
			b[++len] = belong[a2[i]];
			f[i] = len;
			continue;
		}
		int k = mid_find(1, len + 1, belong[a2[i]]);
		b[k] = belong[a2[i]];
		f[i] = k;
	}
	printf("%d\n", len);
	return 0;
}