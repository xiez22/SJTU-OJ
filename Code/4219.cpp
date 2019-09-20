#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;

const int mod = int(1e9 + 7);
vector<int> value;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int T, n;
	cin >> T >> n;

	for (int i = 0; i < n; ++i) {
		int temp;
		cin >> temp;
		value.push_back(temp);
	}

	sort(value.begin(), value.end(), [](int a, int b) {return a > b; });

	for (int i = 1; i < n; ++i)
		value[i] = (value[i - 1] + value[i]) % int(1e9 + 7);

	for (; T > 0; --T) {
		int temp;
		cin >> temp;
		cout << value[temp - 1] << "\n";
	}

	return 0;
}