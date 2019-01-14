#include "iostream"
#include "iomanip"
#include "cstdlib"
using namespace std;

constexpr auto EPS = 1E-6;

int main() {
	int i, n, item;
	double e;

	e = 1;
	n = 1;
	item = 1;

	do
	{
		item *= n;

		e += 1.0 / item;
		n++;
	} while (item <= 1.0/EPS);

	cout << "e=" << fixed << setprecision(6) << e << endl;

	system("pause");

	return 0;
}