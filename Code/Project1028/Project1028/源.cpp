//WA - 90

#include <iostream>
#include <cstring>
using namespace std;

int bucket[5] = { 0 };

int cmp(char arr[]) {
	if (!strcmp(arr, "begin"))
		return 0;
	if (!strcmp(arr, "end"))
		return 1;
	if (!strcmp(arr, "if"))
		return 2;
	if (!strcmp(arr, "then"))
		return 3;
	if (!strcmp(arr, "else"))
		return 4;
}

int main() {
	int n;
	cin >> n;
	bool flag = false, isif = false, isbegin = false;
	char arr[109][6];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		bucket[cmp(arr[i])]++;
		if (cmp(arr[i]) == 2)
			isif = true;
		if (cmp(arr[i]) == 3 && isif == true) 
			isif = false;
		if (cmp(arr[i]) == 0 && isif == true) 
			isbegin = true;
		if (cmp(arr[i]) == 1 && isif == true && isbegin == true) {
			cout << "NO";
			flag = true;
			break;
		}
		if (bucket[0] < bucket[1] || bucket[2] < bucket[3] || bucket[2] < bucket[4]) {
			cout << "NO";
			flag = true;
			break;
		}
	}
	if (flag == false) {
		if (bucket[0] == bucket[1] && bucket[2] == bucket[3]) {
			cout << "YES";
		}
		else {
			cout << "NO";
		}
	}
	return 0;
}