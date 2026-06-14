#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX=200'001*4;

ll SZ=1, a[MAX];

void update(int i, ll val) {
    i+=SZ;
    a[i]=val;
    while(i>1) {
        i>>=1;
        a[i]=a[i*2]+a[i*2+1];
    }
}

ll query(int L, int R) {
    ll ret=0;
    for(L+=SZ, R+=SZ;L<=R;L>>=1, R>>=1) {
        if(L&1) ret+=a[L++];
        if(!(R&1)) ret+=a[R--];
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    while(SZ<n) SZ<<=1;
    for(int i=0;i<n;i++) cin >> a[SZ+i];
    for(int i=SZ-1;i>0;i--) a[i]=a[i*2]+a[i*2+1];

    while(q--) {
        int op; cin >> op;
        if(op==1) {
            int i, x; cin >> i >> x;
            update(i-1, x);
        } else {
            int l, r; cin >> l >> r;
            cout << query(l-1, r-1) << '\n';
        }
    }
}
