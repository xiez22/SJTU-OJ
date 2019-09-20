#include "iostream"
#include "cstdio"
using namespace std;

int *findNum(int *data,int dataSize, int num) {
	if (dataSize == 0) return data-1;
	if (data[dataSize / 2] == num) return data + dataSize / 2;
	else if (data[dataSize / 2] < num) return findNum(data + dataSize / 2 + 1, dataSize - dataSize / 2 - 1, num);
	else return findNum(data, dataSize / 2, num);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int N, T;
	cin >> N >> T;
	int *NList = new int[N];

	//为了提高输入输出速度，全部改用scanf和printf。（只有这样才可以通过OJ）
	for (int i = 0; i < N; i++) {
		cin >> NList[i];
	}

	for (int i = 0; i < T; i++) {
		int temp;
		cin >> temp;
		if (i != T - 1)
			cout<<N - 1 - int(findNum(NList, N, temp) - NList)<<endl;
		else
			cout<<N - 1 - int(findNum(NList, N, temp) - NList);
	}
	return 0;
}