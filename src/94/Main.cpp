#include<bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("fma")
using namespace std;

typedef long long ll;
const ll MOD = 998244353;

ll pow(ll a, ll b) {
    ll ret=1;
    while(b) {
        if(b&1) ret=ret*a%MOD;
        b>>=1;
        a=a*a%MOD;
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll n; cin >> n;
    if(n%4!=1) return !(cout << 1);
    ll cnt=n/4;
    cout << (1-pow(pow(3LL, cnt), MOD-2)+MOD)%MOD;
}
