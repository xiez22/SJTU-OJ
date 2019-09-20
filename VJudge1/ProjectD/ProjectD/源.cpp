#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;

char buff[100009] = { 0 };
int ans[26] = { 0 };

int main() {
	while (gets_s(buff)) {
		memset(ans, 0, sizeof(ans));
		int length = strlen(buff);
		for (int i = 0; i < length; ++i) {
			if (buff[i] >= 'a' && buff[i] <= 'z')
				++ans[buff[i] - 'a'];
		}
		for (int i = 0; i < 26; ++i)
			printf("%c:%d\n", i + 'a', ans[i]);
		printf("\n");
	}

	return 0;
}