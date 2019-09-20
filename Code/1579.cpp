#include "iostream"
#include "algorithm"
#include "cstring"
using namespace std;

int ansData[1000][1000];
char str1[1009], str2[1009];
int lcs(int start1, int start2, int end1, int end2) {
	if (start1 >= end1 || start2 >= end2) return 0;
	//ÅĞ¶ÏÊÇ·ñÖØ¸´
	if (ansData[start1][start2] >= 0) return ansData[start1][start2];
	//µİ¹é
	if (str1[start1] == str2[start2]) {
		ansData[start1][start2] = lcs(start1 + 1, start2 + 1, end1, end2) + 1;
		return ansData[start1][start2];
	}
	else {
		ansData[start1][start2] = max(lcs(start1 + 1, start2, end1, end2),
			lcs(start1, start2 + 1, end1, end2));
		return ansData[start1][start2];
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int len1, len2;
	memset(ansData, -1, sizeof(ansData));

	cin >> len1 >> len2;
	cin >> str1 >> str2;

	cout << lcs(0, 0, len1, len2);

	return 0;
}