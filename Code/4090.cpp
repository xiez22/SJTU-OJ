#include "cstdio"
#include "iostream"

using namespace std;

int main() {
	int year, month, day;
	int n;
	int months[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

	scanf("%4d%2d%2d %d", &year, &month, &day, &n);
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		months[2] = 29;
	else
		months[2] = 28;

	for (; n > 0; n--) {
		if (day + 1 > months[month]) {
			day = 1;
			if (month + 1 > 12) {
				month = 1;
				if (year + 1 > 9999) {
					cout << "out of limitation!";
					return 0;
				}
				else
					year++;
				if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
					months[2] = 29;
				else
					months[2] = 28;
				
			}
			else
				month++;
		}
		else
			day++;
	}

	printf("%04d%02d%02d", year, month, day);

	return 0;
}