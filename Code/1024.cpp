#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	vector<int> vector_data;

	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		int temp;
		cin >> temp;
		vector_data.push_back(temp);
	}

	sort(vector_data.begin(), vector_data.end());

	for (auto p : vector_data)
		cout << p << " ";

	return 0;
}