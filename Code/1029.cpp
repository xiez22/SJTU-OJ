#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

class node {
public:
	int val = 0;
	node* next = nullptr;
};

node* heads[109] = { nullptr };
node* rears[109] = { nullptr };

char ch[10009] = { 0 };

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; ++i) {
		rears[i] = heads[i] = new node;
	}

	cin.getline(ch, 10009);

	for (int i = 1; i <= n; ++i) {
		cin.getline(ch, 10000);
		int length = strlen(ch);

		int num = 0;

		for (int j = 0; j < length; ++j) {
			if (ch[j] == ' ') {
				continue;
			}
			else if (ch[j] == '\n') {
				break;
			}
			else {
				num = num * 10 + ch[j] - '0';
				if (ch[j + 1]<'0' || ch[j + 1]>'9') {
					rears[i]->next = new node;
					rears[i] = rears[i]->next;
					rears[i]->val = num;
					num = 0;
				}
			}
		}
	}

	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);

		rears[b]->next = heads[a]->next;
		heads[a]->next = nullptr;
		rears[b] = rears[a];
		rears[a] = heads[a];
	}

	for (int i = n; i > 0; --i) {
		if (heads[i]->next == nullptr)
			continue;
		for (auto p = heads[i]->next; p; p = p->next)
			cout << p->val << " ";
	}

	return 0;
}