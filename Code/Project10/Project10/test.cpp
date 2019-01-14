
/*
*  Author:      illuz <iilluzen[at]gmail.com>
*  File:        coj1216.cpp
*  Create Date: 2014-07-27 14:18:44
*  Descripton:  trie
*/

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N = 100000 << 5;

struct Trie {
	int a[2];
	int num;
} f[N];

int cnt, ans;

// insert x into the root which id is u, the deep is num
void insert(int x, int u, int num) {
	bool k;
	for (int i = num; i >= 0; i--) {
		k = (1 << i)&x;
		if (f[u].a[k] == -1)
			f[u].a[k] = ++cnt;
		u = f[u].a[k];
	}
	f[u].num = x;
}

// query xor
void query(int x, int u, int num) {
	bool k;
	for (int i = num; i >= 0; i--) {
		k = (1 << i)&x;
		if (f[u].a[!k] != -1)
			u = f[u].a[!k];
		else
			u = f[u].a[k];
	}
	ans = max(ans, f[u].num^x);
}

int main() {
	int n, t;
	while (~scanf("%d", &n)) {
		memset(f, -1, sizeof(Trie) * N);
		cnt = 0;
		ans = 0;
		while (n--) {
			scanf("%d", &t);
			insert(t, 0, 31);
			query(t, 0, 31);
		}
		printf("%d\n", ans);
	}
	return 0;
}
