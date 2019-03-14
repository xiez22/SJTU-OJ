#include "iostream"
#include "cstdio"
using namespace std;

int main() {
	int a, b, c, y1, y2;
	cin >> a >> b >> c >> y1 >> y2;
	--c;

	int months[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

	for (int year = 1850, weekday = 1; year <= y2; ++year) {
		//判断是否是闰年
		bool is_year = false;
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
			months[2] = 29;
			is_year = true;
		}
		else {
			months[2] = 28;
			is_year = false;
		}
		if(year<y1){
			if (is_year)
				weekday = (weekday + 2) % 7;
			else
				weekday = (weekday + 1) % 7;
			continue;
		}
		int cur_day = weekday;
		//计算月份
		for (int month = 1; month < a; ++month)
			cur_day = (cur_day + months[month] % 7) % 7;
		//计算第一个日期
		int first_date = (c + 7 - cur_day) % 7 + 1;
		int date = first_date + (b - 1) * 7;
		if (date <= months[a])
			printf("%d/%02d/%02d\n", year, a, date);
		else
			printf("none\n");

		//调整日期
		if (is_year)
			weekday = (weekday + 2) % 7;
		else
			weekday = (weekday + 1) % 7;
	}

	return 0;
}