#include "iostream"
#include "vector"

using namespace std;

int main() {
	int M, data[20000];
	vector<int> monkeyList;
	cin >> M;
	for (int i = 0; i < M-1; i++)
		cin >> data[i];
	for (int i = 0; i < M; i++)
		monkeyList.push_back(i+1);

	for (int i = 0,current=0,len=M; i < M - 1; i++,len--) {
		int temp = (data[i]+current-1) % len;
		monkeyList.erase(monkeyList.begin()+temp);
		current = temp;
	}

	cout << monkeyList.back();

	return 0;
}