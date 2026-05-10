#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    stack<int> stk;
    int q; cin >> q;
    while(q--) {
        string s; int x; cin >> s;
        if(s=="push") {
            cin >> x;
            stk.push(x);
        } else if(s=="pop") {
            stk.pop();
        } else if(s=="top") {
            cout << stk.top() << '\n';
        } else {
            cout << stk.size() << '\n';
        }
    }
}