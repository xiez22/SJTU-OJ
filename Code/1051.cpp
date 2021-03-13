#include "iostream"
using namespace std;

class myList {
public:
	class node {
	public:
		int data;
		node* next = nullptr;
	};

	node* head;
	node* rear;
	myList() {
		head = new node;
		rear = head;
	}
	
	~myList() {
		for (auto p = head; p!= nullptr;) {
			auto temp = p;
			p = p->next;
			delete temp;
		}
	}

	int find(int num) {
		int ans = 0;
		auto p = head;
		for (; p->next != nullptr; p = p->next,ans++) {
			if (p->next->data == num) {
				ans++;
				break;
			}
		}
		//ÒÆ¶¯
		if (head != p&&p->next!=nullptr) {
			auto temp = head->next;
			head->next = p->next;
			p->next = head->next->next;
			head->next->next = temp;
		}
		return ans;
	}
	
	void insert(int num) {
		auto p = head;
		bool flag = true;
		/*for (; p->next != nullptr; p = p->next)
			if (p->next->data == num) {
				flag = false;
				break;
			}*/

		if (flag) {
			rear->next = new node;
			rear = rear->next;
			rear->data = num;
		}
	}
};

int main() {
	ios::sync_with_stdio(false);

	int n, m;
	cin >> n;

	myList newList;

	for (; n > 0; n--) {
		int temp;
		cin >> temp;
		newList.insert(temp);
	}

	cin >> m;

	long long ans = 0;
	for (; m > 0; m--) {
		int temp;
		cin >> temp;
		ans += newList.find(temp);
	}

	cout << ans;

	return 0;
}