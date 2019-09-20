#include <iostream>
#include <vector>
using namespace std;

class node {
public:
	int parent = 0;
	vector<int> child;
	vector<int> isbad;
	bool good = false;
};

int n;
vector<node> tdata;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	tdata.resize(n + 1);

	for (int a = 0; a < n; ++a) {
		int i, j, k;
		cin >> i >> j >> k;

		tdata[i].child.emplace_back(j);
		tdata[j].child.emplace_back(i);
		
	}

	return 0;
}