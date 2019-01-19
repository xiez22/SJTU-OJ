#include "iostream"
using namespace std;

bool bac[100][100] = { 0 }, base[100][100] = { 0 };
int baci[10000] = { 0 }, bacj[10000] = { 0 };

int main() {
	int num,bacNum=0,drugNum=0;
	cin >> num;

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			int temp;
			scanf("%d", &temp);
			if (temp == 1) {
				bac[i][j] = true;
				baci[bacNum] = i;
				bacj[bacNum] = j;
				bacNum++;
			}
			else if (temp == 2) {
				base[i][j] = true;
				drugNum++;
			}
		}
	}

	//所有的数量
	int allBac = num * num - drugNum;
	int generals = 0,curBegin=0;
	while (bacNum < allBac) {
		//繁衍
		int tempBacNum = bacNum;
		for (int i = curBegin; i < tempBacNum; i++) {
			if (baci[i] > 0&&!bac[baci[i]-1][bacj[i]]&&!base[baci[i]-1][bacj[i]]) {
				bac[baci[i] - 1][bacj[i]] = true;
				baci[bacNum] = baci[i] - 1;
				bacj[bacNum] = bacj[i];
				bacNum++;
			}
			if (baci[i] <num-1 && !bac[baci[i] +1][bacj[i]] && !base[baci[i] + 1][bacj[i]]) {
				bac[baci[i] + 1][bacj[i]] = true;
				baci[bacNum] = baci[i] + 1;
				bacj[bacNum] = bacj[i];
				bacNum++;
			}
			if (bacj[i] >0 && !bac[baci[i]][bacj[i]-1] && !base[baci[i]][bacj[i]-1]) {
				bac[baci[i]][bacj[i]-1] = true;
				baci[bacNum] = baci[i];
				bacj[bacNum] = bacj[i]-1;
				bacNum++;
			}
			if (bacj[i] <num-1 && !bac[baci[i]][bacj[i] + 1] && !base[baci[i]][bacj[i] + 1]) {
				bac[baci[i]][bacj[i] + 1] = true;
				baci[bacNum] = baci[i];
				bacj[bacNum] = bacj[i] + 1;
				bacNum++;
			}
		}
		curBegin = tempBacNum;
		generals++;
	}

	cout << generals;

	return 0;
}