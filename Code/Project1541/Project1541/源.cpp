#include "iostream"
#include "cstdio"
#include "set"
using namespace std;


int main() {
	int k, n;
	cin >> k >> n;

	multiset<int,greater<int>> mySet;
	
	int currentNum,*numData=new int[n];
	for (int i = 0; i < k; i++) {
		int tempNum;
		scanf("%d", &tempNum);
		numData[i] = tempNum;
	}

	mySet.insert(numData, numData + k);
	cout << *mySet.begin();
	for (int startNum = 0; startNum + k < n; startNum++) {
		int tempNum;
		scanf("%d", &tempNum);
		numData[startNum + k] = tempNum;
		mySet.erase(mySet.find(numData[startNum]));
		mySet.insert(tempNum);
		printf(" %d", *mySet.begin());
	}
	return 0;
}