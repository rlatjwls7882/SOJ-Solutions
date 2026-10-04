#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    set<int> s;
    int q; cin >> q;
    while(q--) {
        string st; int x; cin >> st;
        if(st=="insert") {
            cin >> x;
            s.insert(x);
        } else if(st=="erase") {
            cin >> x;
            s.erase(x);
        } else if(st=="count") {
            cin >> x;
            cout << s.count(x) << '\n';
        } else {
            cout << s.size() << '\n';
        }
    }
}