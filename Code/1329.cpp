#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

int n, m;
bool visited[25] = { 0 };
int choose[65][25] = { 0 };
int val_num[65] = { 0 };
bool fucked = false;

void fuck(int pos) {
	if (pos == n + 1) {
		bool flag = true;
		for (int i = 0; i < m; ++i) {
			int cnt = 0;
			for (int j = 0; j < val_num[i]; ++j) {
				if (choose[i][j] < 0 && !visited[-choose[i][j]]) {
					++cnt;
				}
				else if (choose[i][j] > 0 && visited[choose[i][j]]) {
					++cnt;
				}
			}
			if (cnt == 0) {
				flag = false;
				break;
			}
		}
		if (flag) {
			fucked = true;
		}
		return;
	}
	visited[pos] = true;
	fuck(pos + 1);
	visited[pos] = false;
	fuck(pos + 1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;
	cin.get();

	for (; t > 0; --t) {
		fucked = false;
		memset(visited, 0, sizeof(visited));
		memset(choose, 0, sizeof(choose));
		memset(val_num, 0, sizeof(val_num));
		cin >> n >> m;
		/*
		cin.get();
		char buff[1000] = { 0 };
		cin.getline(buff, 1000);
		int length = strlen(buff);
		int cnt = 0;
		int cur_num = 0;
		for (int i = 0; i < length; ++i) {
			if (buff[i] >= '0' && buff[i] <= '9') {
				cur_num = cur_num * 10 + buff[i] - '0';
				if ()
			}
		}*/
		cin.get();
		for (int i = 0; i < m; ++i) {
			for (int cnt = 0;; ++cnt) {
				cin >> choose[i][cnt];
				if (cin.get() == '\n') {
					val_num[i] = cnt + 1;
					break;
				}
			}
		}

		fuck(1);

		if (fucked) {
			cout << "Bingo!\n";
		}
		else {
			cout << "Sigh...\n";
		}
	}

	return 0;
}