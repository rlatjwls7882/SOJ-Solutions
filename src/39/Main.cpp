#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll LINF=0x3f3f3f3f3f3f3f3f;

struct edge {
    ll v, w;
};

ll dist[1001];
vector<vector<edge>> conn(1001);

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, s; cin >> n >> m >> s;
    while(m--) {
        ll u, v, w; cin >> u >> v >> w;
        conn[u].push_back({v, w});
    }

    fill(dist, dist+n+1, LINF);
    dist[s]=0;
    for(int i=0;i<n;i++) {
        bool update=false;
        for(int j=1;j<=n;j++) {
            if(dist[j]==LINF) continue;
            for(auto [nxt, w]:conn[j]) {
                if(dist[nxt]>dist[j]+w) {
                    dist[nxt]=dist[j]+w;
                    update=true;
                }
            }
        }
        if(!update) break;
        if(i==n-1) return !(cout << "NEGATIVE CYCLE");
    }
    for(int i=1;i<=n;i++) {
        if(dist[i]==LINF) cout << "INF\n";
        else cout << dist[i] << '\n';
    }
}
