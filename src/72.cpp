#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int par[200'001];

int find(int x) {
    if(x==par[x]) return x;
    return par[x]=find(par[x]);
}

void merge(int x, int y) {
    x=find(x);
    y=find(y);
    if(x<y) par[y]=x;
    else par[x]=y;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, q; cin >> n >> m >> q;
    vector<pair<int, int>> conn(m);
    for(auto &[u, v]:conn) cin >> u >> v;

    vector<pair<int, int>> query(q);
    for(auto &[a, b]:query) cin >> a >> b;
    vector<int> l(q, 1), r(q, m+1);
    while(true) {
        vector<vector<int>> mid(m+2);
        bool chk=false;
        for(int i=0;i<q;i++) {
            if(l[i]<r[i]) {
                chk=true;
                mid[l[i]+r[i]>>1].push_back(i);
            }
        }
        if(!chk) break;

        for(int i=1;i<=n;i++) par[i]=i;
        for(int i=1;i<=m;i++) {
            merge(conn[i-1].first, conn[i-1].second);
            for(int idx:mid[i]) {
                if(find(query[idx].first)==find(query[idx].second)) r[idx]=i;
                else l[idx]=i+1;
            }
        }
    }
    for(auto e:l) cout << (e==m+1 ? -1 : e) << '\n';
}
