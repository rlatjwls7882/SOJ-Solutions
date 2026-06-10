#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct element {
    ll u, v, w;
    bool operator<(const element &e) const {
        return w<e.w;
    }
};

int par[100'001];

int find(int x) {
    if(x==par[x]) return x;
    return par[x] = find(par[x]);
}

bool merge(int x, int y) {
    x=find(x);
    y=find(y);
    if(x==y) return false;
    if(x>y) swap(x, y);
    par[x]=y;
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;

    for(int i=1;i<=n;i++) par[i]=i;
    vector<element> v(m);
    for(int i=0;i<m;i++) cin >> v[i].u >> v[i].v >> v[i].w;
    sort(v.begin(), v.end());

    ll res=0;
    for(auto [u, v, w]:v) {
        if(merge(u, v)) {
            res+=w;
        }
    }
    cout << res;
}
