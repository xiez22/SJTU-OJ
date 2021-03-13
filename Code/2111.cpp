#include "iostream"
#include "cstdio"
#include "cmath"
#include "set"
#include "algorithm"
using namespace std;

int main() {
	set<int> setdata;
	int M;
	cin >> M;
	
	for (; M > 0; --M) {
		int op, x;
		scanf("%d %d", &op, &x);

		if (op == 0) {
			auto p=setdata.lower_bound(x);
			if (p == setdata.end())
				printf("%d\n", (int)abs(*setdata.rbegin() - x));
			else if (p == setdata.begin())
				printf("%d\n", (int)abs(*setdata.begin() - x));
			else {
				int x1 = (int)abs(*p - x),
					x2 = (int)abs(*(--p) - x);
				printf("%d\n", min(x1, x2));
			}
				
		}
		else if (op == 1) {
			setdata.insert(x);
		}
		else {
			setdata.erase(setdata.find(x));
		}
	}
	return 0;
}