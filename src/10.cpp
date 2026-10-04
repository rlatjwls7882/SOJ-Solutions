#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<int> v;
    int q; cin >> q;
    while(q--) {
        string s; int i, x; cin >> s;
        if(s=="push_back") {
            cin >> x;
            v.push_back(x);
        } else if(s=="pop_back") {
            v.pop_back();
        } else if(s=="front") {
            cout << v.front() << '\n';
        } else if(s=="back") {
            cout << v.back() << '\n';
        } else {
            cin >> i;
            cout << v[i] << '\n';
        }
    }
}