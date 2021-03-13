#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> mdata = {
	{1,2,4,5},
	{1,2,3},
	{2,3,5,6},
	{1,4,7},
	{2,4,5,6,8},
	{3,6,9},
	{4,5,7,8},
	{7,8,9},
	{5,6,8,9}
};

vector<int> vdata(10);

class clock {
public:
	int ttime[10] = { 0 };
	int last = 0;
};

queue<clock> qdata;

bool check(const clock& cur_time) {
	for (int i = 1; i <= 9; ++i) {
		if (i != 12)
			return false;
	}
	
	return true;
}

void bfs(const clock& cur_time) {
	for (int i = 1; i <= 9; ++i) {
		qdata.push(cur_time);
	}
	
	while (!qdata.empty()) {
		
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	for (int i = 1; i <= 9; ++i)
		cin >> vdata[i];



	return 0;
}