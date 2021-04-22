//
// Created by 谢哲 on 2021/4/22.
//
// 注意：这道题的输入不包括两侧的双引号

#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;

    stack<char> sdata;

    if (s.length()<1 || s.length()>10000) {
        cout << 0;
        return 0;
    }

    for (auto p: s) {
        if (p==')') {
            if (sdata.empty()||sdata.top()!='(') {
                cout<<0;
                return 0;
            }
            else sdata.pop();
        }
        else if (p==']') {
            if (sdata.empty()||sdata.top()!='[') {
                cout<<0;
                return 0;
            }
            else sdata.pop();
        }
        else if (p=='}') {
            if (sdata.empty()||sdata.top()!='{') {
                cout<<0;
                return 0;
            }
            else sdata.pop();
        }
        else sdata.push(p);
    }

    if (sdata.empty()) {cout<<1;}
    else cout<<0;

    return 0;
}
