#include "iostream"
#include "cstdio"
using namespace std;

long long myMergeSort(int *data, int num) {
	if (num == 0||num==1) return 0;

	long long result = 0;
	result += myMergeSort(data, num / 2)+myMergeSort(data + num / 2, num - num / 2);

	//ºÏ²¢
	int *temp = new int[num];

	for (int i = 0, j = num / 2, n = 0; i < num / 2 || j < num; n++) {
		if (i < num / 2 && j < num) {
			if (data[i] <= data[j]) {
				temp[n] = data[i];
				i++;
				result += j - num / 2;
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
		else if (j == num) {
			temp[n] = data[i];
			i++;
			result += j - num / 2;
		}
	}

	//¸´ÖÆ
	for (int i = 0; i < num; i++)
		data[i] = temp[i];

	delete temp;
	return result;
}

int main() {
	int num;
	cin >> num;
	int *trees = new int[num];
	for (int i = 0; i < num; i++)
		scanf("%d", &trees[i]);

	cout << myMergeSort(trees, num);

	return 0;
}