#include "iostream"
using namespace std;

int main() {
	int salary;
	cin >> salary;
	salary -= 3500;

	double ans = 0.0;
	if (salary > 80000) {
		ans += (salary - 80000) * 0.45;
		salary = 80000;
	}
	if (salary > 55000) {
		ans += (salary - 55000) * 0.35;
		salary = 55000;
	}
	if (salary > 35000) {
		ans += (salary - 35000) * 0.30;
		salary = 35000;
	}
	if (salary > 9000) {
		ans += (salary - 9000) * 0.25;
		salary = 9000;
	}
	if (salary > 4500) {
		ans += (salary - 4500) * 0.20;
		salary = 4500;
	}
	if (salary > 1500) {
		ans += (salary - 1500) * 0.10;
		salary = 1500;
	}
	if (salary > 0) {
		ans += (salary - 0) * 0.03;
	}

	cout << (int)ans;

	return 0;
}