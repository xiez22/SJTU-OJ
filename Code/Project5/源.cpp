#include "iostream"
using namespace std;

void addOne(int &a) {
	a++;
}

int main() {
	int a;
	//cin >> a;
	scanf("%d", &a);
	addOne(a);
	cout << a << endl;

	return 0;
}