#include "iostream"
using namespace std;

class Time {
public:
	int hour = 0, minute = 0, second = 0;

	Time &operator+=(const Time &t) {
		int jw = 0;
		second += t.second;
		if (second >= 60) {
			second -= 60;
			jw = 1;
		}
		minute += t.minute+jw;
		if (minute >=60) {
			minute -= 60;
			jw = 1;
		}
		else
			jw = 0;
		hour += t.hour+jw;
		if (hour >= 24) {
			hour -= 24;
		}
		return *this;
	}

	Time &operator-=(const Time &t) {
		int jw = 0;
		second -= t.second;
		if (second <0) {
			second += 60;
			jw = 1;
		}
		minute -= t.minute+ jw;
		if (minute <0) {
			minute += 60;
			jw = 1;
		}
		else
			jw = 0;
		hour -= t.hour + jw;
		if (hour< 0) {
			hour += 24;
		}
		return *this;
	}

	Time &operator++() {
		Time temp;
		temp.second = 1;
		*this += temp;
		return *this;
	}
	Time operator++(int) {
		Time temp, tmp;
		tmp = *this;
		temp.second = 1;
		*this += temp;
		return tmp;
	}

	Time &operator--() {
		Time temp;
		temp.second = 1;
		*this -= temp;
		return *this;
	}
	Time operator--(int) {
		Time temp, tmp;
		tmp = *this;
		temp.second = 1;
		*this -= temp;
		return tmp;
	}
};

istream &operator>>(istream &input, Time &t) {
	input >> t.hour >> t.minute >> t.second;
	return input;
}
ostream &operator<<(ostream &output,const Time &t) {
	output << (t.hour<10?"0":"")<<t.hour<<":" << (t.minute < 10 ? "0" : "")<< t.minute<<":" << (t.second < 10 ? "0" : "")<<t.second;
	return output;
}

int main() {
	Time time1, time2;
	cin >> time1 >> time2;
	time1 += (time2++);
	cout << time1 << endl;
	time1 -= time2;
	cout << time1 << endl;
	++time2;
	cout << time2 << endl;
	time2 += (time1--);
	cout << time2 << endl;
	--time1;
	cout << time1 << endl;
	time2 -= time1;
	cout << time2 << endl;

	return 0;
}