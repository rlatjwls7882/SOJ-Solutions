#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll f[101][101], c[101][101], prv[101];
vector<vector<int>> conn(101);

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, s, t; cin >> n >> m >> s >> t;
    while(m--) {
        ll u, v, w; cin >> u >> v >> w;
        c[u][v]+=w;
        conn[u].push_back(v);
        conn[v].push_back(u);
    }

    ll res=0;
    while(true) {
        queue<int> q; q.push(s);
        memset(prv, -1, sizeof prv);
        while(!q.empty() && prv[t]==-1) {
            int cur=q.front(); q.pop();
            for(int next:conn[cur]) {
                if(c[cur][next]-f[cur][next] && prv[next]==-1) {
                    prv[next]=cur;
                    q.push(next);
                }
            }
        }
        if(prv[t]==-1) break;

        ll flow=0x3f3f3f3f;
        for(int i=t;i!=s;i=prv[i]) flow=min(flow, c[prv[i]][i]-f[prv[i]][i]);
        for(int i=t;i!=s;i=prv[i]) {
            f[prv[i]][i]+=flow;
            f[i][prv[i]]-=flow;
        }
        res+=flow;
    }
    cout << res;
}
