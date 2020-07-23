#include <iostream>
using namespace std;

int main() {
    int H, h, n, num = 0;
    cin >> H >> h >> n;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        if (H + h >= t) {
            num++;
        }
    }
    cout << num << endl;
}
