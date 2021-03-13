
#include <iostream>
#include <stdio.h>
using namespace std;
int dayOfMonth[][13] = { {0,31,28,31,30,31,30,31,31,30,31,30,31},{0,31,29,31,30,31,30,31,31,30,31,30,31} };
struct Date
{
	int y, m, d;
	int leap()
	{
		return (y % 4 == 0 && y % 100 != 0 || y % 400 == 0 ? 1 : 0);
	}
	int week()
	{
		int Y = y, M = m;
		if (m == 1 || m == 2)
		{
			Y--;
			M += 12;
		}
		int W = (d + M * 2 + 3 * (M + 1) / 5 + Y + Y / 4 - Y / 100 + Y / 400) % 7;
		return W + 1;
	}
	Date() {}
	Date(int yy, int mm, int dd) { y = yy; m = mm; d = dd; }
	Date getNext()
	{
		Date t(y, m, d);
		if (d < dayOfMonth[leap()][m])
			t.d += 1;
		else if (m < 12)
		{
			t.m += 1;
			t.d = 1;
		}
		else
		{
			t.y += 1;
			t.m = 1;
			t.d = 1;
		}
		return t;
	}

	bool dealDay()
	{
		if (week() == 6 || week() == 7)
			return false;
		if (m == 1 && d == 1 || m == 5 && d >= 1 && d <= 3 || m == 10 && d >= 1 && d <= 7)
			return false;
		return true;
	}
	bool isWeekend()
	{
		return week() == 6 || week() == 7;
	}

};
bool equals(Date d1, Date d2)
{
	return d1.y == d2.y && d1.m == d2.m && d1.d == d2.d;
}

int ansOfYear(int year)
{
	bool isleap = (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
	int res = (isleap ? 366 : 365), t1, t2, t3 = 0, i;
	t1 = 104;
	if (isleap)
	{
		if (Date(year, 12, 30).isWeekend())
			t1 += 1;
		if (Date(year, 12, 31).isWeekend())
			t1 += 1;
	}
	else
	{
		if (Date(year, 12, 31).isWeekend())
			t1 += 1;
	}
	t2 = 11;
	if (Date(year, 1, 1).isWeekend())
		t3 += 1;
	for (i = 1; i < 4; i++)
		if (Date(year, 5, i).isWeekend())
			t3 += 1;
	for (i = 1; i < 8; i++)
		if (Date(year, 10, i).isWeekend())
			t3 += 1;
	res = res - t1 - t2 + t3;
	return res;
}

int main()
{
	int n, res = 0, i;
	Date d1, d2, t;
	scanf("%d", &n);
	while (n--)
	{
		res = 0;
		scanf("%d-%d-%d %d-%d-%d", &d1.y, &d1.m, &d1.d, &d2.y, &d2.m, &d2.d);
		if (d2.y - d1.y <= 1)
		{
			for (t = d1; !equals(t, d2.getNext()); t = t.getNext())
				if (t.dealDay())
					res += 1;
		}
		else
		{
			for (t = d1; !equals(t, Date(d1.y + 1, 1, 1)); t = t.getNext())
				if (t.dealDay())
					res += 1;
			for (t = Date(d2.y, 1, 1); !equals(t, d2.getNext()); t = t.getNext())
				if (t.dealDay())
					res += 1;
			for (i = d1.y + 1; i < d2.y; i++)
				res += ansOfYear(i);
		}
		printf("%d\n", res);
	}
	return 0;
}
