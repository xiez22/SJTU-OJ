#include <iostream>
using namespace std;
using ull = unsigned long long;

int main() {
	ull n, a = 0, b = 0, c = 0;
	cin >> n;

	for (; n % 5ull == 0; n /= 5ull, ++c);
	for (; n % 3ull == 0; n /= 3ull, ++b);
	for (; n % 2ull == 0; n /= 2ull, ++a);

	if (n != 1)
		cout << -1;
	else
		cout << a + 2ull * b + 3ull * c;

	return 0;
}
