#include "iostream"
#include "algorithm"
using namespace std;

int main() {
	int num;
	cin >> num;
	int *data = new int[num];

	for (int i = 0; i < num; i++) {
		cin >> data[i];
	}

	long long windows[3] = { 0 };
	long long totalTime = 0, totalWaiting = 0;

	//计算总时间
	for (int i = 0; i < num; i++) {
		totalWaiting += windows[i % 3];
		windows[i % 3] += data[i];
	}

	totalTime = *max_element(windows, windows + 3);

	cout << totalWaiting << " " << totalTime << endl;

	totalTime = 0, totalWaiting = 0;

	//新方法
	long long newWindows[3] = { 0 };

	for (int i = 0; i < num; i++) {
		auto p = min_element(newWindows, newWindows + 3);
		totalWaiting += *p;
		//进入队列
		*p += data[i];
	}

	totalTime = *max_element(newWindows, newWindows + 3);

	cout << totalWaiting << " " << totalTime;

	return 0;
}