#include "iostream"
using namespace std;

int main() {
	bool a[2000001];
	int num;
	cin >> num;

	for (int i = 0; i <= num; i++)
		a[i] = true;

	for (int i = 2; i <= num; i++) {
		if (a[i]) {
			for (int j = 2; i*j <= num; j++)
				a[i*j] = false;
		}
	}

	cout << "2";

	for (int i = 3; i <= num; i++) {
		if (a[i])
			cout << " " << i;
	}


	return 0;
}