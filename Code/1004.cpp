#include "iostream"
#include "cstdio"
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int M, T, U, F, D;
	cin >> M >> T >> U >> F >> D;

	int ans = 0;
	for (int i = 0, cur_time = 0; i < T; ++i) {
		char c;
		cin >> c;
		if (c == 'u'||c=='d') {
			if (cur_time + U + D <= M)
				++ans;
			cur_time += U + D;
		}
		else {
			if (cur_time + 2 * F <= M)
				++ans;
			cur_time += 2 * F;
		}
	}
	cout << ans;
	return 0;
}