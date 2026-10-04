#include<bits/stdc++.h>
using namespace std;

int par[200'000], sz[200'000];

int find(int x) {
    if(x==par[x]) return x;
    return par[x] = find(par[x]);
}

void merge(int x, int y) {
    x=find(x);
    y=find(y);
    if(x<y) {
        par[y]=x;
        sz[x]+=sz[y];
    } else if(x>y) {
        par[x]=y;
        sz[y]+=sz[x];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    vector<pair<int, int>> v(n), query(q);
    for(int i=0;i<n;i++) {
        cin >> v[i].first;
        v[i].second=i;
    }
    for(int i=0;i<q;i++) {
        cin >> query[i].first;
        query[i].second=i;
    }
    sort(v.begin(), v.end());
    sort(query.begin(), query.end());

    int idx=0, cur=0;
    vector<int> res(q);
    for(auto [x, qi]:query) {
        while(idx<n && v[idx].first<=x) {
            int i=v[idx++].second;
            sz[i]=1; par[i]=i;
            if(i>0 && sz[i-1]) merge(i, i-1);
            if(i+1<n && sz[i+1]) merge(i, i+1);
            cur = max(cur, sz[find(i)]);
        }
        res[qi]=cur;
    }
    for(auto e:res) cout << e << '\n';
}
