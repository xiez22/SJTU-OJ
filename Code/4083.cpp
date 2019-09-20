#include "iostream"
#include "cstring"

using namespace std;

//交换
template <class T>
constexpr void mySwap(T&a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

//冒泡排序
//(bool为真表示需要交换)
template <class T>
constexpr void bubbleSort(T *destination, T *source, int num, bool(*f)(T a, T b)) {
	//复制
	if (destination != source)
		for (int i = 0; i < num; i++)
			destination[i] = source[i];

	for (int i = num - 2; i >= 0; i--)
		for (int j = 0; j <= i; j++)
			if (f(destination[j], destination[j + 1]))
				mySwap(destination[j], destination[j + 1]);
}

class student {
public:
	char name[100];
	int xuehao=0, chengji = 0;
};

int main() {
	student stu[10000];
	int num = 0;
	while (true) {
		int n=0;
		cin >> n;
		if (n == 7) {
			cout << "END";
			break;
		}

		switch (n) {
		case 1: {
			int temp;
			bool flag = false;
			cin >> temp;
			for (int i = 0; i < num; i++) {
				if (stu[i].xuehao == temp) {
					flag = true;
					break;
				}
			}
			if (flag) {
				cout << "FAILED" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}
			stu[num].xuehao = temp;
			cin >> stu[num].name;
			cin >> stu[num].chengji;
			num++;
			cout << "SUCCESS" << endl;
			break;
		}
		case 2: {
			for (int i = 0; i < num; i++)
				cout << stu[i].xuehao << " " << stu[i].name << " " << stu[i].chengji << endl;
			break;
		}
		case 3: {
			int temp;
			cin >> temp;
			for (int i = 0; i < num; i++) {
				if (stu[i].xuehao == temp) {
					cout << stu[i].xuehao << " " << stu[i].name << " " << stu[i].chengji << endl;
					break;
				}
			}
			break;
		}
		case 4: {
			char temp[100];
			cin >> temp;
			for (int i = 0; i < num; i++) {
				if (strcmp(temp,stu[i].name)==0) {
					cout << stu[i].xuehao << " " << stu[i].name << " " << stu[i].chengji << endl;
					break;
				}
			}
			break;
		}
		case 5: {
			student temp[10000];
			bubbleSort<student>(temp, stu, num, [](student stu1, student stu2) {return stu1.xuehao > stu2.xuehao ? true : false; });
			for (int i = 0; i < num; i++)
				cout << temp[i].xuehao << " " << temp[i].name << " " << temp[i].chengji << endl;
			break;
		}
		case 6: {
			student temp[10000];
			bubbleSort<student>(temp, stu, num, [](student stu1, student stu2) {return stu1.chengji < stu2.chengji ? true : false; });
			for (int i = 0; i < num; i++)
				cout << temp[i].xuehao << " " << temp[i].name << " " << temp[i].chengji << endl;
			break;
		}
		}
	}
	return 0;
}