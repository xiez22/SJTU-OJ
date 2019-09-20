#include "iostream"
using namespace std;

int main() {
	bool data[1100000] = { 0 };
	//¼ÆËãËØÊı
	for (int i = 2; i < 1100; i++) {
		if (!data[i]) {
			for (int sum = i * 2; sum < 1100000; sum += i)
				data[sum] = true;
		}
	}
	
	//ÅĞ¶ÏËØÊı
	int input;
	cin >> input;
	int left, right;
	for (left = input; data[left]; left--) {}
	for (right = input; data[right]; right++) {}
	cout << right - left;

	return 0;
}