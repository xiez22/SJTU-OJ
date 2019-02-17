#include "iostream"
using namespace std;

int myStack[1000000] = { 0 }, stackn = 0;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int num;
	cin >> num;
	for (int i = 0; i < num; i++) {
		int temp;
		cin >> temp;

		if (stackn == 0 || temp > myStack[stackn - 1])
			myStack[stackn++] = temp;
		else {
			//¶ş·Ö²éÕÒ
			int ll = 0, rr = stackn - 1;
			while (ll < rr) {
				int mid = (ll + rr) >> 1;
				if (myStack[mid] < temp)
					ll = mid + 1;
				else
					rr = mid;
			}
			//Ìæ»»
			myStack[ll] = temp;
		}
	}

	cout << stackn;

	return 0;
}