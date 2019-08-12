#include "iostream"
#include "string"

using namespace std;

int main() {
	string dst, sub, src;
	cin >> dst >> sub >> src;

	//ÅÐ¶Ï
	if (dst.find(sub) == string::npos) {
		cout << "No string to replace!";
		return 0;
	}
	else if (src.find(sub) != string::npos) {
		cout << "error!";
		return 0;
	}

	//Ìæ»»
	while (dst.find(sub) != string::npos) {
		dst.replace(dst.find(sub), sub.length(), src);
	}

	cout << dst;

	return 0;
}