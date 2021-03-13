#include <iostream>
#include <vector>
using namespace std;

int f(int n, int m) {
	if (n == 1)
		return 0;
	return (f(n - 1, m) + m) % n;
}

int main() {
	int n, m;
	cin >> n >> m;

	cout << f(n, m) + 1;

	return 0;
}