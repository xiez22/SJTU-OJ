#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	string ch1, ch2;
	cin >> ch1 >> ch2;
	auto pos1 = ch1.find('.'), pos2 = ch2.find('.');

	auto ch10 = ch1.substr(0, pos1), ch11 = ch1.substr(pos1 + 1);
	auto ch20 = ch2.substr(0, pos2), ch21 = ch2.substr(pos2 + 1);

	string ans;

	auto l1=ch10.length(),l2=ch20.length();
	for(int i=0,jw=(atoi(ch11.c_str())+atoi(ch21.c_str())>=100);i<l1||i<l2||jw;++i){
		int a = i<ch10.length()?ch10[l1-i-1]-'0':0,b=i<ch20.length()?ch20[l2-i-1]-'0':0;
		if(a+b+jw>=10){
			ans.push_back(a+b+jw-10+'0');
			jw=1;
		}else{
			ans.push_back(a+b+jw+'0');
			jw = 0;
		}
	}

	reverse(ans.begin(),ans.end());
	cout<<ans<<".";
	printf("%02d\n",(atoi(ch11.c_str())+atoi(ch21.c_str()))%100);

	return 0;
}