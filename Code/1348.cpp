#include "iostream"
#include "iomanip"
#include "cstdio"
#include "queue"
#include "vector"
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
		queueData.push_back((T)0);
		sizeOfQueue = 0;
	}

	//compare函数返回父结点a与孩子结点b的关系正确与否
	myPriorityQueue(bool(*compare)(T a, T b)) :cmp(compare) {
		queueData.clear();
		queueData.push_back((T)0);
		sizeOfQueue = 0;
	}

	//根据数组建立堆
	void buildHeap(T *eleData, unsigned int eleNum) {
		queueData.clear();
		sizeOfQueue = eleNum;
		queueData.push_back((T)0);
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
	void push(const T& input) {
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
		if (sizeOfQueue == 0)
			return NULL;
		return queueData[1];
	}

	//出队
	T pop() {
		if (sizeOfQueue == 0)
			return NULL;
		auto temp = queueData[1];
		queueData[1] = queueData[sizeOfQueue--];
		queueData.pop_back();
		percolateDown(1);
		return temp;
	}
};

int main() {
	int N,num;
	cin >> N;
	int *songTime = new int[N];
	for (int i = 0; i < N; i++)
		scanf("%d", &songTime[i]);

	cin >> num;
	myPriorityQueue<int> boy, girl;
	int *boytemp = new int[num+1], *girltemp = new int[num+1],boyNum=0,girlNum=0;
	for (int i = 0; i < num; i++) {
		int sex;
		scanf("%d", &sex);
		if (sex == 1)
			scanf("%d", &boytemp[boyNum++]);
		else
			scanf("%d", &girltemp[girlNum++]);
	}
	//建立队列
	boy.buildHeap(boytemp, boyNum);
	delete boytemp;
	girl.buildHeap(girltemp, girlNum);
	delete girltemp;

	double boyTotal = 0, girlTotal = 0;

	for (long long currentTime = 0, i = 0; 
		i < N; 
		currentTime += songTime[i], i++) {
		//最后一首歌，大家一起来
		if (i == N - 1) {
			while (!boy.empty())
				boyTotal += currentTime - boy.pop();
			while (!girl.empty())
				girlTotal += currentTime - girl.pop();
		}
		//配对CP
		else {
			while (!boy.empty() && !girl.empty() && boy.top() <= currentTime&&girl.top() <= currentTime) {
				boyTotal += currentTime - boy.pop();
				girlTotal += currentTime - girl.pop();
			}
		}
	}	

	//输出
	printf("%.2f %.2f",boyTotal / boyNum,girlTotal / girlNum);
	delete songTime;
	return 0;
}
