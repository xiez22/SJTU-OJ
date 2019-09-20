#include "iostream"
using namespace std;

long long mmin(long long a, long long b) {
	return a < b ? a : b;
}

long long cal_step(long long n, long long x, long long y) {
	//记录当前边数
	long long gap = mmin(mmin(x - 1, n - x), mmin(y - 1, n - y));
	long long num = n - 2 * gap;
	long long step = n * n - num * num;

	long long dx[] = { 0,1,0,-1 };
	long long dy[] = { 1,0,-1,0 };
	//记录步数
	for (long long status = 0, i = (n - num) / 2 + 1, j = i - 1; i != x || j != y; step++) {
		i += dx[status];
		j += dy[status];
		//判断是否越界
		if (i + dx[status] > n - gap || i + dx[status]<gap + 1 || j + dy[status]>n - gap || j + dy[status] < gap + 1) {
			status = status < 3 ? status + 1 : 0;
		}
	}
	return step - 1;
}

int main() {
	long long n, x, y;
	cin >> n >> x >> y;
	
	cout << cal_step(n, y, n - x + 1) << " " << cal_step(n, n - y + 1, x);

	return 0;
}