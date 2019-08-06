#include <iostream>
#include <cstring>
using namespace std;

class dset {
public:
	int set_data[30009] = { 0 };
	dset() {
		memset(set_data, -1, sizeof(set_data));
	}
	void set_union(int root1, int root2) {
		if (root1 == root2)
			return;
		if (set_data[root1] < set_data[root2]) {
			set_data[root1] += set_data[root2];
			set_data[root2] = root1;
		}
		else {
			set_data[root2] += set_data[root1];
			set_data[root1] = root2;
		}
	}
	int set_find(int pos) {
		if (set_data[pos] < 0)
			return pos;
		return set_data[pos] = set_find(set_data[pos]);
	}
};

dset set_data;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	for (; m > 0; --m) {
		int k;
		cin >> k;
		int temp;
		cin >> temp;
		for (; k > 1; --k) {
			int i;
			cin >> i;
			set_data.set_union(set_data.set_find(temp), set_data.set_find(i));
		}
	}

	cout << -set_data.set_data[set_data.set_find(0)];

	return 0;
}