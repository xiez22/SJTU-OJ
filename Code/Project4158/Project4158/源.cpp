#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

int mods_cnt[5009] = { 0 };

int main() {
	int T;
	scanf("%d", &T);

	for (; T > 0; --T) {
		int n, m;
		scanf("%d %d", &n, &m);
		//≥ı ºªØ	
		memset(mods_cnt, 0, sizeof(int) * m);
		mods_cnt[0] = 1;
		long long ans = 0;
		for (int i = 0, cur_ans = 0; i < n; ++i) {
			int temp;
			scanf("%d", &temp);
			cur_ans = (cur_ans + temp) % m;
			ans += (long long)mods_cnt[cur_ans];
			++mods_cnt[cur_ans];
		}
		printf("%lld\n", ans);
	}

	return 0;
}