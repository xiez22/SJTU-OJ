#include "iostream"
using namespace std;
int main() {
	double price = 0, cost = 0;
	int pri;

	cin >> price;

	pri = price;

	switch (pri / 1000) {
	case 0:cost = price; break;
	case 1:cost = price*0.9; break;
	case 2:cost = price * 0.9; break;
	case 3:cost = price * 0.7; break;
	case 4:cost = price * 0.6; break;
	default:
	cost = price * 0.5; break;
	}
	cout << cost << endl;

	return 0;
}