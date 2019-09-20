#include "iostream"
#include "cstdio"
using namespace std;

bool city[100001] = { 0 };
int road[100000][3] = { 0 };

int main() {
	int n, m, k;
	cin >> n >> m >> k;

	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &road[i][0], &road[i][1], &road[i][2]);
	}

	for (int i = 0; i < k; i++) {
		int temp;
		scanf("%d", &temp);
		city[temp] = true;
	}

	//Ñ°ÕÒ×î¶ÌÂ·
	long long minMoney=1e10;
	for (int i = 0; i < m; i++) {
		if ((city[road[i][0]] && !city[road[i][1]]) || (!city[road[i][0]] && city[road[i][1]])) {
			if (road[i][2] < minMoney)
				minMoney = road[i][2];
		}
	}

	if (k == 0 || minMoney >= 1e10)
		cout << -1;
	else
		cout << minMoney;

	return 0;
}