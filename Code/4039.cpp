#include "iostream"
using namespace std;

int main() {
	int input;
	cin >> input;
	
	for (int i = 2;i<=input; i++) {
		while (1) {
			//²»¶ÏµØ³ı
			if (input == i) {
				cout << i;
				break;
			}
			else if (input%i == 0) {
				input /= i;
				cout << i << " ";
			}
			else
				break;
		}
	}
	return 0;
}