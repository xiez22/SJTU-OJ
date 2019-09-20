#include "iostream"
#include "queue"
#include "iomanip"
using namespace std;

int main() {
	queue<int> car;
	queue<int> truck;

	//输入
	int num;
	cin >> num;
	for (int i = 0; i < num; i++) {
		int temp,arrive;
		scanf("%d %d", &temp, &arrive);
		if (temp == 0)
			car.push(arrive);
		else
			truck.push(arrive);
	}

	long long carTime = 0, truckTime = 0;
	int carNum = car.size(), truckNum = truck.size();

	//开始模拟
	for (int t = 0;!car.empty()||!truck.empty(); t += 10) {
		//上船
		for (int n = 0,carn=0; n < 10; n++) {
			if (!car.empty()&&car.front() <= t && !truck.empty()&&truck.front() <= t) {
				if (carn< 4) {
					carTime += t-car.front();
					car.pop();
					carn++;
				}
				else {
					truckTime += t-truck.front();
					truck.pop();
					carn = 0;
				}
			}
			else if (!car.empty()&&car.front() <= t) {
				carTime += t-car.front();
				car.pop();
				carn++;
			}
			else if (!truck.empty()&&truck.front() <= t) {
				truckTime += t-truck.front();
				truck.pop();
			}
		}
	}

	printf("%.3f %.3f",(double)carTime / (double)carNum, (double)truckTime / (double)truckNum);

	return 0;
}