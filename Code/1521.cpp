#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

class node {
public:
	int first_max = 0, second_max = 0;
	int depth = 0;
	int parent = 0;
};

node tree_data[20009]{};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	tree_data[1].depth = 1;

	for (int i = 2; i <= n + m; ++i) {
		cin >> tree_data[i].parent;
		tree_data[i].depth = tree_data[tree_data[i].parent].depth + 1;
	}

	for (int i = n + m; i > 0; --i) {
		if (tree_data[i].depth > tree_data[i].first_max) {
			tree_data[i].second_max = tree_data[i].first_max;
			tree_data[i].first_max = tree_data[i].depth;
		}
		if (tree_data[i].depth > tree_data[i].second_max) {
			tree_data[i].second_max = tree_data[i].depth;
		}
		if (tree_data[i].first_max > tree_data[tree_data[i].parent].first_max) {
			tree_data[tree_data[i].parent].second_max = tree_data[tree_data[i].parent].first_max;
			tree_data[tree_data[i].parent].first_max = tree_data[i].first_max;
		}
		else if (tree_data[i].first_max > tree_data[tree_data[i].parent].second_max) {
			tree_data[tree_data[i].parent].second_max = tree_data[i].first_max;
		}
	}

	int ans = 0;
	for (int i = 1; i <= n + m; ++i) {
		int cur_ans = tree_data[i].first_max + tree_data[i].second_max - 2 * tree_data[i].depth;
		ans = cur_ans > ans ? cur_ans : ans;
	}

	cout << ans;

	return 0;
}