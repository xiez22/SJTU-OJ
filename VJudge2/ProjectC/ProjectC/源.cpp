#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	while (cin >> n) {
		cin.get();
		for (int k = 0; k < n; ++k) {
			int cnt[5] = { 0 };
			char ch[109] = { 0 };
			cin.getline(ch, 109);

			int length = strlen(ch);
			for (int i = 0; i < length; ++i) {
				if (ch[i] == 'a')
					++cnt[0];
				else if (ch[i] == 'e')
					++cnt[1];
				else if (ch[i] == 'i')
					++cnt[2];
				else if (ch[i] == 'o')
					++cnt[3];
				else if (ch[i] == 'u')
					++cnt[4];
			}
			if (k)
				cout << "\n";
			cout << "a:" << cnt[0] << "\n";
			cout << "e:" << cnt[1] << "\n";
			cout << "i:" << cnt[2] << "\n";
			cout << "o:" << cnt[3] << "\n";
			cout << "u:" << cnt[4] << "\n";
		}
	}

	return 0;
}