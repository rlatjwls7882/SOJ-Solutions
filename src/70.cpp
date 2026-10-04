#include<bits/stdc++.h>
using namespace std;

int a[222'222], sz=450, sq[450];

void update(int i, int x) {
    a[i]=x;
    i=i/sz*sz;
    sq[i/sz]=INT_MIN;
    for(int j=i;j<i+sz;j++) {
        sq[i/sz]=max(sq[i/sz], a[j]);
    }
}

int query(int l, int r, int x) {
    while(l%sz && l<=r) {
        if(a[l]>=x) return l;
        l++;
    }
    while(l+sz<=r) {
        if(sq[l/sz]>=x) {
            for(int i=l;i<l+sz;i++) {
                if(a[i]>=x) return i;
            }
        }
        l+=sz;
    }
    while(l<=r) {
        if(a[l]>=x) return l;
        l++;
    }
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    fill(sq, sq+sz, INT_MIN);
    for(int i=1;i<=n;i++) {
        cin >> a[i];
        sq[i/sz]=max(sq[i/sz], a[i]);
    }
    while(q--) {
        int op; cin >> op;
        if(op==1) {
            int i, x; cin >> i >> x;
            update(i, x);
        } else {
            int l, r, x; cin >> l >> r >> x;
            cout << query(l, r, x) << '\n';
        }
    }
}
