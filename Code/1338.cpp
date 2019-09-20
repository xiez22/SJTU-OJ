#include "iostream"
#include "cstdio"
using namespace std;

void myMergeSort(int* data, int num) {
	if (num == 0) return;
	else if (num == 1) return;

	myMergeSort(data, num / 2);
	myMergeSort(data + num / 2, num - num / 2);

	//合并
	int* temp = new int[num];

	for (int i = 0, j = num / 2, n = 0; i < num / 2 || j < num; n++) {
		if (i < num / 2 && j < num) {
			if (data[i] < data[j]) {
				temp[n] = data[i];
				i++;
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
		}
	}

	//复制
	for (int i = 0; i < num; i++)
		data[i] = temp[i];

	delete temp;
}

int A[100009], B[100009];

int main() {
	int len;
	cin >> len;

	for (int i = 0; i < len; ++i)
		scanf("%d", &A[i]);
	for (int i = 0; i < len; ++i)
		scanf("%d", &B[i]);

	myMergeSort(A, len);
	myMergeSort(B, len);

	//计算
	unsigned long long ans = 0;
	for (int i = 0; i < len; ++i)
		ans += (long long)A[i] * (long long)B[i];
	cout << ans << " ";
	ans = 0;
	for (int i = 0; i < len; ++i)
		ans += (long long)A[i] * (long long)B[len - i - 1];
	cout << ans;

	return 0;
}