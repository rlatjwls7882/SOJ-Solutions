#include<bits/stdc++.h>
using namespace std;

bool notPrime[10'000'001] = {true, true};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    for(int i=2;i*i<=n;i++) {
        if(notPrime[i]) continue;
        for(int j=i*i;j<=n;j+=i) notPrime[j]=true;
    }
    while(q--) {
        int x; cin >> x;
        cout << (notPrime[x] ? "No\n" : "Yes\n");
    }
}
