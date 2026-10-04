#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q; cin >> q;

    map<int, int> m;
    while(q--) {
        string s; int k, v; cin >> s;
        if(s=="insert") {
            cin >> k >> v;
            m[k]=v;
        } else if(s=="erase") {
            cin >> k;
            m.erase(k);
        } else if(s=="count") {
            cin >> k;
            cout << m.count(k) << '\n';
        } else if(s=="get") {
            cin >> k;
            if(m.count(k)) cout << m[k] << '\n';
            else cout << "-1\n";
        } else {
            cout << m.size() << '\n';
        }
    }
}