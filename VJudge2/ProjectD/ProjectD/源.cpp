#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

constexpr long long mod = (long long)(1e14 + 7);
constexpr long long hash1 = (long long)(1e9 + 7);
constexpr long long hash2 = (long long)(1949100111);
constexpr long long max_num = 12345677;

long long hash_list1[20009] = { 0 };
long long hash_list2[20009] = { 0 };
long long pnum1[20009] = { 0 };
long long pnum2[20009] = { 0 };

long long hash_map[int(max_num)] = { 0 };

bool exist(long long key) {
	long long ans = key % max_num;
	for (; 
		hash_map[ans] != key; 
		ans = (ans + 1LL) % max_num) {
		if (hash_map[ans] == 0) {
			return false;
		}
	}
	return true;
}

void insert(long long key) {
	long long ans = key % max_num;
	for (; 
		hash_map[ans] != 0; 
		ans = (ans + 1LL) % max_num);
	hash_map[ans] = key;
}

long long string_hash(int start, int len) {
	long long ans1 = (hash_list1[start + len] + hash1 - (hash_list1[start] * pnum1[len]) % hash1) % hash1;
	long long ans2 = (hash_list2[start + len] + hash2 - (hash_list2[start] * pnum2[len]) % hash2) % hash2;
	return (ans1 * ans2) % mod;
}

long long cal_hash(char* ch) {
	int length = strlen(ch);
	long long ans1 = 0, ans2 = 0;
	for (int i = 0; i < length; ++i) {
		ans1 = (ans1 * 31LL + (long long)(ch[i] - 'a' + 1)) % hash1;
		ans2 = (ans2 * 31LL + (long long)(ch[i] - 'a' + 1)) % hash2;
	}
	return (ans1 * ans2) % mod;
}

int mmax(int a, int b) {
	return a > b ? a : b;
}

int main() {
	//初始化列表
	pnum1[0] = 1;
	for (int i = 1; i < 20009; ++i) {
		pnum1[i] = (pnum1[i - 1] * 31LL) % hash1;
	}
	pnum2[0] = 1;
	for (int i = 1; i < 20009; ++i) {
		pnum2[i] = (pnum2[i - 1] * 31LL) % hash2;
	}

	char ch[20009] = { 0 };
	scanf("%s", ch);
	int length = strlen(ch);
	for (int i = 1; i <= length; ++i) {
		hash_list1[i] = (hash_list1[i - 1] * 31LL + (long long)(ch[i - 1] - 'a' + 1)) % hash1;
		hash_list2[i] = (hash_list2[i - 1] * 31LL + (long long)(ch[i - 1] - 'a' + 1)) % hash2;
	}

	char s[20009], e[20009];
	scanf("%s", s);
	scanf("%s", e);

	int slen = strlen(s), elen = strlen(e);
	auto s_hash = cal_hash(s), e_hash = cal_hash(e);

	int ans = 0;

	for (int start = 0; start + slen <= length; ++start) {
		if (string_hash(start, slen) != s_hash)
			continue;
		for (int end = mmax(start, start + slen - elen); end + elen <= length; ++end) {
			if (string_hash(end, elen) == e_hash) {
				//精确判断
				bool flag = true;
				for (int i = 0; i < slen; ++i) {
					if (s[i] != ch[start + i]) {
						flag = false;
						break;
					}
				}
				for (int i = 0; i < elen; ++i) {
					if (e[i] != ch[end + i]) {
						flag = false;
						break;
					}
				}
				if (!flag)
					continue;
				//判断是否已经存在
				long long this_hash = string_hash(start, end + elen - start);
				if (!exist(this_hash)) {
					insert(this_hash);
					++ans;
				}
			}
		}
	}

	cout << ans;

	return 0;
}