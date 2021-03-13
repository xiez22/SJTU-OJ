#include "iostream"
using namespace std;

int main() {
	int num;
	cin >> num;

	for (; num > 0; num--) {
		int data[9][9];
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				cin >> data[i][j];

		//Check
		bool flag = false;
		for (int i = 0; i < 9; i++) {
			bool check[9] = { 0 };
			for (int j = 0; j < 9; j++) {
				if (check[data[i][j] - 1]) {
					cout << "Wrong" << endl;
					flag = true;
					break;
				}
				check[data[i][j] - 1] = true;
			}
			if (flag)
				break;
		}
		if (flag)
			continue;

		//Check
		flag = false;
		for (int i = 0; i < 9; i++) {
			bool check[9] = { 0 };
			for (int j = 0; j < 9; j++) {
				if (check[data[j][i] - 1]) {
					cout << "Wrong" << endl;
					flag = true;
					break;
				}
				check[data[j][i] - 1] = true;
			}
			if (flag)
				break;
		}
		if (flag)
			continue;

		flag = false;
		for (int i = 0; i < 9; i += 3) {
			for (int j = 0; j < 9; j += 3) {
				//Small Square
				bool check[9] = { 0 };
				for (int m = 0; m < 3; m++) {
					for (int n = 0; n < 3; n++) {
						if (check[data[i + m][j + n] - 1]) {
							flag = true;
							cout << "Wrong" << endl;
							goto outside;
						}
						check[data[i + m][j + n] - 1] = true;
					}
				}
			}
		}

	outside:
		if (flag)
			continue;
		cout << "Right" << endl;
	}

	return 0;
}