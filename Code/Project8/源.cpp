#include <iostream>
#include<cstring>
void longchar(char b[], int t);
using namespace std;
int t, i, n;
char b[100];
bool c[100] = { 0 };

int main()
{
	char a[100];
	cin.getline(a, 100, '\n');
	t = strlen(a);
	for (i = 0; i < t; i++)b[i] = '0';
	for (i = 0; i < t; i++)b[i] = a[t - i - 1];
	n = t;
	longchar(b, t - 1);
	t = strlen(b);
	for (i = t - 1; i >= 0; i--)cout << b[i];
	return 0;
}

void longchar(char b[], int t) {

	if (t == 0) {
		if (b[0] > '8') {
			b[0] -= 9;
			c[1] = 1;
		}
		else b[0]++;
	}
	if (t > 0) {
		longchar(b, t - 1);
		if ((b[t] == '9') && (c[t] == 1)) {
			if (t == n - 1) { b[t + 1] = '1'; }
			b[t] -= 9; c[t + 1] = 1;

		}
		else if ((c[t] == 1) && (b[t] <= '8')) {

			b[t]++;
		}

	}

}
