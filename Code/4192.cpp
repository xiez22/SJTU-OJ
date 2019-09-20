#include "iostream"
#include "list"
#include "numeric"
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	int *nums = new int[n];
	for (int i = 0; i < n; i++)
		nums[i] = i;

	//存储最大数据
	list<int> List;
	List.push_back(0);
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			int temp = nums[i] ^ nums[j];
			//插入
			auto p = List.rbegin();
			/*for (; p != List.rend(); p++) {
				if (*p > temp)
					break;
			}
			if (p != List.rbegin()) {
				List.insert(p.base(), temp);
				if(List.size()>m)
					List.pop_back();
			}*/
		}
	}

	cout << accumulate(List.begin(), List.end(), 0)%int(1e9+7);

	return 0;
}