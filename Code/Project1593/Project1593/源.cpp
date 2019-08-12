#include "cstdio"
#include "iostream"
#include "cmath"
using namespace std;

constexpr int mod = (int)(1e8);

struct mouse_type {
	long long val = 0, strength = 0;
} mouse[200009];

bool cmp(const int& a, const int& b) {
	return mouse[a].val > mouse[b].val || (mouse[a].val == mouse[b].val && a < b);
}

int paiwei[200009] = { 0 };

template <class T, class T_val = decltype(*declval<T>()),
	class Compare = bool (*)(T_val, T_val)>
	void quick_sort(T start, T end,
		Compare cmp = [](T_val a, T_val b) {return a < b; }) {
	if (start == end)
		return;
	auto i = start, j = end;
	--j;
	if (i == j)
		return;
	//交换
	auto key = *start;
	for (bool status = true; i != j;) {
		if (status) {
			if (cmp(*j, key)) {
				*i = *j;
				++i;
				status = false;
			}
			else
				--j;
		}
		else {
			if (cmp(key, *i)) {
				*j = *i;
				--j;
				status = true;
			}
			else
				++i;
		}
	}
	*i = key;
	//递归
	quick_sort(start, ++i, cmp);
	quick_sort(i, end, cmp);
}

void arrange(int pos) {
	auto temp = paiwei[pos];
	auto p = pos - 1;
	for (; p >= 0; --p) {
		if (cmp(temp, paiwei[p])) {
			paiwei[p + 1] = paiwei[p];
		}
		else
			break;
	}
	paiwei[p + 1] = temp;
}

void myMergeSort(int* data, int num) {
	if (num == 0) return;
	else if (num == 1) return;

	myMergeSort(data, num / 2);
	myMergeSort(data + num / 2, num - num / 2);

	//合并
	int* temp = new int[num];

	for (int i = 0, j = num / 2, n = 0; i < num / 2 || j < num; n++) {
		if (i < num / 2 && j < num) {
			if (cmp(data[i], data[j])) {
				temp[n] = data[i];
				i++;
			}
			else {
				temp[n] = data[j];
				j++;
			}
		}
		else if (i == num / 2) {
			temp[n] = data[j];
			j++;
		}
		else if (j == num) {
			temp[n] = data[i];
			i++;
		}
	}

	//复制
	for (int i = 0; i < num; i++)
		data[i] = temp[i];

	delete temp;
}

int main() {
	int N, R;
	scanf("%d %d", &N, &R);
	N *= 2;
	//srand(0);
	for (int i = 1; i <= N; ++i) {
		paiwei[i - 1] = i;
		scanf("%lld", &mouse[i].val);
		//mouse[i].val =  rand()%mod;
	}
	for (int i = 1; i <= N; ++i) {
		scanf("%lld", &mouse[i].strength);
		//mouse[i].strength = rand()%mod;
	}

	//排序
	quick_sort(paiwei, paiwei + N, cmp);
	//myMergeSort(paiwei, N);

	//开始比赛
	for (int i = 0; i < R; ++i) {
		for (int step = 0; step < N; step += 2) {
			if (mouse[paiwei[step]].strength < mouse[paiwei[step + 1]].strength) {
				mouse[paiwei[step + 1]].val += 2;
				arrange(step + 1);
			}
			else if (mouse[paiwei[step]].strength == mouse[paiwei[step + 1]].strength) {
				++mouse[paiwei[step]].val;
				++mouse[paiwei[step + 1]].val;
				arrange(step);
				arrange(step + 1);
			}
			else {
				mouse[paiwei[step]].val += 2;
				arrange(step);
			}
		}
	}

	for (int i = 0; i < N; ++i)
		printf("%d ", paiwei[i]);

	return 0;
}