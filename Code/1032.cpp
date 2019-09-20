#include "iostream"
using namespace std;



class cur_data {
public:
	bool status = false;
	int m, n;
	cur_data() = default;
	cur_data(int m,int n,bool status=false):m(m),n(n),status(status){}
};
cur_data stack_data[20000];
int stack_size = 0;
int ackerman(int m, int n) {
	int cur_ans;
	cur_data data_temp(m, n, false);
	stack_data[stack_size++] = data_temp;

	while (stack_size > 0) {
		auto temp = stack_data[--stack_size];

		if (temp.m == 0) {
			cur_ans = temp.n + 1;
		}
		else if (temp.n == 0) {
			cur_data data_push(temp.m - 1, 1, false);
			stack_data[stack_size++] = data_push;
		}
		else {
			if (!temp.status) {
				cur_data data_push(temp.m, temp.n - 1, false);
				temp.status = true;
				stack_data[stack_size++] = temp;
				stack_data[stack_size++] = data_push;
			}
			else {
				cur_data data_push(temp.m - 1, cur_ans, false);
				stack_data[stack_size++] = data_push;
			}
		}
	}

	return cur_ans;
}

int main() {
	int m, n;
	cin >> m >> n;
	cout << ackerman(m, n);

	return 0;
}