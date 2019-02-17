//图类 数据结构模板 By @ligongzzz
//更新时间：2019年1月20日


#include "iostream"
#include "queue"
#include "cstdio"
using namespace std;

//常量
constexpr auto maxPoints = 100009;
constexpr auto maxLines = 10;
constexpr auto inf = 9999999;

//结点
template <class T>
class myPoint {
public:
	int num = 0;
	int line[maxLines] = { 0 };
	T linelen[maxLines] = { 0 };
};

//有向图
template <class T>
class myGraph {
public:
	int num = 0;
	myPoint<T> points[maxPoints];

	void addPoint() {
		num++;
	}
	void addPoint(int n) {
		num += n;
	}
	void addLine(int from, int to, T length) {
		points[from].line[points[from].num] = to;
		points[from].linelen[points[from].num] = length;
		points[from].num++;
	}

	//最短路算法
	T SPFA(int from, int to) {
		T *length = new T[num];
		bool *inQueue = new bool[num];
		//记录最短路径
		for (int i = 0; i < num; i++) {
			length[i] = inf;
			inQueue[i] = false;
		}
		length[from] = 0.0;
		queue<int> road;
		//入队
		road.push(from);
		inQueue[from] = true;

		while (!road.empty()) {
			//出队一个节点
			int curPoint = road.front();
			inQueue[road.front()] = false;
			road.pop();

			//遍历
			for (int i = 0;
				i < points[curPoint].num;
				i++) {
				if (length[curPoint] +
					points[curPoint].linelen[i] <
					length[points[curPoint].line[i]]) {
					//更新
					length[points[curPoint].line[i]] = length[curPoint] + points[curPoint].linelen[i];
					if (!inQueue[points[curPoint].line[i]]) {
						road.push(points[curPoint].line[i]);
						inQueue[points[curPoint].line[i]] = true;
					}
				}
			}
		}
		auto result = length[to];
		delete length;
		delete inQueue;
		return result;
	}
};