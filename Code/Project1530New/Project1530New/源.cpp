#include "iostream"
#include "cstring"

using namespace std;

char *ch;

void preorder(char *str,int pos, int num) {
	printf("%c", str[pos-1]);
	if (pos * 2 <= num)
		preorder(str, pos * 2, num);
	if (pos * 2 + 1 <= num)
		preorder(str, pos * 2 + 1, num);
}
void inorder(char *str, int pos, int num) {
	if (pos * 2 <= num)
		inorder(str, pos * 2, num);
	printf("%c", str[pos - 1]);
	if (pos * 2 + 1 <= num)
		inorder(str, pos * 2 + 1, num);
}
void postorder(char *str, int pos, int num) {
	if (pos * 2 <= num)
		postorder(str, pos * 2, num);
	if (pos * 2 + 1 <= num)
		postorder(str, pos * 2 + 1, num);
	printf("%c", str[pos - 1]);
}

void preorderWrite(char *str,char *input, int pos, int num) {
	str[pos - 1] = *ch;
	ch++;
	if (pos * 2 <= num)
		preorderWrite(str,input, pos * 2, num);
	if (pos * 2 + 1 <= num)
		preorderWrite(str,input, pos * 2 + 1, num);
}

void inorderWrite(char *str,char *input, int pos, int num) {
	if (pos * 2 <= num)
		inorderWrite(str,input, pos * 2, num);
	str[pos - 1] = *ch;
	ch++;
	if (pos * 2 + 1 <= num)
		inorderWrite(str,input, pos * 2 + 1, num);
}

void postorderWrite(char *str,char *input, int pos, int num) {
	if (pos * 2 <= num)
		postorderWrite(str,input, pos * 2, num);
	if (pos * 2 + 1 <= num)
		postorderWrite(str,input, pos * 2 + 1, num);
	str[pos - 1] = *ch;
	ch++;
}

int main() {
	int num;
	cin >> num;

	for (; num > 0; num--) {
		int n;
		scanf("%d", &n);
		char order[100], op[100], *str = new char[n + 1];
		scanf("%s %s\n%s", order, op, str);
		
		if (strcmp(op, "ENCODE") == 0) {
			if (strcmp(order, "PREORDER") == 0) {
				preorder(str, 1, strlen(str));
				delete str;
			}
			else if (strcmp(order, "INORDER") == 0) {
				inorder(str, 1, strlen(str));
				delete str;
			}
			else if (strcmp(order, "POSTORDER") == 0) {
				postorder(str, 1, strlen(str));
				delete str;
			}
		}
		if (strcmp(op, "DECODE") == 0) {
			ch = str;
			char *output = new char[n + 1]{ 0 };
			if (strcmp(order, "PREORDER") == 0) {
				preorderWrite(output,str, 1, strlen(str));
				delete str;
			}
			else if (strcmp(order, "INORDER") == 0) {
				inorderWrite(output,str, 1, strlen(str));
				delete str;
			}
			else if (strcmp(order, "POSTORDER") == 0) {
				postorderWrite(output,str, 1, strlen(str));
				delete str;
			}
			printf("%s", output);
			delete output;
		}


		printf("\n");
	}

	return 0;
}