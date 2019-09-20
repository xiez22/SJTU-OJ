#include "iostream"
#include "cstdio"
using namespace std;

bool check[100009] = { 0 };

int main() {
	int N, M;
	cin >> N >> M;

	auto cnt = N, pos = 0;

	for (int left = 0, right = cnt; cnt > 1; --cnt) {
		left = cnt - right;
		//计算最后一步的位移
		auto step = M % (2 * cnt - 2);
		if (step == 0)
			step = cnt * 2 - 2;
		if (step <= right) {
			//移动
			for (int i = 0; i < step; )
				if (!check[++pos])
					++i;
			right -= step;
		}
		else if (step < right * 2) {
			//移动
			for (int i = 0; i < right * 2 - step;)
				if (!check[++pos])
					++i;
			right = step - right;
		}
		else if (step < right * 2 + left - 1) {
			//移动
			for (int i = 0; i < step - right * 2 + 1;)
				if (!check[--pos])
					++i;
			right = step - right;
		}
		else {
			//移动
			for (int i = 0; i < cnt * 2 - 1 - step;)
				if (!check[--pos])
					++i;
			right += cnt * 2 - 2 - step;
		}
		check[pos] = true;
	}

	printf("%d", pos);

	return 0;
}