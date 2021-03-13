#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	for (; n > 0; --n) {
		int a, b;
		cin >> a >> b;
		
		vector<vector<int>> mat(a,vector<int>(a,0));
		
		if (b == 0) {
			for (int i = 0; i < a; ++i) {
				for (int j = 0; j < a; ++j) {
					cin >> mat[i][a - j - 1];
				}
			}
		}
		else if (b == 1) {
			for (int i = 0; i < a; ++i) {
				for (int j = 0; j < a; ++j) {
					cin >> mat[a - i - 1][j];
				}
			}
		}
		else {
			for (int i = 0; i < a; ++i) {
				for (int j = 0; j < a; ++j) {
					cin >> mat[j][i];
				}
			}
		}

		for (auto& p : mat) {
			for (auto q : p) {
				cout << q << " ";
			}
			cout << "\n";
		}
	}

	return 0;
}