#include "iostream"
#include "cstdio"
#include "cmath"
using namespace std;



long long myMergeSort(int *data, int num) {
	if (num == 0) return 0;
	else if (num == 1) return 0;

	long long result = 0;
	result += myMergeSort(data, num / 2);
	result += myMergeSort(data + num / 2, num - num / 2);
	
	//合并
	int *temp = new int[num];

	for (int i = 0, j = num / 2, n = 0; i < num / 2 || j < num;n++) {
		if (i < num / 2 && j < num) {
			if (data[i] < data[j]) {
				temp[n] = data[i];
				i++;
				result += j-num/2;
			}
			else {
				temp[n] = data[j];
				j++;
			}
		}
		else if (i == num / 2) {
			temp[n] = data[j];
			j++;
		}
		else if (j == num ) {
			temp[n] = data[i];
			i++;
			result += j-num/2;
		}
	}

	//复制
	for (int i = 0; i < num; i++)
		data[i] = temp[i];

	delete temp;
	return result;
}

long long myMergeSort(int *data,int *datab,int num) {
	if (num == 0) return 0;
	else if (num == 1) return 0;

	long long result = 0;
	result += myMergeSort(data,datab, num / 2);
	result += myMergeSort(data + num / 2,datab+num/2, num - num / 2);

	//合并
	int *temp = new int[num];
	int *tempb = new int[num];

	for (int i = 0, j = num / 2, n = 0; i < num / 2 || j < num; n++) {
		if (i < num / 2 && j < num) {
			if (data[i] < data[j]) {
				temp[n] = data[i];
				tempb[n] = datab[i];
				i++;
				result += j - num / 2;
			}
			else {
				temp[n] = data[j];
				tempb[n] = datab[j];
				j++;
			}
		}
		else if (i == num / 2) {
			temp[n] = data[j];
			tempb[n] = datab[j];
			j++;
		}
		else if (j == num) {
			temp[n] = data[i];
			tempb[n] = datab[i];
			i++;
			result += j - num / 2;
		}
	}

	//复制
	for (int i = 0; i < num; i++) {
		data[i] = temp[i];
		datab[i] = tempb[i];
	}

	delete temp;
	delete tempb;
	return result;
}

int a[100009], b[100009],aList[100009],bList[100009],temp[100009];

int main() {
	int num;
	cin >> num;

	for (int i = 0; i < num; i++) {
		scanf("%d", &a[i]);
		aList[i] = i;
	}
	for (int i = 0; i < num; i++) {
		scanf("%d", &b[i]);
		bList[i] = i;
	}

	//排序
	myMergeSort(a, aList, num);
	myMergeSort(b, bList, num);

	//按情况排序
	for (int i = 0; i < num; i++) {
		temp[bList[i]] = aList[i];
	}

	//再排序
	cout << myMergeSort(temp, b, num)%99999997;

	return 0;
}