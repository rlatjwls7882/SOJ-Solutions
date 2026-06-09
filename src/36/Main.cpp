#include<bits/stdc++.h>
using namespace std;

long long pow(long long a, long long b, long long m) {
    long long ret=1;
    while(b) {
        if(b&1) ret=ret*a%m;
        a=a*a%m;
        b>>=1;
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    long long a, b, m; cin >> a >> b >> m;
    cout << pow(a, b, m);
}
