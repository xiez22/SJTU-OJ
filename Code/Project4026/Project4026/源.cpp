#include <iostream>

using namespace std;

int main() {
	char a, b, c, d;
	int input;
	cin >> input;
	a = input / 1000;
	b = (input % 1000) / 100;
	c = (input % 100) / 10;
	d = (input % 10);
	a = a + 77;
	b = b + 77;
	c = c + 77;
	d = d + 77;
	cout<< a << b << c << d << endl;
	return 0;
}