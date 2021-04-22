//
// Created by 谢哲 on 2021/4/22.
//

#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int cur_min = 999999999;
    int result = 0;

    int n;
    cin >> n;

    for(;n;--n) {
        int a;
        cin >> a;
        result = max(result, a - cur_min);
        cur_min = min(cur_min, a);
    }

    cout << result;

    return 0;
}
