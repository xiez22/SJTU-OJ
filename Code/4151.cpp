#include "iostream"
#include "cstdio"
using namespace std;

int main() {
	int T;
	ios::sync_with_stdio(false);
	cin >> T;

	for (; T > 0; T--) {
		int num;
		bool flag = true;
		cin >> num;
		int stackTop = 0;
		//²»¶Ï±éÀúÄ£Äâ
		for (int i = 0, n = 1; i < num; i++) {
			int currentNum;
			cin >> currentNum;
			if (!flag) continue;
			if (n <= currentNum) {
				stackTop = currentNum;
				n = currentNum + 1;
			}
			if (currentNum <= stackTop)
				stackTop=currentNum;
			else {
				flag = false;
			}
		}
		
		if (flag)
			printf("Yes\n");
		else
			printf("No\n");
			
	}


	return 0;
}