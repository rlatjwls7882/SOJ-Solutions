#include<bits/stdc++.h>
#include<ext/rope>
using namespace std;
using namespace __gnu_cxx;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s; cin >> s;
    crope rp(s.c_str());

    int q; cin >> q;
    while(q--) {
        int op, l, r, p; string t; cin >> op;
        if(op==1) {
            cin >> p >> t;
            rp.insert(p-1, t.c_str());
        } else if(op==2) {
            cin >> l >> r;
            rp.erase(l-1, r-l+1);
        } else if(op==3) {
            cin >> l >> r;
            cout << rp.substr(l-1, r-l+1) << '\n';
        } else if(op==4) {
            cin >> l >> r;
            rp = rp.substr(l-1, r-l+1)+rp.substr(0, l-1)+rp.substr(r, rp.size()-r);
        } else {
            cin >> l >> r;
            rp = rp.substr(0, l-1)+rp.substr(r, rp.size()-r+1)+rp.substr(l-1, r-l+1);
        }
    }
}
