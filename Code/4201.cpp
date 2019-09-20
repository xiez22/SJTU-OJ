#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
using namespace std;

constexpr double jd = 0.00001;

//交换
template <class T>
void mySwap(T&a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

struct School
{
	char name[7]; //学院名字
	double score; //加权总分
	int count;    //学生人数

	int scoreA = 0, scoreB = 0, scoreC = 0;
};

class Solution
{
public:
	Solution(int cnt) { numOfSchool = 0; schools = new School[cnt]; }
	//根据学生信息，修改所在学院的相应信息
	void modify(char* id, double score, char* schoolName);
	void displayResult();  //输出
	~Solution() { delete[] schools; }

	// 可以根据设计自行添加所需成员

private:
	School *schools;    // 存放学院信息的指针
	unsigned int numOfSchool;  // 学院数量

// 可以根据设计自行添加所需成员

};
void Solution::displayResult() {
	//算分
	for (int i = 0; i < numOfSchool; i++) {
		schools[i].score = double(schools[i].scoreA) + double(schools[i].scoreB) / 1.5 + double(schools[i].scoreC) * 1.5;
	}

	//开始排序
	sort(schools, schools + numOfSchool, [](School a, School b) {
		return int(a.score) > int(b.score) ||
			int(a.score) == int(b.score) && (a.count < b.count) ||
			(int(a.score) == int(b.score) && (a.count == b.count) && strcmp(a.name, b.name) < 0);
	});
	/*auto num = numOfSchool;
	auto destination = schools;
	for (int i = num - 2; i >= 0; i--)
		for (int j = 0; j <= i; j++)
		{
			bool flag = false;
			if (int(destination[j].score) < int(destination[j+1].score)) flag = true;
			else if (int(destination[j].score) == int(destination[j+1].score) && destination[j].count > destination[j + 1].count) flag = true;
			else if (int(destination[j].score) == int(destination[j+1].score) && destination[j].count == destination[j + 1].count&&strcmp(destination[j].name, destination[j + 1].name) > 0) flag = true;
			if(flag)
			   mySwap(destination[j], destination[j + 1]);
		}*/
	cout << numOfSchool;
	for (int i = 0; i < numOfSchool; i++) {
		cout << endl;
		//判断是否并列
		int n = 0;
		for (n = 1; n <= numOfSchool; n++)
			if (int(schools[n - 1].score) == int(schools[i].score))
				break;
		cout << n << " " << schools[i].name << " " << int(schools[i].score) << " " << schools[i].count;
	}
}

void Solution::modify(char* id, double score, char* schoolName) {
	//化小写
	for (int i = 0; i < strlen(schoolName); i++) {
		if (schoolName[i] >= 'A'&&schoolName[i] <= 'Z') {
			schoolName[i] -= 'A' - 'a';
		}
	}
	//归并学院
	bool flag = false;
	int thisSchool = 0;
	for (int i = 0; i < numOfSchool; i++) {
		if (strcmp(schoolName, schools[i].name) == 0) {
			flag = true;
			thisSchool = i;
			break;
		}
	}
	if (!flag) {
		thisSchool = numOfSchool++;
		schools[thisSchool].count = 0;
		schools[thisSchool].score = 0.0;
		strcpy(schools[thisSchool].name, schoolName);
	}

	//开始算分
	schools[thisSchool].count++;
	if (id[0] == 'A') schools[thisSchool].scoreA += score;
	else if (id[0] == 'B') schools[thisSchool].scoreB += score;
	else if (id[0] == 'T') schools[thisSchool].scoreC += score;
}
//main函数不要做任何修改
int main()
{
	int numOfPerson;
	cin >> numOfPerson;   //输入考试人数

	char id[7]; //准考证号
	int score;  //分数
	char schoolName[7]; //学院名字

	Solution solution(numOfPerson);

	for (int i = 0; i < numOfPerson; i++) {
		cin >> id >> score >> schoolName;    // 读取考试信息
		solution.modify(id, score, schoolName);  //根据学生信息，修改所在学院的相应信息
	}
	solution.displayResult();    //输出结果

	return 0;
}