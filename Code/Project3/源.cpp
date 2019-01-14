#include "iostream"
using namespace std;

int main() {
	char temp[1000];
	while (cin >> temp) {
		cout << temp << endl;
		if (getchar() == '\n')
			break;
	}
	cout << "Finish!" << endl;

	return 0;
}