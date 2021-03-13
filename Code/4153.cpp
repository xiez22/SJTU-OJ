#include "iostream"
#include "algorithm"
using namespace std;

//记录被选中的点
int choose[100009] = { 0 };

int main() {
	int n, m, k;
	ios::sync_with_stdio(false);
	cin >> n >> m >> k;

	int *dis = new int[n];
	for (int i = 0; i < n; i++)
		cin >> dis[i];
	sort(dis, dis + n);
	if (k == 1) {
		int cl = 0, cr = dis[n - 1],ans=0;
		//二分法
		while (cl <= cr) {
			int mid = (cl + cr) >> 1,cnt=0;
			for (int i = 1, startNum = 0; i < n; i++)
				if (dis[i] - dis[startNum] < mid) cnt++;
				else startNum = i;
			if (cnt > n - m) cr = mid - 1;
			else {
				cl = mid + 1;
				ans = mid;
			}
		}
		cout << ans;
	}
	else if(k==2){
		int cl = dis[0], cr = 2*dis[n - 1]-3*dis[0], ans = 0;
		//二分法
		while (cl <= cr) {
			int mid = (cl + cr) >> 1, cnt = 0,topNum=0;
			choose[topNum++] = 0;
			bool flag = false;
			for (int i = 1, startNum = 0; i < n; i++)
				if (dis[i] - dis[startNum] < mid) { 
					cnt++; 
					//判断是否在末尾
					if (i == n - 1) {
						choose[topNum - 1] = i;
					}
				}
				else {
					choose[topNum++] = i;
					startNum = i;
				}
			//判断是否可以插入
			for (int i = 1; i < topNum; i++) {
				if (choose[i] > choose[i - 1] + 1) {
					if (dis[choose[i] - 1] - dis[choose[i - 1]] >= mid ||
						dis[choose[i]] - dis[choose[i - 1] + 1] >= mid) {
						flag = true;
						break;
					}
				}
			}
			if (cnt < n - m + 1)
				flag = true;
			if (cnt > n - m + 1||!flag) 
				cr = mid - 1;
			else {
				cl = mid + 1;
				ans = mid;
			}
		}
		cout << ans;
	}

	return 0;
}