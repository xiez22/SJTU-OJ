#include "iostream"
#include "cstring"
using namespace std;

int main() {
	char a[200], b[200];
	cin >> a >> b;
	char ans[200] = { 0 };
	for (int i = strlen(a)-1, j = strlen(b)-1,temp=0; i >= 0 || j >= 0 || temp != 0; i--, j--) {
		int n1 = i < 0 ? 0 : a[i] - 'a';
		int n2 = j < 0 ? 0 : b[j] - 'a';

		if (n1 + n2 + temp > 25) {
			ans[strlen(ans)] = 'a' + n1 + n2 + temp - 26;
			temp = 1;
		}
		else {
			ans[strlen(ans)] = 'a' + n1 + n2 + temp;
			temp = 0;
		}
	}

	//µ¹ĞòÊä³ö
	for (int i = strlen(ans) - 1; i >= 0; i--)
		cout << ans[i];

	return 0;
}