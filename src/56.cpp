#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX=1'000'001;

ll SZ=1, a[MAX*4];

void update(int i, int val) {
    i+=SZ;
    a[i]+=val;
    while(i>1) {
        i>>=1;
        a[i]=a[i*2]+a[i*2+1];
    }
}

int query(ll k) {
    int i=1;
    while(i<SZ) {
        i<<=1;
        if(a[i]<k) k-=a[i++];
    }
    return i-SZ+1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    while(SZ<n) SZ<<=1;
    for(int i=0;i<n;i++) cin >> a[i+SZ];
    for(int i=SZ-1;i>0;i--) a[i]=a[i*2]+a[i*2+1];
    while(q--) {
        int op; cin >> op;
        if(op==1) {
            int i, x; cin >> i >> x;
            update(i-1, x);
        } else {
            ll k; cin >> k;
            cout << query(k) << '\n';
        }
    }
}
