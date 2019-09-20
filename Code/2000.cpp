#include "cstdio"
using namespace std;

int main() {
	int num,n;
	long long ans=0;
	scanf("%d", &num);
	for (int i = 0; i < num; i++) {
		scanf("%d", &n);
		ans += n;
	}

	printf("%lld", ans);
	return 0;
}