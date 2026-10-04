#include<bits/stdc++.h>
using namespace std;

int a[100'000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    for(int i=0;i<n;i++) cin >> a[i];
    while(q--) {
        int x; cin >> x;
        auto it = lower_bound(a, a+n, x);
        if(it==a+n || *it!=x) cout << "-1\n";
        else cout << it-a << '\n';
    }
}
