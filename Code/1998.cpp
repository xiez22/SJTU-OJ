#include "iostream"
#include "cmath"
#include "algorithm"
using namespace std;

int main() {
	int num;
	cin >> num;
	int *data = new int[num];
	for (int i = 0; i < num; i++)
		cin >> data[i];

	sort(data, data + num);
	int dis = 0;
	for (int i = 0; i < num;i++) {
		dis += abs(data[i] - data[num / 2]);
	}
	cout << dis;
	return 0;
}