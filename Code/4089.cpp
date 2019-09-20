#include "iostream"
using namespace std;

constexpr auto maxNum = 1000;

class Joseph {
	bool exi[maxNum];
public:
	int n, m;
	Joseph(int n,int m):n(n),m(m){
		for (int i = 0; i <= n; i++) exi[i] = true;
	}

	void simulate() {
		int num = n;
		int cal = 0, sci = 1;
		while (num > 0) {
			if (!exi[sci]) {
				sci++;
				if (sci> n)
					sci = 1;
				continue;
			}
			if (cal == m) {
				cout << sci;
				cal = 0;
				exi[sci] = false;
				num--;
				if (num > 0)
					cout << " ";
			}
			sci++;
			cal++;
			if (sci>n)
				sci = 1;
		}
	}
};

int main() {
	int m, n;
	cin >> m >> n;
	Joseph j(m, n);

	j.simulate();

	return 0;
}