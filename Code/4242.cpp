#include <iostream>
#include <string>
using namespace std;

using ull = unsigned long long;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	string A, B;
	cin >> A >> B;

	if (A.length() < B.length()) {
		cout << 0;
		return 0;
	}
	int al = A.length(), bl = B.length();

	ull hasha = 0, hashb = 0, pnum = 1ull;
	for (int i = 0; i < bl; ++i) {
		hasha = hasha * 131ull + ull(A[i]);
		hashb = hashb * 131ull + ull(B[i]);
		pnum *= 131ull;
	}

	int cnt = 0;
	for (int i = 0;; ++i) {
		if (hasha == hashb)
			++cnt;
		if (i + bl >= al)
			break;

		hasha = hasha * 131ull + ull(A[i + bl]) - pnum * ull(A[i]);
	}

	cout << cnt;

	return 0;
}