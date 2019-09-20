#include "iostream"
#include "cstring"

using namespace std;

constexpr auto maxNum = 100;

//交换
template <class T>
void mySwap(T&a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

//冒泡排序
//(bool为真表示a>b,true代表升序)
template <class T>
void bubbleSort(T *destination, T *source, int num, bool(*f)(T a, T b),bool mode) {
	//复制
	if (destination != source)
		for (int i = 0; i < num; i++)
			destination[i] = source[i];

	for (int i = num - 2; i >= 0; i--)
		for (int j = 0; j <= i; j++)
			if ((f(destination[j], destination[j + 1])&&mode)|| (!f(destination[j], destination[j + 1]) && !mode))
				mySwap(destination[j], destination[j + 1]);
}

class student {
public:
	int chinese, math, english;
	char name[maxNum];

	student() =default;

	/*student(const student &stu) {
		strcpy(name, stu.name);
		chinese = stu.chinese;
		math = stu.math;
		english = stu.english;
	}*/

};

int main() {
	int n, k;
	char name[maxNum];
	cin >> n;
	student *stu = new student[n];
	for (int i = 0; i < n; i++) {
		cin >> stu[i].name;
		cin >> stu[i].chinese;
		cin >> stu[i].math;
		cin >> stu[i].english;
	}
	cin >> k;
	k--;

	//开始排序
	bubbleSort<student>(stu, stu, n, [](student stu1,student stu2) {
		int sum1 = stu1.chinese+stu1.math+stu1.english, sum2 = stu2.chinese+stu2.math+stu2.english;
		if (sum1 > sum2)
			return true;
		else if (sum1 < sum2)
			return false;
		else if (stu1.chinese > stu2.chinese)
			return true;
		else if (stu1.chinese < stu2.chinese)
			return false;
		else if (stu1.math > stu2.math)
			return true;
		else if (stu1.math < stu2.math)
			return false;
		else if (stu1.english > stu2.english)
			return true;
		else if (stu1.english < stu2.english)
			return false;
		else if (strcmp(stu1.name,stu2.name)<0)
			return true;
		else if (strcmp(stu1.name, stu2.name)>0)
			return false;

		return true;
	},false);

	//输出
	cout << stu[k].name << " " << stu[k].chinese + stu[k].math + stu[k].english;

	return 0;
}