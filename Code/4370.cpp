#include <iostream>
#include <stack>
using namespace std;

class myStack {
    stack<unsigned  int> real_stack;
    stack<pair<unsigned int,unsigned int>> min_stack;

public:
    void push(unsigned int x) {
        real_stack.push(x);
        if (min_stack.empty()||min_stack.top().second>x){
            min_stack.push(make_pair(real_stack.size(), x));
        }
    }

    void pop() {
        if (real_stack.empty()) {
            cout << "Empty\n";
            return;
        }
        if (min_stack.top().first==real_stack.size()) {
            min_stack.pop();
        }
        real_stack.pop();
    }

    void top() {
        if (real_stack.empty()) {
            cout << "Empty\n";
            return;
        }
        cout << real_stack.top() << "\n";
    }

    void getMin() {
        if (real_stack.empty()) {
            cout << "Empty\n";
            return;
        }
        cout << min_stack.top().second << "\n";
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n = 0;
    cin >> n;

    myStack stack1;

    for (;n;--n) {
        int a;
        cin >> a;
        if (a==0) {
            unsigned int b;
            cin >> b;
            stack1.push(b);
        }
        else if (a==1) {
            stack1.pop();
        }
        else if (a==2) {
            stack1.top();
        }
        else {
            stack1.getMin();
        }
    }
}
