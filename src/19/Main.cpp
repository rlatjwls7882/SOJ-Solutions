#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q; cin >> q;
    deque<int> D;
    while(q--) {
        string s; int x; cin >> s;
        if(s=="push_front") {
            cin >> x;
            D.push_front(x);
        } else if(s=="push_back") {
            cin >> x;
            D.push_back(x);
        } else if(s=="front") {
            cout << D.front() << '\n';
        } else if(s=="back") {
            cout << D.back() << '\n';
        } else if(s=="size") {
            cout << D.size() << '\n';
        } else if(s=="pop_back") {
            D.pop_back();
        } else {
            D.pop_front();
        }
    }
}
