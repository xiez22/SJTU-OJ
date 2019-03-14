#include "iostream"
#include "cstdio"
using namespace std;

void quick_sort(int* from, int* to) {
	if (from == to || from + 1 == to)
		return;
	int key = *from;
	//¿ªÊ¼É¨Ãè
	bool status = true;
	auto p = from, q = to - 1;
	while (p != q) {
		if (status) {
			if (key < *q) {
				*p = *q;
				++p;
				status = false;
			}
			else {
				--q;
			}
		}
		else {
			if (key > * p) {
				*q = *p;
				--q;
				status = true;
			}
			else {
				++p;
			}
		}
	}
	*p = key;
	quick_sort(from, p + 1);
	quick_sort(p + 1, to);
}

int n_data[10009] = { 0 }, m_data[10009] = { 0 };

int main() {
	int N, M;
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; ++i)
		scanf("%d", &n_data[i]);
	for (int i = 0; i < M; ++i)
		scanf("%d", &m_data[i]);

	quick_sort(n_data, n_data + N);
	quick_sort(m_data, m_data + M);

	int ans = 0;
	for (int i = 0, j = 0; i < N; ++i) {
		++ans;
		if (j < M) {
			for (; j < M && m_data[j] >= n_data[i]; ++j);
			if (j < M) {
				++j;
				++ans;
			}
		}
	}

	printf("%d", ans);

	return 0;
}