#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

constexpr int mod = 198964;

struct type {
	char name[40] = { 0 };
	int val = 0;
};

type hash_map[mod];
char names[10009][40] = { 0 };

int get_hash(char* key) {
	int length = strlen(key);
	int ans = 0;
	for (int i = 0; i < length; ++i) {
		if(key[i]>='a')
			ans = ((ans * 26) + key[i] - 'a') % mod;
		else
			ans = ((ans * 26) + key[i] - 'A') % mod;
	}
	for (; strcmp(hash_map[ans].name, key) != 0; ans = (ans + 1) % mod);
	return ans;
}

int ins_hash(char* key) {
	int length = strlen(key);
	int ans = 0;
	for (int i = 0; i < length; ++i) {
		if (key[i] >= 'a')
			ans = ((ans * 26) + key[i] - 'a') % mod;
		else
			ans = ((ans * 26) + key[i] - 'A') % mod;
	}
	for (; hash_map[ans].name[0] != 0; ans = (ans + 1) % mod);
	return ans;
}

int main() {
	int n;
	scanf("%d", &n);

	int memory_index = 0;
	for (int i = 0; i < n; ++i) {
		scanf("%s", names[i]);

		int index = ins_hash(names[i]);
		strcpy(hash_map[index].name, names[i]);

		if (strcmp(names[i], "memory") == 0)
			memory_index = i;
	}

	int t;
	scanf("%d", &t);

	for (; t > 0; --t) {
		for (int i = 0; i < n; ++i) {
			char temp[40];
			int num;
			scanf("%d %s", &num, temp);

			hash_map[get_hash(temp)].val += num;
		}
		//检查第几位
		int ans = 1;
		int cur_val = hash_map[get_hash(names[memory_index])].val;
		for (int i = 0; i < n; ++i) {
			if (hash_map[get_hash(names[i])].val>cur_val)
				++ans;
		}
		printf("%d\n", ans);
	}

	return 0;
}