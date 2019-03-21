#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

int main() {
	int n;
	scanf("%d", &n);

	char dest[209];
	scanf("%s", dest);
	auto dest_len = strlen(dest);
	int ans = 0;

	//字符串拼接处理
	for (int i = dest_len; i >= 1; --i) {
		dest[i + dest_len - 2] = dest[i];
	}

	for (int i = 0; i < n; ++i) {
		char temp[209];
		scanf("%s", temp);
		auto temp_len = strlen(temp);
		if (temp_len == dest_len) {
			temp[temp_len - 1] = 0;
			if (strstr(dest, temp + 1) != nullptr) {
				++ans;
				continue;
			}
			//反转
			char reverse_temp[209] = { 0 };
			for (int i = 0; i < temp_len - 2; ++i) {
				reverse_temp[i] = temp[temp_len - i - 2];
			}
			if (strstr(dest, reverse_temp) != nullptr) {
				++ans;
				continue;
			}
		}
	}

	cout << ans;

	return 0;
}