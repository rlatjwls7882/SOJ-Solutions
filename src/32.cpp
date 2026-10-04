#include<bits/stdc++.h>
using namespace std;

bool isPrime(long long n) {
    if(n<=1) return false;
    for(long long i=2;i*i<=n;i++) {
        if(n%i==0) return false;
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    long long n; cin >> n;
    cout << (isPrime(n) ? "Yes" : "No");
}
