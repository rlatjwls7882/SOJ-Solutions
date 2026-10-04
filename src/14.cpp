#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll MAX = 1e18;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;

    vector<ll> v;
    for(ll i=2;i<=1000000;i++) {
        ll cur=i*i*i;
        while(true) {
            v.push_back(cur);
            if(cur>MAX/i) break;
            cur*=i;
        }
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    while(t--) {
        ll n; cin >> n;
        if(n==1) {
            cout << "No\n";
        } else if((ll)sqrtl(n)*(ll)sqrtl(n)==n) {
            cout << "Yes\n";
        } else {
            ll f = lower_bound(v.begin(), v.end(), n)-v.begin();
            cout << (f!=v.size() && v[f]==n ? "Yes\n" : "No\n");
        }
    }
}