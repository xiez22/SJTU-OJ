#include "iostream"
#include "cstring"
using namespace std;

int main() {
	//所有文件内容
	char ch[200][3000] = { 0 };
	int row = 0;

	//输入
	while (true) {
		char temp[3000];
		cin.getline(temp, 3000);
		if (strcmp(temp, "******") == 0)
			break;
		row++;
		strcpy(ch[row], temp);
	}

	//操作
	while (true) {
		char op[100];
		cin >> op;
		if (strcmp(op, "quit") == 0) {
			cout << ch[1];
			for (int i = 2; i <= row; i++) cout << endl << ch[i];
			break;
		}
		if (strcmp(op, "list") == 0) {
			int n1, n2;
			cin >> n1 >> n2;

			//是否合法
			if (n1 > n2 || n1 <= 0 || n2 > row) {
				cout << "Error!"<<endl;
				continue;
			}
			for (int i = n1; i <= n2; i++)
				cout << ch[i] << endl;
		}
		if (strcmp(op, "ins") == 0) {
			int n1, n2;
			char str[3000];
			cin >> n1 >> n2;
			cin.get();
			cin.getline(str, 3000);
			if (n1 <= 0 || n1 > row  || n2 > strlen(ch[n1])+1) {
				cout << "Error!" << endl;
				continue;
			}
				strcat(str, ch[n1] + n2-1);
				strcpy(ch[n1] + n2-1, str);
		}
		if (strcmp(op, "del") == 0) {
			int n1, n2, num;
			cin >> n1 >> n2 >> num;
			if (n1 <= 0 || n1 > row || n2 > strlen(ch[n1]) + 1 || num <0 || num + n2 - 1 > strlen(ch[n1])) {
				cout << "Error!" << endl;
				continue;
			}
			strcpy(ch[n1] + n2 - 1, ch[n1] + num + n2 - 1);
		}
	}

	return 0;
}