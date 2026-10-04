#include<bits/stdc++.h>
using namespace std;

long long MOD = 998244353;

long long pow(long long a, long long b) {
    long long ret=1;
    while(b) {
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    long long a; cin >> a;
    cout << pow(a, MOD-2)%MOD;
}
