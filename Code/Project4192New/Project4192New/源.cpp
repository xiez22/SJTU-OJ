#include "iostream"
#include "cmath"
#include "list"
#include "map"
#include "numeric"
using namespace std;

//01二叉树
class newTree {
public:
	newTree *p1=nullptr;
	newTree *p2 = nullptr;
	bool data;
};


int main() {
	//头二叉树
	newTree *head=new newTree;

	int n, m;
	cin >> n >> m;
	int *nums = new int[n];
	
	//存储最大数据
	list<int> List;
	List.push_back(0);
	//查找地图
	map<int,int> Map;
	//二进制池
	bool **shitBool = new bool *[n];

	for (int i = 0; i < n; i++) {
		int temp;
		scanf("%d", &temp);
		nums[i] = temp;
		//转化为二进制
		shitBool[i] = new bool[31]{ 0 };
		for (int j = 30; temp != 0; j--) {
			shitBool[i][j] = temp % 2;
			temp /= 2;
		}
		//构建二叉树
		auto p = head;
		for (int j = 0; j < 31; j++) {
			if (!shitBool[i][j]) {
				//没有就创建
				if (p->p1 == nullptr)
					p->p1 = new newTree;
				p = p->p1;
				p->data = false;
			}
			else {
				//没有就创建
				if (p->p2 == nullptr)
					p->p2 = new newTree;
				p = p->p2;
				p->data = true;
			}
		}
	}

	//寻找最大数
	for (int i = 0; i < n; i++) {
		int temp = nums[i];
		//转化为二进制
		bool *newTemp = shitBool[i];
		temp = nums[i];
		//循环查找
		auto p = head;
		int cpNum = 0;
		int currentResult = 0;
		
		//寻找当前数字对应的最大或非值
		for (int j = 0; j < 31; j++) {
			if (!newTemp[j]) {
				if (p->p2 != nullptr) {
					p = p->p2;
					currentResult = currentResult * 2 + 1;
				}
				else {
					p = p->p1;
					currentResult = currentResult * 2;
				}
				cpNum= p->data+cpNum*2;
			}
			else {
				if (p->p1 != nullptr) {
					p = p->p1;
					currentResult = currentResult * 2 + 1;
				}
				else {
					p = p->p2;
					currentResult = currentResult * 2;
				}
				cpNum = p->data + cpNum * 2;
			}
		}

		//判断是否重复并插入
		auto mapFinder = Map.find(cpNum);
		if (mapFinder==Map.end()||mapFinder->second!=temp) {
			//加入map序列
			Map.insert(pair<int, int>(temp, cpNum));

			//插入
			auto tempp = List.rbegin();
			for (; tempp != List.rend(); tempp++) {
				if (*tempp > currentResult)
					break;
			}
			if (tempp != List.rbegin()) {
				List.insert(tempp.base(), currentResult);
				if (List.size() > m)
					List.pop_back();
			}
		}
	}

	cout << accumulate(List.begin(), List.end(), 0)%int(1e9+7);

	return 0;
}