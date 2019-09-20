#include "iostream"
#include "cstdio"
using namespace std;

int numData[100009] = { 0 };
long long numAns[100009] = { 0 };

int main() {
	int N, M;
	scanf("%d %d", &N, &M);

	for (int i = 1; i <= N; i++) {
		scanf("%d", &numData[i]);
		numAns[i] = numAns[i - 1] + numData[i];
	}

	for (; M > 0; M--) {
		char op;
		scanf("\n%c", &op);

		if (op == 'Q') {
			int a, b;
			scanf("%d %d", &a, &b);
			printf("%lld\n", numAns[b] - numAns[a - 1]);
		}
		else {
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			if (a - 1 > N - b) {
				int ans = c;
				for (; a < b; a++,ans+=c)
					numAns[a] += ans;
				for (; a <= N; a++)
					numAns[a] += ans;
			}
			else {
				int ans = c;
				for (b=b-1;b>=a;b--, ans += c)
					numAns[b] -= ans;
				for (; b>=0; b--)
					numAns[b] -= ans;
			}
		}
	}

	return 0;
}