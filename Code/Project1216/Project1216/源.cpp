#include "iostream"
#include "vector"
#include "algorithm"
#include "cstdio"
#include "cstring"
using namespace std;

constexpr int inf = 1e8;

template <class T>
class myPriorityQueue {
public:
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


	//构建
	myPriorityQueue() {
		queueData.clear();
		queueData.push_back((T)0);
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

	void refresh() {
		//向下过滤
		for (unsigned int pos = size() / 2; pos > 0; pos--)
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

int find(int num,int startPos,int& pos,int numSize,const vector<int> &b) {
	if (startPos > numSize)
		return -1;
	if (b[startPos] > num) {
		pos = startPos;
		return 0;
	}
	int pos1, pos2;
	int ans1 = find(num, startPos * 2, pos1, numSize, b),
		ans2 = find(num, startPos * 2 + 1, pos2, numSize, b);
	if (ans1 < 0 && ans2 < 0)
		return -1;
	else if (ans2 < 0) {
		pos = pos1;
		return 0;
	}
	else if (ans1 < 0) {
		pos = pos2;
		return 0;
	}
	else {
		if (b[pos1] < b[pos2]) {
			pos = pos1;
			return 0;
		}
		else if (b[pos1] > b[pos2]) {
			pos = pos2;
			return 0;
		}
		else {
			pos = min(pos1, pos2);
			return 0;
		}
	}
}

int main() {
	int M;
	cin >> M;
	myPriorityQueue<int> myQueue;

	for (; M > 0; M--) {
		char temp[100];
		scanf("%s", temp);
		if (strcmp(temp, "insert") == 0) {
			int tempNum;
			scanf("%d", &tempNum);
			myQueue.push(tempNum);
		}
		else if (strcmp(temp, "find") == 0) {
			int tempNum, pos;
			scanf("%d", &tempNum);
			find(tempNum, 1, pos, myQueue.size(), myQueue.queueData);
			printf("%d\n", pos);
		}
		else {
			int tempNum,v;
			scanf("%d %d", &tempNum,&v);
			myQueue.queueData[tempNum] -= v;

			//向上过滤
			for (auto i = tempNum; i > 1; i = i / 2) {
				//判断是否比父结点更小
				if (myQueue.queueData[i]<myQueue.queueData[i / 2]) {
					//交换
					auto temp = myQueue.queueData[i];
					myQueue.queueData[i] = myQueue.queueData[i / 2];
					myQueue.queueData[i / 2] = temp;
				}
				else break;
			}
			
		}
	}

	return 0;
}