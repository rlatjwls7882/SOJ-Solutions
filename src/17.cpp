#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    queue<int> Q;
    int q; cin >> q;
    while(q--) {
        string s; cin >> s;
        if(s=="push") {
            int x; cin >> x;
            Q.push(x);
        } else if(s=="pop") {
            Q.pop();
        } else if(s=="front") {
            cout << Q.front() << '\n';
        } else if(s=="back") {
            cout << Q.back() << '\n';
        } else {
            cout << Q.size() << '\n';
        }
    }
}