#include <iostream>
#include <vector>
using namespace std;

int cal(const vector<long long>& vdata, long long total) {
	long long base = 0;
	for (int pos = 0; pos < vdata.size(); ++pos) {
		bool flag = true;
		base += vdata[pos];
		
		if (total % base)
			continue;

		long long temp = 0;
		int cnt = 0;
		for (int i = 0, j = 0; j < vdata.size(); ++j) {
			temp += vdata[j];
			if (j == vdata.size() - 1) {
				if (temp != base) {
					flag = false;
					break;
				}
			}

			if (temp == base) {
				temp = 0;
				i = j + 1;
				++cnt;
			}
			else if (temp > base) {
				flag = false;
				break;
			}
		}
		if (flag) {
			return cnt;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int p;
	cin >> p;

	for (; p; --p) {
		int n, m;
		cin >> n >> m;

		vector<long long> vdata(m);

		long long total = 0;
		for (int i = 0; i < m; ++i) {
			cin >> vdata[i];
			total += vdata[i];
		}

		cout << n << " " << cal(vdata, total) << "\n";
	}

	return 0;
}