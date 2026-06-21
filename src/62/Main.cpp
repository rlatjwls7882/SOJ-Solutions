#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX=200'001*4;

ll SZ=1, a[MAX], lazy[MAX];

void updateLazy(int nodeNum) {
    if(lazy[nodeNum]) {
        a[nodeNum]+=lazy[nodeNum];
        if(nodeNum<SZ) {
            lazy[nodeNum*2]+=lazy[nodeNum];
            lazy[nodeNum*2+1]+=lazy[nodeNum];
        }
        lazy[nodeNum]=0;
    }
}

void updateRange(int L, int R, ll val, int nodeNum=1, int nodeL=0, int nodeR=SZ-1) {
    updateLazy(nodeNum);
    if(R<nodeL || nodeR<L) return;
    if(L<=nodeL && nodeR<=R) {
        lazy[nodeNum]+=val;
        updateLazy(nodeNum);
        return;
    }
    int mid=nodeL+nodeR>>1;
    updateRange(L, R, val, nodeNum*2, nodeL, mid);
    updateRange(L, R, val, nodeNum*2+1, mid+1, nodeR);
    a[nodeNum]=max(a[nodeNum*2], a[nodeNum*2+1]);
}

ll maxRange(int L, int R, int nodeNum=1, int nodeL=0, int nodeR=SZ-1) {
    updateLazy(nodeNum);
    if(R<nodeL || nodeR<L) return LONG_LONG_MIN;
    if(L<=nodeL && nodeR<=R) return a[nodeNum];
    int mid=nodeL+nodeR>>1;
    return max(maxRange(L, R, nodeNum*2, nodeL, mid), maxRange(L, R, nodeNum*2+1, mid+1, nodeR));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    while(SZ<n) SZ<<=1;
    for(int i=0;i<n;i++) cin >> a[i+SZ];
    for(int i=SZ-1;i>0;i--) a[i]=max(a[i*2], a[i*2+1]);
    while(q--) {
        int op, l, r, x; cin >> op >> l >> r;
        if(op==1) {
            cin >> x;
            updateRange(l-1, r-1, x);
        } else {
            cout << maxRange(l-1, r-1) << '\n';
        }
    }
}
