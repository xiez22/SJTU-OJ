#include "iostream"
using namespace std;

int ai[109] = { 0 };

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int num;
	cin >> num;
	int average = 0;

	for (int i = 0; i < num; ++i) {
		cin >> ai[i];
		average += ai[i];
	}
	average /= num;
	
	int ans = 0;
	for (int i = 0; i < num - 1; ++i) {
		if (ai[i] != average) {
			ai[i + 1] -= average - ai[i];
			ai[i] = average;
			++ans;
		}
	}

	cout << ans;


	return 0;
}