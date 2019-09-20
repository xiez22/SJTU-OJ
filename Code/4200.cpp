#include "iostream"
#include "cstdio"
#include "cstdlib"
#include "algorithm"
#include "cstring"

using namespace std;

class Person {
public:
	Person() {}
	bool isLegal(); //判断输入是否合理，合理返回true,否则返回flase
	void read();    //读入居民信息

  // 可以根据设计自行添加所需成员
	friend class Solution;

private:
	char name[6];        //姓名
	char birthday[11];   //生日

  // 可以根据设计自行添加所需成员

};
void Person::read() {
	cin >> name >> birthday;
}

bool Person::isLegal() {
	int year, month, day;
	sscanf(birthday, "%d/%d/%d", &year, &month, &day);
	//判断不合理
	if (month > 12 || day > 31)
		return false;
	int yearTime = year * 10000 + month * 100 + day;
	if (yearTime > 20181220 || yearTime < 18981220)
		return false;
	else
		return true;
}

class Solution {
public:
	Solution() { count = 0; }
	void regPerson(const Person &person);//统计有效生日人数，以及最年轻与最年长的人
	void displayResult();  //输出相关信息

// 可以根据设计自行添加所需成员

private:
	char eldestName[6]; //最年长人的姓名
	char eldestBirthday[11]; //最年长人的生日
	char youngestName[6]; //最年轻人的姓名
	char youngestBirthday[11];  //最年轻人的生日
	int count;   //有效生日人数
};

void Solution::displayResult() {
	cout << count << " " << eldestName << " " << youngestName;
}

void Solution::regPerson(const Person &person) {
	count++;
	int year, month, day;
	int yearTime = 0, eldestYearTime = 0, youngestYearTime = 0;

	sscanf(person.birthday, "%d/%d/%d", &year, &month, &day);
	yearTime = year * 10000 + month * 100 + day;

	if (count > 1) {
		sscanf(eldestBirthday, "%d/%d/%d", &year, &month, &day);
		eldestYearTime = year * 10000 + month * 100 + day;

		sscanf(youngestBirthday, "%d/%d/%d", &year, &month, &day);
		youngestYearTime = year * 10000 + month * 100 + day;
	}

	//判断是否最大最小
	if (yearTime < eldestYearTime || count == 1) {
		strcpy(eldestName, person.name);
		strcpy(eldestBirthday, person.birthday);
	}
	if (yearTime > youngestYearTime || count == 1) {
		strcpy(youngestName, person.name);
		strcpy(youngestBirthday, person.birthday);
	}
}

//main函数不要做任何修改
int main()
{
	Solution solution;
	int num;
	cin >> num;
	for (int i = 0; i < num; i++) {
		Person person;
		person.read();
		if (person.isLegal()) {
			solution.regPerson(person);
		}
	}
	solution.displayResult();

	return 0;
}