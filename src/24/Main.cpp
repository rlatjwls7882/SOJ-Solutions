#include<bits/stdc++.h>
using namespace std;

long long preSum[100'001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    for(int i=1;i<=n;i++) {
        cin >> preSum[i];
        preSum[i]+=preSum[i-1];
    }
    while(q--) {
        int l, r; cin >> l >> r;
        cout << preSum[r]-preSum[l-1] << '\n';
    }
}
