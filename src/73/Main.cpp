#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

struct element {
    ll a, b;
    ld x=1e-150;
};

ld meetX(element a, element b) { return (ld)(a.b-b.b)/(b.a-a.a); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q; cin >> q;
    vector<element> stk;
    while(q--) {
        int op; cin >> op;
        if(op==1) {
            int a, b; cin >> a >> b;
            element cur = {a, b};
            while(!stk.empty()) {
                cur.x=meetX(stk.back(), cur);
                if(cur.x>stk.back().x) break;
                stk.pop_back();
            }
            stk.push_back(cur);
        } else {
            int x; cin >> x;
            int l=0, r=stk.size()-1;
            while(l<r) {
                int m=l+r+1>>1;
                if(x<=stk[m].x) r=m-1;
                else l=m;
            }
            cout << stk[l].a*x+stk[l].b << '\n';
        }
    }
}
