#include <iostream>
#include "cstdio"
using namespace std;

class MyComplex
{
private:
	double x, y;
public:
	friend istream& operator>>(istream& input, MyComplex &b) {
		input >> b.x >> b.y;
		return input;
	}
	friend ostream& operator<<(ostream& output, const MyComplex &b) {
		char op[1000];
		sprintf(op, "%.2f %.2f", b.x, b.y);
		output << op;
		//output << fixed << setprecision(2) << b.x << " " << b.y;
		return output;
	}

	MyComplex operator+(const MyComplex &b) const{
		MyComplex temp;
		temp.x = x + b.x;
		temp.y = y + b.y;
		return temp;
	}

	MyComplex operator-(const MyComplex &b) const {
		MyComplex temp;
		temp.x = x - b.x;
		temp.y = y - b.y;
		return temp;
	}

	MyComplex operator*(const MyComplex &b) const {
		MyComplex temp;
		temp.x = x * b.x - y * b.y;
		temp.y = x * b.y + y * b.x;
		return temp;
	}

	MyComplex operator/(const MyComplex &b) const {
		MyComplex temp;
		double data = b.x*b.x + b.y*b.y;
		temp.x = (x*b.x + y * b.y) / data;
		temp.y = (y*b.x - x * b.y) / data;
		return temp;
	}

	MyComplex &operator+=(const MyComplex &b) {
		*this = *this + b;
		return *this;
	}

	MyComplex &operator-=(const MyComplex &b) {
		*this = *this - b;
		return *this;
	}

	MyComplex &operator*=(const MyComplex &b) {
		*this = *this * b;
		return *this;
	}

	MyComplex &operator/=(const MyComplex &b) {
		*this = *this / b;
		return *this;
	}
};

int main()
{
	MyComplex z1;
	MyComplex z2;

	cin >> z1 >> z2;

	cout << z1 + z2 << endl;
	cout << z1 - z2 << endl;
	cout << z1 * z2 << endl;
	cout << z1 / z2 << endl;
	cout << (z1 += z2) << endl;
	cout << (z1 -= z2) << endl;
	cout << (z1 *= z2) << endl;
	cout << (z1 /= z2);

	return 0;
}