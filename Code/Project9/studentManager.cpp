#include "studentManager.h"
#include "list"

istream &operator>>(istream &input, student &b) {
	input >> b.num >> b.name >> b.mark;
	return input;
}

ostream &operator<<(ostream &output, const student &b) {
	output << b.num << " " << b.name << " " << b.mark;
	return output;
}

int startManager() {
	list<student> stuList;
	while (true) {
		int input;
		bool exit = false;
		cin >> input;

		switch (input) {
		case 1:
		{
			student temp;
			bool flag = false;
			cin >> temp;
			//¼ì²éÖØ¸´
			for (auto i = stuList.begin(); i!=stuList.end(); i++) {
				if (i->num == temp.num) {
					flag = true;
					cout << "FAILED" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					break;
				}
			}
			if (!flag) {
				stuList.push_back(temp);
				cout << "SUCCESS" << endl;
			}
			break;
		}
		case 2:
		{
			for (auto i = stuList.begin(); i!=stuList.end(); i++)
				cout << *i << endl;
			break;
		}
		case 3:
		{
			int temp;
			cin >> temp;
			for (auto i = stuList.begin(); i!=stuList.end(); i++)
				if (temp == i->num) {
					cout << *i << endl;
					break;
				}
			break;
		}
		case 4:
		{
			string temp;
			cin >> temp;
			for (auto i = stuList.begin(); i!=stuList.end(); i++)
				if (temp == i->name) {
					cout << *i << endl;
					break;
				}
			break;
		}
		case 5:
		{
			list<student> temp(stuList);
			stable_sort(temp.begin(), temp.end(), [](student a, student b) {return a.num < b.num; });
			for (auto i = temp.begin(); i!=temp.end(); i++)
				cout << *i << endl;
			break;
		}
		case 6:
		{
			list<student> temp(stuList);
			stable_sort(temp.begin(), temp.end(), [](student a, student b) {return a.mark > b.mark; });
			for (auto i = temp.begin(); i!=temp.end(); i++)
				cout << *i << endl;
			break;
		}
		default:
		{
			cout << "END";
			exit = true;
			break;
		}
		}
		if (exit)
			break;
	}
	return 0;
}