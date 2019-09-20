#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class plane {
public:
	int id, t, u, g;

	plane(int id, int t, int u, int g) :id(id), t(t), u(u), g(g) {}

	bool operator<(const plane& other) const{
		return t > other.t;
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int N, MAX, S;
	cin >> N >> MAX >> S;

	priority_queue<plane> qdata;
	for (int i = 0; i < N; ++i) {
		int t, u, g;
		cin >> t >> u >> g;
		qdata.push(plane(i, t, u, g));
	}

	vector<int> ans(N);
	int cur_land = -999999999;
	while (!qdata.empty()) {
		auto temp = qdata.top();
		qdata.pop();

		//ÅÐ¶ÏÊÇ·ñÏà×²
		if (!qdata.empty() && qdata.top().t == temp.t) {
			cout << "CHANGE BOYFRIEND";
			return 0;
		}
		if (temp.t >= MAX) {
			cout << "GO DATING";
			return 0;
		}
		if (ans.empty() || temp.t + temp.u >= cur_land + S) {
			cur_land = ans[temp.id] = temp.t + temp.u;
		}
		else {
			qdata.push(plane(temp.id, temp.t + temp.g, temp.u, temp.g));
		}
	}

	for (auto p : ans)
		cout << p << "\n";


	return 0;
}