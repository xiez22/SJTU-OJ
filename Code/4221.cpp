#include "iostream"
#include "stack"
#include "cstdio"
using namespace std;

stack<int> stack_data;

int main() {
	int n;
	scanf("%d", &n);


	int ans = 0;
	for (int i = 0; i < n; ++i) {
		int val, direction;
		scanf("%d %d", &val, &direction);
		if (direction) {
			stack_data.push(val);
		}
		else {
			while (!stack_data.empty()) {
				if (val >= stack_data.top())
					stack_data.pop();
				else {
					--ans;
					break;
				}
			}
			++ans;
		}
	}
	printf("%d", (int)stack_data.size() + ans);

	return 0;
}