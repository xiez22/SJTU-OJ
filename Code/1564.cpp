#include "iostream"
using namespace std;

constexpr int inf = 1e9;

bool flag[6][6] = { 0 };
int dx[] = { 0,1,0,-1 }, 
    dy[] = { 1,0,-1,0 };
int disData[6][6] = { 0 };
int dfs(int fromx, int fromy, int tox, int toy, int status) {
	if (fromx == tox && fromy == toy)
		return 0;
	//深度优先搜索
	flag[fromx][fromy] = true;
	int minDis=inf;
	for (int i = 0; i < 4; i++) {
		if (fromx + dx[i] < 6 && fromx + dx[i] >= 0 && fromy + dy[i] < 6 && fromy + dy[i] >= 0
			&&!flag[fromx+dx[i]][fromy+dy[i]]) {
			int dis = disData[fromx + dx[i]][fromy + dy[i]] * status,
				ans = dfs(fromx + dx[i], fromy + dy[i], tox, toy, dis % 4 + 1)+dis;
			if (minDis > ans) minDis = ans;
		}
	}
	//回溯
	flag[fromx][fromy] = false;
	return minDis;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;

	for (; n > 0; n--) {
		
		int fromx, fromy, tox, toy;
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++)
				cin >> disData[i][j];
		cin >> fromx >> fromy >> tox >> toy;

		//深度优先搜索
		cout << dfs(fromx, fromy, tox, toy, 1) << endl;
	}

	return 0;
}