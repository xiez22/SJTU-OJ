#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

class person {
public:
	int parent = 0, childnum = 0;
	bool status = true;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	unordered_map<int, int> person_map;
	vector<person> vdata;
	int total_cnt = 1, ans = 1;

	//Init
	person fiperson;
	fiperson.status = false;
	vdata.emplace_back(fiperson);
	fiperson.status = true;
	vdata.emplace_back(fiperson);
	person_map.insert(make_pair(1, 1));

	for (; n; --n) {
		string ch;
		cin >> ch;

		if (ch == "B") {
			int x, y;
			cin >> x >> y;
			person tmp;
			tmp.parent = person_map[x];
			vdata[person_map[x]].childnum++;
			vdata.emplace_back(tmp);
			person_map.insert(make_pair(y, ++total_cnt));
		}
		else if (ch == "D") {
			int x;
			cin >> x;
			vdata[person_map[x]].status = false;
			if (!vdata[person_map[x]].parent || !vdata[vdata[person_map[x]].parent].status) {
				ans += vdata[person_map[x]].childnum - 1;
			}
			else {
				--vdata[vdata[person_map[x]].parent].childnum;
				ans += vdata[person_map[x]].childnum;
			}
			person_map.erase(x);
			cout << ans << "\n";
		}
	}

	return 0;
}