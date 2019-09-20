#include "iostream"
using  namespace std;

int main() {
	int a = 0, b = 0;
	int result[10000];
	int count = 0;
	cin >> a >> b;
	if (a > b||a<=0||b<=0) {
		cout << "error";
	}
	else {
		for (; a <= b; a++) {
			int temp = a;
			int sum = 0;
			while (temp > 0) {
				sum += (temp % 10)*(temp % 10)*(temp % 10);
				temp = (temp - (temp % 10))/10;
			}
			if (sum == a) {
				result[count++] = a;
			}
		}

		//Êä³ö
		if (count == 0)
			cout << "no";
		else {
			cout << result[0];
			for (int i = 1; i < count; i++)
				cout << endl << result[i];
		}
	}

	return 0;
}