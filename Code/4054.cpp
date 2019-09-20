#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
using namespace std;

long long poww(int i) {
	long long ans = 1;
	for (int j = 0; j < i; ++j)
		ans *= 10;
	return ans;
}

long long cal(char* ch) {
	int len = strlen(ch);
	if (len == 1)
		return ch[0] - '0';
	if (len == 2) {
		if (ch[0] > ch[1])
			return ch[0] - '1' + 9;
		else
			return ch[0] - '0' + 9;
	}
	int temp = ch[0] > ch[len - 1] ? ch[len - 1] - '0' : ch[0] - '0';

	long long ans = 9;
	for (int i = 0; i < len - 2; ++i)
		ans += (long long)9 * poww(i);
	long long p = 1;
	char ch1[100];
	strcpy(ch1, ch + 1);
	ch1[strlen(ch1) - 1] = 0;
	sscanf(ch1, "%lld", &p);
	if (ch[0] <= ch[len - 1])
		ans += p + 1;
	else
		ans += p;
	ans += (long long)(ch[0] - '1') * poww(len - 2);
	return ans;
}

int main() {
	
	char L[100], R[100];
	cin >> L >> R;

	long long Lans, Rans;
	Lans = cal(L);
	Rans = cal(R);

	if (L[0] == L[strlen(L) - 1])
		++Rans;

	cout << Rans - Lans;

	return 0;
}