#include "iostream"
#include "cstdio"
using namespace std;

int val[400009] = { 0 };
//单调队列类
class f_queue {
public:
	//存储单调队列数据的数组
	int queue_data[400009] = { 0 };
	//队头元素位置
	int start = 0;
	//队尾元素位置
	int end = 0;
	//插入函数
	void push(int num) {
		int i = end;
		//从队尾开始扫描，将小于num的元素全部弹出，直到遇到大于等于num的元素
		for (; i > start; --i) {
			if (queue_data[i - 1] >= num)
				break;
		}
		//将num放入单调队列中
		queue_data[i] = num;
		end = i + 1;
	}
	//弹出函数
	void pop(int num) {
		//判断需要弹出的num是否与队头元素相等，如果相等则将队头出队，如果不相等则不进行任何操作
		if (num == queue_data[start])
			++start;
	}
	//返回队头元素
	int front() {
		return queue_data[start];
	}
};

//单调队列
f_queue qdata;

int main() {
	int N, K;
	cin >> N >> K;

	int init = 0;
	for (int i = 0, cur_max = 0; i < N; ++i) {
		scanf("%d", &val[i]);
	}
	
	//拼接，并且将前K个元素入单调队列
	for (int i = 0; i < K; ++i) {
		val[N + i] = val[i];
		qdata.push(val[i]);
	}

	int rp_max = qdata.front();
	for (int i = 0; i < N; ++i) {
		//移动窗口，先将第i个元素出单调队列，再将第i+K个元素入队，并判断此时单调队列中的最大值是否比rp_max小
		qdata.pop(val[i]);
		qdata.push(val[i + K]);
		if (qdata.front() < rp_max)
			rp_max = qdata.front();
	}
	//输出答案rp_max
	cout << rp_max;

	return 0;
}