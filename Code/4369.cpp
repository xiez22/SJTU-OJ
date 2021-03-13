//
// Created by ligongzzz on 2021/3/13.
//
// 4369
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int a, b;
    cin >> a >> b;

    int start_len = min(1, int(to_string(a).length()/2));
    int cnt = 0;

    for (int len=start_len;;++len) {
        int nmax = 1;
        for (int i=len-1;i;--i, nmax*=10);

        for(int first_num=2;first_num<10;first_num+=2) {
            for(int remain=0;remain<nmax;++remain) {
                int ans = first_num*nmax+remain;
                string ans_str = to_string(ans);
                reverse(ans_str.begin(), ans_str.end());
                ans = stoi(to_string(ans)+ans_str);

                if (ans>b) {
                    if (cnt==0) cout<<0<<'\n';
                    return 0;
                }

                if (ans>=a) {
                    ++cnt;
                    cout<<ans<<'\n';
                }
            }
        }
    }

    return 0;
}
