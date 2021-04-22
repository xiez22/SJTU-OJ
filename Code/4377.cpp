//
// Created by 谢哲 on 2021/4/13.
//

#include <iostream>
#include <vector>
using namespace std;

constexpr long long mod = 1e9+7;

vector<long long> dp_data;


long long dp(int l, int r) {
    if (dp_data[r-l]>=0) return dp_data[r-l];

    if (r-l==1) return 1;
    if (r==l) return 1;

    long long ans = 0;
    for (int i=l;i<r;++i) {
        long long ans_l = dp(l, i);
        long long ans_r = dp(i+1, r);
        ans = (ans+(ans_l*ans_r) % mod)%mod;
    }
    return dp_data[r-l] = ans;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin>>n;

    dp_data.resize(n+1, -1);

    cout<<dp(0, n);

    return 0;
}
