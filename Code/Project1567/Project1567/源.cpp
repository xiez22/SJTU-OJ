#include "iostream"
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	char c;
	int num;
	cin >> c >> num;

	for (int i = 0; i <= num / 2; ++i) {
		for (int j = 0; j < num / 2 - i; ++j)
			cout << " ";
		for (int j = 0; j < 2 * i + 1; ++j)
			cout << c;
		cout << endl;
	}
	for (int i = num / 2 - 1; i >= 0; --i) {
		for (int j = 0; j < num / 2 - i; ++j)
			cout << " ";
		for (int j = 0; j < 2 * i + 1; ++j)
			cout << c;
		cout << endl;
	}

	return 0;
}