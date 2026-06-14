#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX=3'000'001;

ll a[MAX];

void update(int i, ll val) {
    while(i<MAX) {
        a[i]+=val;
        i+=i&-i;
    }
}

ll query(int i) {
    ll ret=0;
    while(i) {
        ret+=a[i];
        i-=i&-i;
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    for(int i=1;i<=n;i++) {
        ll val; cin >> val;
        a[i]+=val;
        int nxt=i+(i&-i);
        if(nxt<=n) a[nxt]+=a[i];
    }

    while(q--) {
        int op; cin >> op;
        if(op==1) {
            int i, x; cin >> i >> x;
            update(i, x);
        } else {
            int l, r; cin >> l >> r;
            cout << query(r)-query(l-1) << '\n';
        }
    }
}
