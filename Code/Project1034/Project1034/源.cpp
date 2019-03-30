#include "iostream"
#include "cstdio"
using namespace std;

int val[400009] = { 0 };
class f_queue {
public:
	int queue_data[400009] = { 0 };
	int start = 0;
	int end = 0;
	void push(int num) {
		int i = end;
		for (; i > start; --i) {
			if (queue_data[i - 1] >= num)
				break;
		}
		queue_data[i] = num;
		end = i + 1;
	}
	void pop(int num) {
		if (num == queue_data[start])
			++start;
	}
	int front() {
		return queue_data[start];
	}
};

f_queue qdata;

int main() {
	int N, K;
	cin >> N >> K;

	int init = 0;
	for (int i = 0, cur_max = 0; i < N; ++i) {
		scanf("%d", &val[i]);
	}
	
	//Æ´½Ó
	for (int i = 0; i < K; ++i) {
		val[N + i] = val[i];
		qdata.push(val[i]);
	}

	int rp_max = qdata.front();
	for (int i = 0; i < N; ++i) {
		qdata.pop(val[i]);
		qdata.push(val[i + K]);
		if (qdata.front() < rp_max)
			rp_max = qdata.front();
	}

	cout << rp_max;

	return 0;
}