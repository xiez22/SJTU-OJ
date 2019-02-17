//由于二叉查找树的实现较为简单但繁琐，所以本题先采用STL实现，待开学后用自己的类实现
#include "iostream"
#include "cstring"
#include "set"
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	multiset<int> setData;

	int num;
	cin >> num;
	for (; num > 0; num--) {
		char op[100];
		cin >> op;
		if (strcmp(op, "insert") == 0) {
			int temp;
			cin >> temp;
			setData.insert(temp);
		}
		else if (strcmp(op, "delete") == 0) {
			int temp;
			cin >> temp;
			if(auto iter=setData.find(temp);iter!=setData.end())
				setData.erase(iter);
		}
		else if (strcmp(op, "delete_less_than") == 0) {
			int temp;
			cin >> temp;
			for (auto p = setData.begin(); p != setData.end(); ) {
				if (*p < temp) {
					setData.erase(p++);
				}
				else break;
			}
		}
		else if (strcmp(op, "delete_greater_than") == 0) {
			int temp;
			cin >> temp;
			for (auto p = setData.begin();p!=setData.end(); ) {
				if (*p > temp) {
					setData.erase(p++);
				}
				else ++p;
			}
		}
		else if (strcmp(op, "delete_interval") == 0) {
			int l, r;
			cin >> l >> r;
			for (auto p = setData.begin(); p != setData.end();) {
				if (*p > l && (*p) < r)
					setData.erase(p++);
				else if (*p >= r)
					break;
				else ++p;
			}
		}
		else if (strcmp(op, "find") == 0) {
			int temp;
			cin >> temp;
			if (setData.find(temp) != setData.end())
				cout << "Y" << endl;
			else cout << "N" << endl;
		}
		else if (strcmp(op, "find_ith") == 0) {
			int temp;
			bool flag = false;
			cin >> temp;
			int i = 1;
			for (auto p = setData.begin(); p != setData.end(); ++p, ++i) {
				if (i == temp) {
					flag = true;
					cout << *p << endl;
					break;
				}
			}
			if (!flag)
				cout << "N" << endl;
		}
	}


	return 0;
}