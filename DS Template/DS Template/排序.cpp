//排序函数 By @ligongzzz
//更新时间：2019年3月9日


#include "iostream"
#include "algorithm"
#include "list"
using namespace std;

//默认函数(cmp为从前往后的正确顺序）
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


int main() {

	return 0;
}