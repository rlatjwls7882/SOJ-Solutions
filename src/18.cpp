#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll pow(ll a, ll n, ll MOD) {
    ll ret=1;
    while(n) {
        if(n&1) ret=ret*a%MOD;
        n>>=1;
        a=a*a%MOD;
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while(t--) {
        ll a, b, n, p; cin >> a >> b >> n >> p;
        cout << (pow(b, n, p)-pow(b, n, a)+p)*pow(a, p-2, p)%p << '\n';
    }
}
