#include "iostream"
#include "vector"
#include "algorithm"
#include "cstdio"
using namespace std;

template <class T>
class myPriorityQueue {
	vector<T> queueData;
	unsigned int sizeOfQueue = 0;
	bool(*cmp)(T a, T b) = [](T a, T b) {return a < b; };

	//向下过滤
	void percolateDown(unsigned int pos) {
		while (pos * 2 <= sizeOfQueue) {
			if (pos * 2 + 1 > sizeOfQueue) {
				//交换
				if (cmp(queueData[pos * 2], queueData[pos])) {
					auto temp = queueData[pos * 2];
					queueData[pos * 2] = queueData[pos];
					queueData[pos] = temp;
				}
				break;
			}
			else {
				bool minNum = cmp(queueData[pos * 2 + 1], queueData[pos * 2]);
				if (cmp(queueData[pos * 2 + minNum], queueData[pos])) {
					auto temp = queueData[pos * 2 + minNum];
					queueData[pos * 2 + minNum] = queueData[pos];
					queueData[pos] = temp;
					pos = pos * 2 + minNum;
				}
				else break;
			}
		}
	}

public:
	//构建
	myPriorityQueue() {
		queueData.clear();
		queueData.push_back(*new T);
		sizeOfQueue = 0;
	}

	//compare函数返回父结点a与孩子结点b的关系正确与否
	myPriorityQueue(bool(*compare)(T a, T b)) :cmp(compare) {
		queueData.clear();
		queueData.push_back(*new T);
		sizeOfQueue = 0;
	}

	//根据数组建立堆
	void buildHeap(T* eleData, unsigned int eleNum) {
		queueData.clear();
		sizeOfQueue = eleNum;
		queueData.push_back(*new T);
		for (unsigned int i = 1; i <= eleNum; i++)
			queueData.push_back(eleData[i - 1]);
		//向下过滤
		for (unsigned int pos = eleNum / 2; pos > 0; pos--)
			percolateDown(pos);
	}

	//判断是否空
	bool empty() {
		return sizeOfQueue == 0;
	}

	//返回队列大小
	auto size() {
		return sizeOfQueue;
	}

	//入队
	void push(const T & input) {
		sizeOfQueue++;
		queueData.push_back(input);

		//向上过滤
		for (auto i = sizeOfQueue; i > 1; i = i / 2) {
			//判断是否比父结点更小
			if (cmp(queueData[i], queueData[i / 2])) {
				//交换
				auto temp = queueData[i];
				queueData[i] = queueData[i / 2];
				queueData[i / 2] = temp;
			}
			else break;
		}
	}

	//队列最前
	T top() {
		return queueData[1];
	}

	//出队
	T pop() {
		auto temp = queueData[1];
		queueData[1] = queueData[sizeOfQueue--];
		queueData.pop_back();
		percolateDown(1);
		return temp;
	}
};

//用于保存数据的格式
class data_type {
public:
	int val = 0;
	int posa = 0, posb = 0;
	data_type() = default;
	data_type(int val,int posa,int posb):val(val),posa(posa),posb(posb){}
	bool operator<(const data_type& other) const {
		return val < other.val;
	}
};

int a[1000009] = { 0 }, b[1000009] = { 0 };
//构造堆
myPriorityQueue<data_type> queue_data;
//保存临时数据
data_type data_temp[1000009];
//保存答案
int ans_data[1000009];

int main() {
	int num;
	scanf("%d", &num);

	for (int i = 0; i < num; ++i)
		scanf("%d", &a[i]);
	for (int i = 0; i < num; ++i)
		scanf("%d", &b[i]);

	sort(a, a + num);
	sort(b, b + num);
	
	//初始化堆
	for (int i = 0; i < num; ++i) {
		data_type temp(a[0] + b[i], 0, i);
		data_temp[i] = temp;
	}

	queue_data.buildHeap(data_temp,num);

	//进行排序和写入
	for (int i = 0; i < num; ++i) {
		auto temp = queue_data.pop();
		//写入答案
		ans_data[i] = temp.val;
		//准备下一次
		if (i < num - 1) {
			++temp.posa;
			temp.val = a[temp.posa] + b[temp.posb];
			queue_data.push(temp);
		}
	}

	//输出答案
	printf("%d", ans_data[0]);
	for (int i = 1; i < num; ++i)
		printf(" %d", ans_data[i]);

	return 0;
}