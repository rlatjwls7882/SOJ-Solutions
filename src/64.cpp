#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MIN=0, MAX=(1<<30)-1;

struct Node {
    int l=-1, r=-1;
    ll val=0, lazy=0;
};

vector<Node> arr = vector<Node>(1);

int newNode() {
    arr.push_back({});
    return arr.size()-1;
}

int lc(int p) {
    if(arr[p].l==-1) arr[p].l=newNode();
    return arr[p].l;
}

int rc(int p) {
    if(arr[p].r==-1) arr[p].r=newNode();
    return arr[p].r;
}

void apply(int p, ll x) {
    arr[p].val+=x;
    arr[p].lazy+=x;
}

void updateLazy(int nodeNum, int nodeL, int nodeR) {
    if(arr[nodeNum].lazy && nodeL!=nodeR) {
        apply(lc(nodeNum), arr[nodeNum].lazy);
        apply(rc(nodeNum), arr[nodeNum].lazy);
        arr[nodeNum].lazy=0;
    }
}

void addRange(int L, int R, ll val, int nodeNum=0, int nodeL=MIN, int nodeR=MAX) {
    if(R<nodeL || nodeR<L) return;
    if(L<=nodeL && nodeR<=R) return apply(nodeNum, val);
    updateLazy(nodeNum, nodeL, nodeR);
    int mid=nodeL+nodeR>>1;
    addRange(L, R, val, lc(nodeNum), nodeL, mid);
    addRange(L, R, val, rc(nodeNum), mid+1, nodeR);
    ll v1 = arr[nodeNum].l!=-1 ? arr[arr[nodeNum].l].val : 0;
    ll v2 = arr[nodeNum].r!=-1 ? arr[arr[nodeNum].r].val : 0;
    arr[nodeNum].val=max(v1, v2);
}

ll maxRange(int L, int R, int nodeNum=0, int nodeL=MIN, int nodeR=MAX, ll z=0) {
    if(R<nodeL || nodeR<L) return 0;
    if(nodeNum==-1) return z;
    if(L<=nodeL && nodeR<=R) return arr[nodeNum].val+z;
    int mid = nodeL+nodeR>>1;
    z+=arr[nodeNum].lazy;
    return max(maxRange(L, R, arr[nodeNum].l, nodeL, mid, z), maxRange(L, R, arr[nodeNum].r, mid+1, nodeR, z));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q; cin >> q;
    int ans=0;
    while(q--) {
        int op, a, b, x; cin >> op >> a >> b;
        int l=a^ans, r=b^ans;
        if(l>r) swap(l, r);
        if(op==1) {
            cin >> x;
            addRange(l, r, x);
        } else {
            ans = maxRange(l, r);
            cout << ans << '\n';
        }
    }
}
