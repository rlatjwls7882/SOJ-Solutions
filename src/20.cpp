#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    priority_queue<int> pq;
    int q; cin >> q;
    while(q--) {
        string s; int x; cin >> s;
        if(s=="push") {
            cin >> x;
            pq.push(x);
        } else if(s=="pop") {
            pq.pop();
        } else if(s=="top") {
            cout << pq.top() << '\n';
        } else {
            cout << pq.size() << '\n';
        }
    }
}
